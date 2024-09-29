#include "apprentice_summoner.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Minion to its specified base stats
ApprenticeSummoner::ApprenticeSummoner() {
    this->name = "Apprentice Summoner";
    this->cost = 1;
    this->description = "Summon a 1/1 air elemental.";
    this->atk = 1;
    this->def = 1;
    this->active_ability_cost = 1;
    this->ability_type = ACTIVE_ABILITY;
    this->ability = SpecialAbilities::apprentice_summoner;
}

// dtor doesnt need to do anything special
ApprenticeSummoner::~ApprenticeSummoner() {}
