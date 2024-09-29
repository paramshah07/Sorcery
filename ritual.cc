#include "ritual.h"

Ritual::~Ritual() {}

int Ritual::get_ritual_cost() const {
    return this->ritual_cost;
}

int Ritual::get_num_charges() const {
    return this->num_charges;
}

bool Ritual::use_ablility(
    int pnum, int owner, int index, int targetPlayer, int targetIndex, int type
) {
    // do nothing if the wrong type of ability is called
    if (type != this->ability_type) return false;

    // do nothing if the ritual has insifficient charges
    if (this->num_charges < this->ritual_cost) return false;

    // trigger the ability of the Ritual 
    if (!ability(pnum, owner, index, targetPlayer, targetIndex)) return false;
    
    // lower the charges of this Ritual by the cost
    this->num_charges -= this->ritual_cost;

    return true;
}
