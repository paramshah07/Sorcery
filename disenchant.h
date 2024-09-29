#ifndef _DISENCHANT_H_
#define _DISENCHANT_H_

#include <string>
#include "spell.h"

// concrete baseclass Disenchant
class Disenchant: public Spell {
  public:
    Disenchant();
    ~Disenchant();
};

#endif
