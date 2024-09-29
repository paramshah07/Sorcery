#ifndef _AURA_OF_POWER_H_
#define _AURA_OF_POWER_H_

#include <string>
#include "ritual.h"

// concrete baseclass AuraOfPower
class AuraOfPower: public Ritual {
  public:
    AuraOfPower();
    ~AuraOfPower();

    bool use_ablility(
        int pnum, int owner, int index, int targetPlayer, int targetIndex, int type
    ) override;
};

#endif
