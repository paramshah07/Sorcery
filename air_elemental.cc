#include "air_elemental.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Minion to its specified base stats
AirElemental::AirElemental() {
    this->name = "Air Elemental";
    this->cost = 0;
    this->description = "";
    this->atk = 1;
    this->def = 1;
    this->ability_type = NO_ABILITY;
}

// dtor doesnt need to do anything special
AirElemental::~AirElemental() {}
