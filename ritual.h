#ifndef _RITUAL_H_
#define _RITUAL_H_

#include <string>
#include "card.h"

// abstract superclass Ritual that inherits Card
class Ritual: public Card {
    friend class SpecialAbilities;
  protected:
    int ritual_cost;
    int num_charges;

  public:
    virtual ~Ritual() = 0;

    int get_ritual_cost() const;
    int get_num_charges() const;

    virtual bool use_ablility(
        int pnum, int owner, int index, int targetPlayer, int targetIndex, int type
    );
};

#endif
