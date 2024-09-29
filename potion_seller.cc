#include <iostream>
#include "potion_seller.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Minion to its specified base stats
PotionSeller::PotionSeller() {
    this->name = "Potion Seller";
    this->cost = 2;
    this->description = "At the end of your turn, all your minions gain +0/+1.";
    this->atk = 1;
    this->def = 3;
    this->ability_type = ON_TURN_START;
    this->ability = SpecialAbilities::potion_seller;
}

// dtor doesnt need to do anything special
PotionSeller::~PotionSeller() {}
