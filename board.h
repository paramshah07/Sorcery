#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "player.h"

class Card;

// Board class keeps track of game state
class Board {
    friend class SpecialAbilities;
    friend class Player;
    // Board will recieve OWNERSHIP of the cards that are played
    // on the board (ie. Graveyard, Ritual, Minions in play)
    // Theres no real reason for this choice of implementation, I just think
    // its reflective of reality
    std::vector<Card *> grave1;
    std::vector<Card *> grave2;
    Card *ritual1;
    Card *ritual2;
    std::vector<Card *> minionsInPlay1;
    std::vector<Card *> minionsInPlay2;

    // Board object will HAVE two Player objects 
    Player *p1;
    Player *p2;

  public:
    Board();
    ~Board();

    std::vector<Card *> *get_grave(int pnum);
    Card *get_ritual(int pnum);
    std::vector<Card *> *get_minions(int pnum);
    Player *&access_player(int pnum);
    void on_turn_start(int pnum);
    void on_turn_end(int pnum);
    void on_minion_entry(int pnum, int targetPlayer, int enteringIndex);
    void on_minion_leave(int pnum, int targetPlayer = -1, int exitingIndex = -1);
};

#endif
