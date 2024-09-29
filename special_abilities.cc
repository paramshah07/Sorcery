#include <iostream>
#include "special_abilities.h"
#include "player.h"
#include "card.h"
#include "minion.h"
#include "ritual.h"
#include "enchantment.h"
#include "spell.h"
#include "air_elemental.h"

using namespace std;

SpecialAbilities::~SpecialAbilities() {}

void SpecialAbilities::set_board(Board *b) {
    board = b;
}

// bone golem gains +1/+1 upon ability trigger
// does not effect the target Minion
bool SpecialAbilities::bone_golem(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // target minion is this minion. The targetPlayer and targetIndex fields
    // are irrelevant since bone golem's ability affects only itself
    Minion *targetMinion = dynamic_cast<Minion *>(
        board->get_minions(owner)->at(index));
    
    targetMinion->atk += 1;
    targetMinion->def += 1;

    return true;
}

// fire elemental deals 1 damage to entering enemy minion
bool SpecialAbilities::fire_elemental(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // check if (targetPlayer, targetIndex) is valid index
    if (targetPlayer > 2 || targetPlayer < 1) return false;
    if (targetIndex >= board->get_minions(targetPlayer)->size() || 
        targetIndex < 0) return false;
    
    // target minion is the target passed in parameters
    Minion *targetMinion = dynamic_cast<Minion *>(
        board->get_minions(targetPlayer)->at(targetIndex));
    
    // only damages opponent minions on entry
    if (owner != targetPlayer) {
        targetMinion->def -= 1;
    }

    // this ability can potentially cause minions to leave play, so we check
    // on_minion_leave()
    board->on_minion_leave(pnum);

    return true;
}

// potion seller gives all friendly minions +0/+1 at the end of each turn
bool SpecialAbilities::potion_seller(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // target minion is every friendly minion
    for (int i = 0; i < board->get_minions(owner)->size(); ++i) {
        Minion *targetMinion = dynamic_cast<Minion *>(
            board->get_minions(owner)->at(i));
        targetMinion->def += 1;
    }

    return true;
}

// novice pyromancer deals 1 damage with active ability to a target minion
bool SpecialAbilities::novice_pyromancer(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) { 
    // special case: this ability was used to target a Player.
    if (targetPlayer == 1000 && targetIndex == 1000) {
        int pOther;
        if (pnum == 1) { pOther = 2; } 
        else if (pnum == 2) { pOther = 1; }
        else { cerr << "Invalid pnum | novice_pyromancer() | special_abilities.cc" << endl; }
        board->access_player(pOther)->receive_damage(1);
        return true;
    }

    // check for valid target minion
    if (targetIndex >= board->get_minions(targetPlayer)->size()) return false;

    // target minion is the specified target minion
    Minion *targetMinion = dynamic_cast<Minion *>(
        board->get_minions(targetPlayer)->at(targetIndex));
    
    targetMinion->def -= 1;

    // this ability can potentially cause minions to leave play, so we check
    // on_minion_leave()
    board->on_minion_leave(pnum);

    return true;
}

// apprentice summoner summons a 1/1 air elemental with active ability
bool SpecialAbilities::apprentice_summoner(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // if owner's minion field is not full, summon a new AirElemental
    if (board->get_minions(owner)->size() < 5) {
        Card *summoned = new AirElemental;
        board->get_minions(owner)->emplace_back(summoned);
    }

    // this ability can potentially cause minions to enter play, so we check
    // on_minion_entry()
    board->on_minion_entry(pnum, owner, board->get_minions(owner)->size()-1);

    return true;
}

// master summoner summons up to 3 1/1 air elementals with active ability
bool SpecialAbilities::master_summoner(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // keeps summoning until either 3 are summoned or playing field
    // is full
    int numSummoned = 0;
    while (board->get_minions(owner)->size() < 5 && numSummoned < 3) {
        Card *summoned = new AirElemental;
        board->get_minions(owner)->emplace_back(summoned);
        // this ability can potentially cause minions to enter play, so we check
        // on_minion_entry()
        board->on_minion_entry(pnum, owner, board->get_minions(owner)->size()-1);
        ++numSummoned;
    }

    return true;
}

// spell that destroys target minion or ritual
bool SpecialAbilities::banish(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // check for valid target
    if (targetPlayer > 2 || targetPlayer < 1) return false;
    if ((targetIndex >= board->get_minions(targetPlayer)->size() || targetIndex < 0)
         && targetIndex != 65) return false;

    // need to parse the index for a ritual, which is 'r'-'0'-1 == 65
    if (targetIndex == 65) {
        Ritual *targetRitual = dynamic_cast<Ritual *>(
            board->get_ritual(targetPlayer));
        delete targetRitual;

        // make sure to set ritual slot back to nullptr (no dangling!!)
        if (targetPlayer == 1) {
            board->ritual1 = nullptr;
        } else if (targetPlayer == 2) {
            board->ritual2 = nullptr;
        } else {
            cerr << "Invalid player targeted | SpecialAbilities::banish | \
special_abilities.cc" << endl;
        }
    } else {
        // target minion is the specified target minion
        Minion *targetMinion = dynamic_cast<Minion *>(
            board->get_minions(targetPlayer)->at(targetIndex));

        // must delete all Enchantments attached to target Minion
        for (int i = 0; i < targetMinion->enchants.size(); ++i) {
            delete targetMinion->enchants.at(i);
        }
        // set target minion health to -10000 as a special interaction
        targetMinion->def = -10000; 

        // this ability can potentially cause minions to leave play, so we check
        // on_minion_leave() while providing the leaving minion
        board->on_minion_leave(pnum, targetPlayer, targetIndex);
    }
    return true;
}

// spell that returns the target minion to owner's hand
bool SpecialAbilities::unsummon(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) { 
    // check for valid target
    if (targetPlayer > 2 || targetPlayer < 1) return false;
    if (targetIndex >= board->get_minions(targetPlayer)->size() || 
        targetIndex < 0) return false;

    // target minion is the specified target minion
    Minion *targetMinion = dynamic_cast<Minion *>(
        board->get_minions(targetPlayer)->at(targetIndex));
    
    // First, destroy all enchantments on the minion
    // We do this by detaching all Enchantments on the target minion in reverse
    // order (calling their detach() function) and then deleting them
    // and popping them out of minion's vector of enchantments
    for (int i = targetMinion->enchants.size()-1; i >= 0; --i) {
        targetMinion->enchants.at(i)->detach_enchantment(targetMinion);
        delete targetMinion->enchants.at(i);
        targetMinion->enchants.pop_back();
    }

    // at this point, after removing the enchants, we can let
    // on_minion_leave() handle the rest of the work
    // (moving to graveyard / hand / deck)
    board->on_minion_leave(pnum, targetPlayer, targetIndex);

    return true;
}

// Spell that increases self's ritual's charges by 3
bool SpecialAbilities::recharge(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    Ritual *targetRitual = dynamic_cast<Ritual *>(
        board->get_ritual(owner));
    
    // if cast was successful (not nullptr)
    if(targetRitual) targetRitual->num_charges += 3;

    return true;
}

// Spell that destroy's the top enchantment on target minion
bool SpecialAbilities::disenchant(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // check for valid target
    if (targetPlayer > 2 || targetPlayer < 1) return false;
    if (targetIndex >= board->get_minions(targetPlayer)->size() || 
        targetIndex < 0) return false;
    
    // target minion is the specified target minion
    Minion *targetMinion = dynamic_cast<Minion *>(
        board->get_minions(targetPlayer)->at(targetIndex));
    
    // do nothing if the minion has no enchants
    if (targetMinion->enchants.size() == 0) return true;
    
    // call the disenchant function on the top enchantment on the minion
    targetMinion->enchants.back()->detach_enchantment(targetMinion);
    // then delete the enchantment
    delete targetMinion->enchants.back();
    // remove the pointer from the vector of enchants
    targetMinion->enchants.pop_back();

    // minion is potentially dead after removing the enchant, so we
    // need to perform neccessary follow-up actions
    if (targetMinion->def <= 0) {
        // if dead, need to destroy all enchantments on it and move it
        // to graveyard
        for (int i = targetMinion->enchants.size()-1; i >= 0; --i) {
            targetMinion->enchants.at(i)->detach_enchantment(targetMinion);
            delete targetMinion->enchants.at(i);
            targetMinion->enchants.pop_back();
        }
        // leave it to on_minion_leave() to process the minion's death
        board->on_minion_leave(pnum, targetPlayer, targetIndex);
    }
    return true;
}

// resurrect the tip minion in player's graveyard and and set its def to 1
bool SpecialAbilities::raise_dead(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // do nothing if theres no minion in graveyard
    if (board->get_grave(owner)->size() == 0) return true;

    // target minion is the top of the graveyard
    Minion *targetMinion = dynamic_cast<Minion *>(
        board->get_grave(owner)->back());

    targetMinion->def = 1;

    // if hand of target player is full, we still return to hand since the
    // raise dead spell card will dissapear from the hand which will
    // make space anyways
    board->access_player(owner)->get_hand()->emplace_back(targetMinion);

    // remove the minion from graveyard
    board->get_grave(owner)->pop_back();

    return true;
}

bool SpecialAbilities::blizzard(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // Note that the APNAP order is implemented already in the
    // on_minion_leave() method so it doesnt really matter which minion
    // takes damage first here.
    // we'll damage pnum's minions first
    for (int i = 0; i < board->get_minions(pnum)->size(); ++i) {
        Minion *mp = dynamic_cast<Minion *>(board->get_minions(pnum)->at(i));
        mp->def -= 2;
    }

    int pOther;
    if (pnum == 1) { pOther = 2; } 
    else if (pnum == 2) { pOther = 1; }
    else { cerr << "Invalid pnum | on_minion_leave() | board.cc" << endl; }

    // then damage p2's minions
    for (int i = 0; i < board->get_minions(pOther)->size(); ++i) {
        Minion *mp = dynamic_cast<Minion *>(board->get_minions(pOther)->at(i));
        mp->def -= 2;
    }

    // at the end, since blizzard can cause minions to die, we call 
    // on_minion_leave(), and it will scan through each minion death
    // and call approporiate death trigger abilities
    board->on_minion_leave(pnum);

    return true;
}

// At the start of your turn, gain 1 mana
bool SpecialAbilities::dark_ritual(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // triggers only when its the turn of the owner of this Card
    if (pnum == owner) board->access_player(owner)->gain_mana(1);
}

// Whenever a minion enters play under your control, it gains +1/+1
bool SpecialAbilities::aura_of_power(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // target minion is the specified target minion
    Minion *targetMinion = dynamic_cast<Minion *>(
        board->get_minions(targetPlayer)->at(targetIndex));
    
    // do nothing if entering minion is not the owner's
    if (targetPlayer = owner) {
        targetMinion->atk += 1;
        targetMinion->def += 1;
    }

    return true;
}

// Whenever a minion enters play, destroy it
bool SpecialAbilities::standstill(
    int pnum, int owner, int index, int targetPlayer, int targetIndex
) {
    // check if (targetPlayer, targetIndex) is valid index
    if (targetPlayer > 2 || targetPlayer < 1) return false;
    if (targetIndex >= board->get_minions(targetPlayer)->size() || 
        targetIndex < 0) return false;
        
    // target minion is the specified target minion
    Minion *targetMinion = dynamic_cast<Minion *>(
        board->get_minions(targetPlayer)->at(targetIndex));

    // must delete all Enchantments attached to target Minion
    for (int i = 0; i < targetMinion->enchants.size(); ++i) {
        delete targetMinion->enchants.at(i);
    }
    // set target minion health to -10000 as a special interaction
    targetMinion->def = -10000; 

    // this ability can potentially cause minions to leave play, so we check
    // on_minion_leave() while providing the leaving minion
    board->on_minion_leave(pnum, targetPlayer, targetIndex);

    return true;
}
