#ifndef _HASTE_H_
#define _HASTE_H_

#include <string>
#include "enchantment.h"

// concrete baseclass Haste
class Haste: public Enchantment {
  public:
    Haste();
    ~Haste();

    void attach_enchantment(Minion *mp) override;
    void detach_enchantment(Minion *mp) override;
};

#endif
