#include "earth_elemental.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Minion to its specified base stats
EarthElemental::EarthElemental() {
    this->name = "Earth Elemental";
    this->cost = 3;
    this->description = "";
    this->atk = 4;
    this->def = 4;
    this->ability_type = NO_ABILITY;
}

// dtor doesnt need to do anything special
EarthElemental::~EarthElemental() {}
