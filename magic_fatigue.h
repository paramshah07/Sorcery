#ifndef _MAGIC_FATIGUE_H_
#define _MAGIC_FATIGUE_H_

#include <string>
#include "enchantment.h"

// concrete baseclass MagicFatigue
class MagicFatigue: public Enchantment {
  public:
    MagicFatigue();
    ~MagicFatigue();

    void attach_enchantment(Minion *mp) override;
    void detach_enchantment(Minion *mp) override;
};

#endif
