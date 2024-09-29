#ifndef _SPECIAL_ABILITIES_H_
#define _SPECIAL_ABILITIES_H_

#include <vector>
#include <string>
#include "board.h"

// ability types:
const int ACTIVE_ABILITY = 0;
const int ON_TURN_START = 1;
const int ON_TURN_END = 2;
const int ON_MINION_ENTRY = 3;
const int ON_MINION_EXIT = 4;
const int NO_ABILITY = 5;

// Pure virtual class that exists only to implement all special abilities in 
// the game (via static methods)
// Unfortunately, this implementations would "limit the number of games that
// can be played simultaneously" to one (because theres only one instance of 
// static fields) but the project doesnt require multiple games
// to run in parralell so we are good :)
class SpecialAbilities {
    // the defined abilities will modify the board (cards on the board)
    static Board *board;
  public:
    virtual ~SpecialAbilities() = 0;
    static void set_board(Board *b);

    // Implementation Logic:

    // Whenever a Minion is played (via "play" command or summoned by spell-- 
    // currently these are the only two ways that a minion can enter play so
    // we will do this check manually in game_controller.cc),
    // we scan the entire board and activate all Cards that have a
    // "Whenever a minion enters play" trigger effect, passing in the entering
    // minion as the "target". It is the responsibility of each of those 
    // abilities to determine whether their effect applies to the target Minion
    // or not.

    // With similar logic, whenever a Minion exits play (defeated after def
    // reaches 0, returned by a spell/ability/ritual) we scan the entire
    // board and activate all Cards that have a "whenever a minion leaves play"
    // trigger effect, passing in the leaving minion as the "target". It is
    // the responsibility of each of those abilities to determine how the
    // target Minion/themself is modified.

    // Start/end of turn abilities will work similarly, except the board
    // will perform the scan at the start/end of every turn

    // Active abilities are manually triggered via the use/play commands
    // so they will be easy to implement

    static bool bone_golem(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);

    static bool fire_elemental(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);

    static bool potion_seller(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool novice_pyromancer(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool apprentice_summoner(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool master_summoner(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool banish(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool unsummon(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool recharge(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool disenchant(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool raise_dead(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool blizzard(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);

    static bool silence(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool dark_ritual(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool aura_of_power(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
    
    static bool standstill(
        int pnum, int owner, int index, int targetPlayer, int targetIndex);
};

#endif
