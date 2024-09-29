#ifndef _GIANT_STRENGTH_H_
#define _GIANT_STRENGTH_H_

#include <string>
#include "enchantment.h"

// concrete baseclass GiantStrength
class GiantStrength: public Enchantment {
  public:
    GiantStrength();
    ~GiantStrength();

    void attach_enchantment(Minion *mp) override;
    void detach_enchantment(Minion *mp) override;
};

#endif
