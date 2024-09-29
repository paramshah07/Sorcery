#ifndef _RECHARGE_H_
#define _RECHARGE_H_

#include <string>
#include "spell.h"

// concrete baseclass Recharge
class Recharge: public Spell {
  public:
    Recharge();
    ~Recharge();
};

#endif
