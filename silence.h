#ifndef _SILENCE_H_
#define _SILENCE_H_

#include <string>
#include "enchantment.h"

// concrete baseclass Silence
class Silence: public Enchantment {
  public:
    Silence();
    ~Silence();

    void attach_enchantment(Minion *mp) override;
    void detach_enchantment(Minion *mp) override;
};

#endif
