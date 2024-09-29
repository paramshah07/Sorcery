#include <iostream>
#include "spell.h"
#include "special_abilities.h"

using namespace std;

Spell::~Spell() {}

bool Spell::use_ablility(
    int pnum, int owner, int index, int targetPlayer, int targetIndex, int type
) {
    // do nothing if the wrong type of ability is called
    if (type != this->ability_type) return false;

    // trigger the ability of the Spell
    if(!ability(pnum, owner, index, targetPlayer, targetIndex)) return false;

    return true;
}
