#ifndef _SPELL_H_
#define _SPELL_H_

#include <string>
#include "card.h"
#include "special_abilities.h"

// abstract superclass Spell that inherits Card
class Spell: public Card {
    int ability_type = ACTIVE_ABILITY;
  public:
    virtual ~Spell() = 0;

    virtual bool use_ablility(
        int pnum, int owner, int index, int targetPlayer, int targetIndex, 
        int type);
};

#endif
