#include "spec.h"
#include "utils/types.h"
#include "utils/log.h"
#include "utils/string.h"
#include <bit>
#include <map>
#include <iostream>

using ResourceID = uint64_t;
using OfferID = size_t;
using Units = uint64_t;

struct Dict {
  ResourceID lookup(str name) {
    if(!name_to_id.count(name)) {
      auto id = name_to_id.size();
      name_to_id[name] = id;
      id_to_name[id] = name;
    }
    return name_to_id[name];
  }
  str lookup_name(ResourceID id) const {
    return id_to_name.at(id);
  }
  size_t size() const { return name_to_id.size(); }
private:
  std::map<str,ResourceID> name_to_id;
  std::map<ResourceID,str> id_to_name;
};

struct Graph {
  struct End {
    ResourceID res; Units units;
    friend str show(const End &e){ return util::fmt("%x [%]",e.units,e.res); }
  };
  struct Edge {
    End from,to; OfferID offer;
    friend str show(const Edge &e){ return util::fmt("(%) -%> (%)",show(e.from),e.offer,show(e.to)); }
  };
  struct Node { vec<Edge> out,in; };
  vec<Node> nodes;
  void add(Edge e) {
    nodes[e.from.res].out.push_back(e);
    nodes[e.to.res].in.push_back(e);
  }

  vec<ResourceID> topo() const {
    vec<size_t> out_deg(nodes.size());
    vec<ResourceID> Q;
    for(size_t i=0; i<nodes.size(); i++) {
      if(!(out_deg[i] = nodes[i].out.size())) Q.push_back(i);
    }
    vec<ResourceID> res;
    while(Q.size()) {
      auto id = Q.back();
      Q.pop_back();
      res.push_back(id);
      for(auto e : nodes[id].in) {
        if(!out_deg[e.from.res]--) Q.push_back(e.from.res);
      }
    }
    return res;
  }

  Graph op() const {
    Graph G = *this;
    for(auto &n : G.nodes){
      std::swap(n.in,n.out);
      for(auto &e : n.in) std::swap(e.from,e.to);
      for(auto &e : n.out) std::swap(e.from,e.to);
    }
    return G;
  }
};

struct Spec {
  Dict names;
  ResourceID gold_id;
  size_t wtb_offers;
  size_t wts_offers;
  Graph trans; 
};

static Spec make_spec() { 
  Spec S;
  S.gold_id = S.names.lookup("g");
  auto wts = spec::WTS();
  auto wtb = spec::WTB();
  S.wts_offers = wts.size();
  S.wtb_offers = wtb.size();
  auto ts = wtb;
  ts.insert(ts.end(),wts.begin(),wts.end());
  for(auto offer : ts) {
    S.names.lookup(offer.obj.name);
    S.names.lookup(offer.price.name);
  }
  S.trans.nodes.resize(S.names.size());
  for(size_t i=0; i<ts.size(); i++) {
    S.trans.add(Graph::Edge{
      .from = {.res = S.names.lookup(ts[i].price.name), .units = ts[i].price.count},
      .to = {.res = S.names.lookup(ts[i].obj.name), .units = ts[i].obj.count},
      .offer = i,
    });
  }
  return S;
}


struct State {
  const Spec &S;
  vec<uint64_t> resources_avail;
  uint64_t wtb_used = 0;
  size_t wtb_used_count = 0;
  size_t depth = 0;

  friend str show(const State &s) {
    str wtb_used_bits = "";
    for(size_t i=0; i<s.S.wtb_offers; i++) wtb_used_bits += ((s.wtb_used>>i)&1) ? '1' : '0';
    vec<str> res;
    for(auto x : s.resources_avail) res.push_back(util::to_str(x));
    return util::fmt("{ depth = %; wtb_used = %; resources = {%} }",s.depth,wtb_used_bits,util::join(",",res));
  }

  struct Transaction {
    State &s;
    const Graph::Edge &e;
    Units t = 0;
    bool wtb;
    INL operator bool(){ return t; }
    INL Transaction(State &_s, const Graph::Edge &_e) : s(_s), e(_e) {
      s.depth++;
      auto got = s.resources_avail[e.from.res];
      if(got<e.from.units) return;
      if((wtb = (e.to.res==s.S.gold_id))) {
        if(s.wtb_used&(1ull<<e.offer)) return;
        s.wtb_used |= 1ull<<e.offer;
        s.wtb_used_count++;
        t = 1;
        //info("set bit % (%)",e.offer,s.wtb_used);
      } else {
        t = got/e.from.units;
      }
      s.resources_avail[e.to.res] += e.to.units*t;
      s.resources_avail[e.from.res] -= e.from.units*t;
    }
    INL ~Transaction() {
      s.depth--;
      if(!t) return;
      if(wtb) {
        s.wtb_used &= ~(1ull<<e.offer);
        s.wtb_used_count--;
      }
      s.resources_avail[e.to.res] -= e.to.units*t;
      s.resources_avail[e.from.res] += e.from.units*t; 
    }
  };
};

struct DFS {
  DFS(const Spec &_S, size_t _depth_limit) : state{_S}, depth_limit(_depth_limit) {
    state.resources_avail.resize(_S.names.size(),0);
    state.resources_avail[_S.gold_id] = 10;
  }
  State state;
  
  size_t depth_limit = 0;
  size_t best = 0;
  
  void run() {
    //info("state = %",show(state));
    if(state.wtb_used_count>best) {
      best = state.wtb_used_count;
      info("% % transactions done %",state.wtb_used,state.wtb_used_count,show(state));
    }
    if(state.depth>depth_limit) return;
    auto &trans_nodes = state.S.trans.nodes;
    for(size_t i=state.resources_avail.size();i--;) {
      auto got = state.resources_avail[i];
      if(got==0) continue;
      for(auto &e : trans_nodes[i].out) {
        State::Transaction T(state,e);
        if(!T) continue;
        //info("WTS %",show(e));
        run();
      }
    }
  }
};

int main() {
  util::StreamLogger _(std::cerr);
  Spec S = make_spec();

  /*vec<str> nodes;
  for(auto n : S.wts.op().topo()) nodes.push_back(S.names.lookup_name(n));
  util::info("{ % }",util::join(", ",nodes));
  */

  for(size_t i=100;i<104; i++) {
    info("depth_limit = %",i);
    DFS dfs(S,i);
    dfs.run();
  }

  return 0;
}
