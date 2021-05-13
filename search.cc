#include "spec.h"
#include "utils/types.h"
#include "utils/log.h"
#include "utils/string.h"
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
  size_t size(){ return name_to_id.size(); }
private:
  std::map<str,ResourceID> name_to_id;
  std::map<ResourceID,str> id_to_name;
};

struct Graph {
  struct End { ResourceID res; Units units; };
  struct Edge { End from,to; OfferID offer; };
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
  Graph wtb,wts; 
};

static Spec make_spec() {
  auto wts = spec::WTS();
  auto wtb = spec::WTS();
  Spec S;
  for(auto offer : wts) {
    S.names.lookup(offer.obj.name);
    S.names.lookup(offer.price.name);
  }
  for(auto offer : wtb) {
    S.names.lookup(offer.obj.name);
    S.names.lookup(offer.price.name);
  }

  S.gold_id = S.names.lookup("g");
  S.wts.nodes.resize(S.names.size());
  S.wtb.nodes.resize(S.names.size());
  S.wts_offers = wts.size();
  S.wtb_offers = wtb.size();

  for(size_t i=0; i<wts.size(); i++) {
    S.wts.add(Graph::Edge{
      .from = {.res = S.names.lookup(wts[i].price.name), .units = wts[i].price.count},
      .to = {.res = S.names.lookup(wts[i].obj.name), .units = wts[i].obj.count},
      .offer = i,
    });
  }
  for(size_t i=0; i<wtb.size(); i++) {
    S.wtb.add(Graph::Edge{
      .from = {.res = S.names.lookup(wtb[i].price.name), .units = wtb[i].price.count},
      .to = {.res = S.names.lookup(wtb[i].obj.name), .units = wtb[i].obj.count},
      .offer = i,
    });
  }
  return S;
}


struct State {
  Spec &S;
  vec<uint64_t> resources_avail;
  uint64_t wtb_used = 0;

  struct Transaction {
    State &s;
    Graph::Edge e;
    Units t = 0;
    bool wtb;
    operator bool(){ return t; }
    Transaction(State &_s, Graph::Edge _e) : s(_s), e(_e) {
      wtb = (e.to.res==s.S.gold_id);
      if(wtb) {
        if((s.wtb_used>>e.offer)&1) return;
        s.wtb_used |= 1<<e.offer;
      }
      t = s.resources_avail[e.from.res]/e.from.units;
      s.resources_avail[e.to.res] += e.to.units*t;
      s.resources_avail[e.from.res] -= e.from.units*t;
    }
    ~Transaction() {
      if(wtb) s.wtb_used ^= 1<<e.offer;
      s.resources_avail[e.to.res] -= e.to.units*t;
      s.resources_avail[e.from.res] += e.from.units*t; 
    }
  };
};

struct DFS {
  DFS(Spec &_S, size_t _depth_limit) : state{_S}, depth_limit(_depth_limit) {
    state.resources_avail.resize(_S.names.size());
    state.resources_avail[_S.gold_id] = 10;
  }
  State state;
  
  size_t depth_limit = 0;
  size_t best = 0;
  
  void run() {
    for(size_t i=0; i<state.resources_avail.size(); i++) {
      auto got = state.resources_avail[i];
      if(got==0) continue;
      for(auto &e : state.S.wts.nodes[i].out) {
        State::Transaction T(state,e);
        if(!T) continue;
        run();
      }
      for(auto &e : state.S.wtb.nodes[i].out) {
        State::Transaction T(state,e);
        if(!T) continue;
        run();
      }
    }
  }
};

int main() {
  util::StreamLogger _(std::cerr);
  Spec S = make_spec();

  vec<str> nodes;
  for(auto n : S.wts.op().topo()) nodes.push_back(S.names.lookup_name(n));
  util::info("{ % }",util::join(", ",nodes));

  return 0;
}
