#include "master_summoner.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Minion to its specified base stats
MasterSummoner::MasterSummoner() {
    this->name = "Master Summoner";
    this->cost = 3;
    this->description = "Summon up to three 1/1 air elementals.";
    this->atk = 2;
    this->def = 3;
    this->active_ability_cost = 2;
    this->ability_type = ACTIVE_ABILITY;
    this->ability = SpecialAbilities::master_summoner;
}

// dtor doesnt need to do anything special
MasterSummoner::~MasterSummoner() {}
