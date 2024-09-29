#ifndef _ENRAGE_H_
#define _ENRAGE_H_

#include <string>
#include "enchantment.h"

// concrete baseclass Enrage
class Enrage: public Enchantment {
  public:
    Enrage();
    ~Enrage();

    void attach_enchantment(Minion *mp) override;
    void detach_enchantment(Minion *mp) override;
};

#endif
