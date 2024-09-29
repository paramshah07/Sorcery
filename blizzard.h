#ifndef _BLIZZARD_H_
#define _BLIZZARD_H_

#include <string>
#include "spell.h"

// concrete baseclass Blizzard
class Blizzard: public Spell {
  public:
    Blizzard();
    ~Blizzard();
};

#endif
