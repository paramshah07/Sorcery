#include "unsummon.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Spell to its specified base stats
Unsummon::Unsummon() {
    this->name = "Unsummon";
    this->cost = 1;
    this->description = "Return target minion to its owner's hand.";
    this->ability = SpecialAbilities::unsummon;
}

// dtor doesnt need to do anything special
Unsummon::~Unsummon() {}
