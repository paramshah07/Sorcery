#include "aura_of_power.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Ritual to its specified base stats
AuraOfPower::AuraOfPower() {
    this->name = "Aura Of Power";
    this->cost = 1;
    this->description = "Whenever a minion enters play under your control, it gains +1/+1.";
    this->ritual_cost = 1;
    this->num_charges = 4;
    this->ability = SpecialAbilities::aura_of_power;
    this->ability_type = ON_MINION_ENTRY;
}

// dtor doesnt need to do anything special
AuraOfPower::~AuraOfPower() {}

bool AuraOfPower::use_ablility(
    int pnum, int owner, int index, int targetPlayer, int targetIndex, int type
) {
    // do nothing if the wrong type of ability is called
    if (type != this->ability_type) return false;

    // do nothing if the entering minion is not the owner's
    if (targetPlayer != owner) return false;

    // do nothing if the ritual has insifficient charges
    if (this->num_charges < this->ritual_cost) return false;

    // trigger the ability of the Minion (the enchantments will modify the
    // ability of the minion when attached if applicable)
    ability(pnum, owner, index, targetPlayer, targetIndex);
    
    // lower the charges of this Ritual by the cost
    this->num_charges -= this->ritual_cost;

    return true;
}
