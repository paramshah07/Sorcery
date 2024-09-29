#ifndef _POTION_SELLER_H_
#define _POTION_SELLER_H_

#include <string>
#include "minion.h"

// concrete baseclass PotionSeller
class PotionSeller: public Minion {
  public:
    PotionSeller();
    ~PotionSeller();
};

#endif
