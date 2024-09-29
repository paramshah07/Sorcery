#include "novice_pyromancer.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Minion to its specified base stats
NovicePyromancer::NovicePyromancer() {
    this->name = "Novice Pyromancer";
    this->cost = 1;
    this->description = "Deal 1 damage to target minion.";
    this->atk = 0;
    this->def = 1;
    this->active_ability_cost = 1;
    this->ability_type = ACTIVE_ABILITY;
    this->ability = SpecialAbilities::novice_pyromancer;
}

// dtor doesnt need to do anything special
NovicePyromancer::~NovicePyromancer() {}
