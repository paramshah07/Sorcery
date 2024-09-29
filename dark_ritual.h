#ifndef _DARK_RITUAL_H_
#define _DARK_RITUAL_H_

#include <string>
#include "ritual.h"

// concrete baseclass DarkRitual
class DarkRitual: public Ritual {
  public:
    DarkRitual();
    ~DarkRitual();

    bool use_ablility(
        int pnum, int owner, int index, int targetPlayer, int targetIndex, int type
    ) override;
};

#endif
