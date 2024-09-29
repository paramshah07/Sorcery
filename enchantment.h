#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_

#include <string>
#include "card.h"
#include "special_abilities.h"

class Minion;

// abstract superclass for all Enchantment Cards
class Enchantment: public Card {
  protected:
    // I kinda had no better idea how I could display the enchantment
    // stat modifiers other than add more fields
    std::string atk_mod;
    std::string def_mod;

    // in addition to having its own ability and type, enchantments also 
    // keep track of the ability that applying this enchantment would 
    // override, as well as the costs of both old/new abilities 
    // (if they are active abilities)
    bool (*prev_ability)(int, int, int, int, int) = nullptr;
    int prev_ability_type = NO_ABILITY;
    
    int prev_active_ability_cost = -1;
    int active_ability_cost = -1;
    
  public:
    virtual ~Enchantment();

    std::string get_atk_mod() const;
    std::string get_def_mod() const;
    
    // these will need to be heavily overrided in each concrete baseclass
    virtual void attach_enchantment(Minion *mp) = 0;
    virtual void detach_enchantment(Minion *mp) = 0;

    bool use_ablility(
        int pnum, int owner, int index, int targetPlayer, int targetIndex, 
        int type) override;
};

#endif
