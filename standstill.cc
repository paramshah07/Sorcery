#include "standstill.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Ritual to its specified base stats
Standstill::Standstill() {
    this->name = "Standstill";
    this->cost = 3;
    this->description = "Whenever a minion enters play, destroy it.";
    this->ritual_cost = 2;
    this->num_charges = 4;
    this->ability = SpecialAbilities::standstill;
    this->ability_type = ON_MINION_ENTRY;
}

// dtor doesnt need to do anything special
Standstill::~Standstill() {}
