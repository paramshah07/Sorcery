#ifndef _CARD_H_
#define _CARD_H_

#include <string>
#include "special_abilities.h"

// abstract superclass Card
class Card {
  protected:
    std::string name;
    int cost;
    std::string description;
    // Every Card will HAVE a function pointer that points to the
    // function that performs the effects of their ability.
    // This field defaults to nullptr for Cards without abilities.
    bool (*ability)(int, int, int, int, int) = nullptr;
    // each Card's ability is classified into one of five types,
    // specified in special_abilities.h. Cards with no ability defaults
    // to NO_ABILITY
    int ability_type = NO_ABILITY;

  public:
    virtual ~Card() = 0;

    std::string get_name() const;
    int get_cost() const;
    std::string get_desc() const;

    // each Card will have a slightly different implementation to this
    // (like different activation conditions, etc)
    virtual bool use_ablility(
        int pnum, int owner, int index, int targetPlayer, int targetIndex, 
        int type) = 0;
    
    // gets the function pointer
    bool (*get_ability() const)(int, int, int, int, int);
};

#endif
