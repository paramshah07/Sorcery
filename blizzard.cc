#include "blizzard.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Spell to its specified base stats
Blizzard::Blizzard() {
    this->name = "Blizzard";
    this->cost = 3;
    this->description = "Deal 2 damage to all minions.";
    this->ability = SpecialAbilities::blizzard;
}

// dtor doesnt need to do anything special
Blizzard::~Blizzard() {}
