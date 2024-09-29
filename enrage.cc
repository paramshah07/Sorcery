#include "enrage.h"
#include "minion.h"

using namespace std;

// ctor constructs the corresponding Enchantment to its specified base stats
Enrage::Enrage() {
    this->name = "Enrage";
    this->cost = 2;
    this->description = "";
    this->atk_mod = "*2";
    this->def_mod = "*2";
}

// dtor doesnt need to do anything special
Enrage::~Enrage() {}

// attaches to, and modifies mp
void Enrage::attach_enchantment(Minion *mp) {
    mp->atk *= 2;
    mp->def *= 2;
}

// detaches from, and modifies mp
void Enrage::detach_enchantment(Minion *mp) {
    mp->atk /= 2;
    mp->def /= 2;
}
