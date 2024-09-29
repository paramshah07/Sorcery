#ifndef _BANISH_H_
#define _BANISH_H_

#include <string>
#include "spell.h"

// concrete baseclass Banish
class Banish: public Spell {
  public:
    Banish();
    ~Banish();
};

#endif
