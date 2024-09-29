#include "haste.h"
#include "minion.h"
using namespace std;

// ctor constructs the corresponding Enchantment to its specified base stats
Haste::Haste() {
    this->name = "Haste";
    this->cost = 1;
    this->description = "Enchanted minion gains +1 action each turn.";
    this->atk_mod = "";
    this->def_mod = "";
}

// dtor doesnt need to do anything special
Haste::~Haste() {}

// attaches to, and modifies mp
void Haste::attach_enchantment(Minion *mp) {
    mp->actions_per_turn += 1;
}

// detaches from, and modifies mp
void Haste::detach_enchantment(Minion *mp) {
    mp->actions_per_turn -= 1;
}
