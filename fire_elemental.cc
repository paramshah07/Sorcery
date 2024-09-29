#include <iostream>
#include "fire_elemental.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Minion to its specified base stats
FireElemental::FireElemental() {
    this->name = "Fire Elemental";
    this->cost = 2;
    this->description = "Whenever an opponent's minion enters play, deal 1 damage to it.";
    this->atk = 2;
    this->def = 2;
    this->ability_type = ON_MINION_ENTRY;
    this->ability = SpecialAbilities::fire_elemental;
}

// dtor doesnt need to do anything special
FireElemental::~FireElemental() {}
