#ifndef _RAISE_DEAD_H_
#define _RAISE_DEAD_H_

#include <string>
#include "spell.h"

// concrete baseclass RaiseDead
class RaiseDead: public Spell {
  public:
    RaiseDead();
    ~RaiseDead();
};

#endif
