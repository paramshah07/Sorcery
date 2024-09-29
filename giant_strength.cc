#include "giant_strength.h"
#include "minion.h"

using namespace std;

// ctor constructs the corresponding Enchantment to its specified base stats
GiantStrength::GiantStrength() {
    this->name = "Giant Strength";
    this->cost = 1;
    this->description = "";
    this->atk_mod = "+2";
    this->def_mod = "+2";
}

// dtor doesnt need to do anything special
GiantStrength::~GiantStrength() {}

// attaches to, and modifies mp
void GiantStrength::attach_enchantment(Minion *mp) {
    mp->atk += 2;
    mp->def += 2;
}

// detaches from, and modifies mp
void GiantStrength::detach_enchantment(Minion *mp) {
    mp->atk -= 2;
    mp->def -= 2;
}
