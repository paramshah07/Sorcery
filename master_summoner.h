#ifndef _MASTER_SUMMONER_H_
#define _MASTER_SUMMONER_H_

#include <string>
#include "minion.h"

// concrete baseclass MasterSummoner
class MasterSummoner: public Minion {
  public:
    MasterSummoner();
    ~MasterSummoner();
};

#endif
