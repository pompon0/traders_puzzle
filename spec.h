#ifndef SPEC_H_
#define SPEC_H_

#include "utils/types.h"

namespace spec {

struct Obj {
  str name;
  size_t count;
};

struct Offer {
  Obj obj;
  Obj price;
};

static vec<Offer> WTS() {
  return {
    {{"Healing Potion", 1},{"g", 2}},
    {{"Golden Goblet", 1},{"Hand Axe", 5}},
    {{"Jade Locket", 1}, {"Linen Bandage", 2}},
    {{"Alliance Mace", 1}, {"Stormwind Cheddar", 14}},
    {{"Draught of Angels", 1}, {"Cute Doll", 3}},
    {{"Gilnean Dagger", 1}, {"Shadowy Gem", 2}},
    {{"Loyal Pet Whistle", 1}, {"Elixir of Vigor", 4}},

    {{"Iron Dagger", 1}, {"g", 1}},
    {{"Jade Locket", 1}, {"Stormwind Cheddar", 4}},
    {{"Golden Goblet", 1}, {"Healing Potion", 4}},
    {{"Ruby Crown", 1}, {"Hand Axe", 22}},
    {{"Sphere of Wisdom", 1}, {"Potion of Night", 4}},
    {{"Shadowy Gem", 1}, {"Gnomish Shield",3}},
    {{"Sapphire Wand", 1}, {"Loyal Pet Whistle", 2}},

    {{"Hand Axe", 1}, {"g", 2}},
    {{"Cute Doll", 1}, {"Linen Bandage", 5}},
    {{"Arcane Scroll", 1}, {"Very Nice Hat", 8}},
    {{"Draught of Angels", 1}, {"Angry Crystal", 1}},
    {{"Potion of Night", 1}, {"Jade Locket", 5}},
    {{"Everburning Candle", 1}, {"Goblin Fishing Pole", 4}},
    {{"Tiger Amulet", 1}, {"Captivating Pipes", 5}},

    {{"Captivating Pipes", 1}, {"g", 11}},
    {{"Linen Bandage", 1}, {"Elixir of Vigor", 1}},
    {{"Gilnean Dagger", 1}, {"Healing Potion", 49}},
    {{"Gnomish Shield", 1}, {"Iron Dagger", 12}},
    {{"Potion of Night", 1}, {"Stormwind Cheddar", 13}},
    {{"Tiger Amulet", 1}, {"Arcane Scroll", 3}},
    {{"Alliance Mace", 1}, {"Golden Goblet", 3}},

    {{"Arcane Scroll", 1}, {"g", 25}},
    {{"Very Nice Hat", 1}, {"Hand Axe", 2}},
    {{"Captivating Pipes", 1}, {"Healing Potion", 7}},
    {{"Angry Crystal", 1}, {"Elixir of Vigor", 20}},
    {{"Gilnean Dagger", 1}, {"Sapphire Wand", 2}},
    {{"Sphere of Wisdom", 1}, {"Golden Goblet", 10}},
    {{"Sapphire Wand", 1}, {"Stormwind Cheddar", 15}},

    {{"Elixir of Vigor", 1}, {"g", 3}},
    {{"Goblin Fishing Pole", 1}, {"Hand Axe", 4}},
    {{"Sapphire Wand", 1}, {"Very Nice Hat", 5}},
    {{"Everburning Candle", 1}, {"Alliance Mace", 1}},
    {{"Angry Crystal", 1}, {"Cute Doll", 5}},
    {{"Ruby Crown", 1}, {"Captivating Pipes", 3}},
    {{"Draught of Angels", 1}, {"Golden Goblet", 9}},

    {{"Stormwind Cheddar", 1}, {"g", 2}},
    {{"Goblin Fishing Pole", 1}, {"Stormwind Cheddar", 5}},
    {{"Loyal Pet Whistle", 1}, {"Iron Dagger", 7}},
    {{"Shadowy Gem", 1}, {"Elixir of Vigor", 9}},
    {{"Gilnean Dagger", 1}, {"Ruby Crown", 1}},
    {{"Tiger Amulet", 1}, {"Gnomish Shield", 4}},
    {{"Alliance Mace", 1}, {"Cute Doll", 3}},
  };
}

static vec<Offer> WTB() {
  return {
    {{"g", 10}, {"Hand Axe", 6}},
    {{"g", 18}, {"Goblin Fishing Pole", 2}},
    {{"g", 60}, {"Angry Crystal", 1}},
    {{"g", 138}, {"Arcane Scroll", 6}},
    {{"g", 205}, {"Sphere of Wisdom", 3}},

    {{"g", 18}, {"Cute Doll", 1}},
    {{"g", 25}, {"Stormwind Cheddar", 10}},
    {{"g", 120}, {"Goblin Fishing Pole", 10}},
    {{"g", 92}, {"Ruby Crown", 4}},
    {{"g", 240}, {"Potion of Night", 8}},

    {{"g", 13}, {"Linen Bandage", 3}},
    {{"g", 14}, {"Very Nice Hat", 4}},
    {{"g", 30}, {"Draught of Angels", 1}},
    {{"g", 150}, {"Angry Crystal", 3}},
    {{"g", 166}, {"Cute Doll", 9}},

    {{"g", 11}, {"Jade Locket", 1}},
    {{"g", 42}, {"Captivating Pipes", 6}},
    {{"g", 72}, {"Ruby Crown", 2}},
    {{"g", 114}, {"Tiger Amulet", 2}},
    {{"g", 125}, {"Sapphire Wand", 10}},

    {{"g", 6}, {"Iron Dagger", 3}},
    {{"g", 70}, {"Gilnean Dagger", 1}},
    {{"g", 50}, {"Captivating Pipes", 4}},
    {{"g", 125}, {"Alliance Mace", 5}},
    {{"g", 166}, {"Shadowy Gem", 7}},

    {{"g", 15}, {"Elixir of Vigor", 10}},
    {{"g", 25}, {"Gnomish Shield", 2}},
    {{"g", 65}, {"Golden Goblet", 7}},
    {{"g", 70}, {"Alliance Mace", 4}},
    {{"g", 180}, {"Everburning Candle", 7}},

    {{"g", 10}, {"Healing Potion", 8}},
    {{"g", 22}, {"Loyal Pet Whistle", 3}},
    {{"g", 70}, {"Arcane Scroll", 2}},
    {{"g", 60}, {"Gnomish Shield", 7}},
    {{"g", 204}, {"Draught of Angels", 4}}
  };
}

} // namespace spec

#endif  // SPEC_H_
