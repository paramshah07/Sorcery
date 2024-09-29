#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <string>

class Card;
class Board;

class Player {
    // will allow Board class to access private fields of Player 
    // (for now. Maybe change later)
    friend class Board;

    std::string name;
    int health;
    int magic;

    // Each player OWNS a hand and a deck
    // (implemented as just a vector of Card *s)
    std::vector<Card *> hand;
    std::vector<Card *> deck;

    // Player will also HAVE access to the Board via a non-owning pointer
    Board *board;

    // some private methods that play_card() will call
    void play_minion(int pnum, int index, bool testing);
    void play_spell(int pnum, int index, bool testing);
    void play_spell(int pnum, int index, int targetPlayer, int targetIndex, bool testing);
    void play_enchantment(int pnum, int index, int targetPlayer, int targetIndex, bool testing);
    void play_ritual(int pnum, int index, bool testing);

  public:
    Player(std::string name);
    ~Player();
    
    // getters 
    std::string get_name();
    int get_health();
    int get_magic();
    std::vector<Card *> *get_hand();
    std::vector<Card *> *get_deck();
    Board *&access_board();
    // setters
    void receive_damage(int amount);
    void restore_health(int amount);
    void use_mana(int amount);
    void gain_mana(int amount);

    // gameplay methods
    void shuffle_deck();
    void add_to_deck(Card *card);
    void draw_card();
    void discard(int index);
    void play_card(int pnum, int index, bool testing);
    void play_card(int pnum, int index, int targetPlayer, int targetIndex, bool testing);
    void use_minion_ability(int pnum, int index, bool testing);
    void use_minion_ability(int pnum, int index, int targetPlayer, int targetIndex, bool testing);
};

#endif
