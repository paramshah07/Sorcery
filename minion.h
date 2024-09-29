#ifndef _MINION_H_
#define _MINION_H_

#include <vector>
#include <string>
#include "card.h"
#include "board.h"

class Enchantment;
class Player;

// abstract superclass Minion that inherits Card
class Minion: public Card {
    friend class SpecialAbilities;
    // probably not the best to create a bunch of friend classes but I cant 
    // think of anything better (other than creating a bunch of setters which
    // would make these private fields pointless anyway)
    friend class GiantStrength;
    friend class Enrage;
    friend class Haste;
    friend class MagicFatigue;
    friend class Silence;
    // minion has all of Card's fields and methods as well as the following:
  protected:
    int atk;
    int def;
    // minions with no active ability will have their active ability cost
    // set to -1 by default
    int active_ability_cost = -1;
    // We'll specify default values here because I'm lazy to put them
    // individually into the ctors of each concrete class.
    // Obviously these are the same defaults for every Minion
    int action_counter = 0;
    int actions_per_turn = 1;
    // every Minion will OWN a vector of Enchatment *s to keep track of
    // the enchantments that it is under (responsible for delete)
    std::vector<Enchantment *> enchants;

  public:
    virtual ~Minion() = 0;

    int get_atk() const;
    int get_def() const;
    int get_ability_cost() const;
    int get_actions() const;
    std::vector<Enchantment *> *get_enchants();

    void reset_actions();
    void attack_player(Player *p);
    void attack_minion(Minion *other);
    virtual bool use_ablility(
        int pnum, int owner, int index, int targetPlayer, int targetIndex, 
        int type) override;
    void attach_enchantment(Enchantment *enchant);
    void detach_enchantment();
};

#endif
