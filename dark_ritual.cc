#include <iostream>
#include "dark_ritual.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Ritual to its specified base stats
DarkRitual::DarkRitual() {
    this->name = "Dark Ritual";
    this->cost = 0;
    this->description = "At the start of your turn, gain 1 mana.";
    this->ritual_cost = 1;
    this->num_charges = 5;
    this->ability = SpecialAbilities::dark_ritual;
    this->ability_type = ON_TURN_START;
}

// dtor doesnt need to do anything special
DarkRitual::~DarkRitual() {}

bool DarkRitual::use_ablility(
    int pnum, int owner, int index, int targetPlayer, int targetIndex, int type
) {
    // do nothing if the wrong type of ability is called
    if (type != this->ability_type) return false;

    // do nothing if its not the start of YOUR turn (ie oppoents turn)
    if (pnum != owner) return false;

    // do nothing if the ritual has insifficient charges
    if (this->num_charges < this->ritual_cost) return false;

    // trigger the ability of the Minion (the enchantments will modify the
    // ability of the minion when attached if applicable)
    ability(pnum, owner, index, targetPlayer, targetIndex);
    
    // lower the charges of this Ritual by the cost
    this->num_charges -= this->ritual_cost;

    return true;
}
