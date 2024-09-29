#include "disenchant.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Spell to its specified base stats
Disenchant::Disenchant() {
    this->name = "Disenchant";
    this->cost = 1;
    this->description = "Destroy the top enchantment on target minion.";
    this->ability = SpecialAbilities::disenchant;
}

// dtor doesnt need to do anything special
Disenchant::~Disenchant() {}
