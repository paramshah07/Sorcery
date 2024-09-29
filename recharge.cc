#include "recharge.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Spell to its specified base stats
Recharge::Recharge() {
    this->name = "Recharge";
    this->cost = 1;
    this->description = "Your ritual gains 3 charges.";
    this->ability = SpecialAbilities::recharge;
}

// dtor doesnt need to do anything special
Recharge::~Recharge() {}
