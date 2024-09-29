#include "banish.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Spell to its specified base stats
Banish::Banish() {
    this->name = "Banish";
    this->cost = 2;
    this->description = "Destroy target minion or ritual.";
    this->ability = SpecialAbilities::banish;
}

// dtor doesnt need to do anything special
Banish::~Banish() {}
