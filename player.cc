#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "special_abilities.h"
#include "player.h"
#include "board.h"
#include "minion.h"
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"

using namespace std;

// constants defined by project requirements
int STARTING_HEALTH = 20;
int STARTING_MAGIC = 3;

// Constructor will construct the Player's starting health, magic, and
// given name
// The Player's Cards and hand will be distributed manually in game_controller.cc
// along with linking the Player to the Board
Player::Player(string name): 
    name{name}, health{STARTING_HEALTH}, magic{STARTING_MAGIC}, board{nullptr}
{}

// destructor must free all the Cards in Player's deck and hand
Player::~Player() {
    for (int i = 0; i < deck.size(); ++i) {
        delete deck.at(i);
    }
    for (int i = 0; i < hand.size(); ++i) {
        delete hand.at(i);
    }
}

// getter methods
string Player::get_name() {
    return this->name;
}

int Player::get_health() {
    return this->health;
}

int Player::get_magic() {
    return this->magic;
}

vector<Card *> *Player::get_hand() {
    return &this->hand;
}

vector<Card *> *Player::get_deck() {
    return &this->deck;
}

// both getter and setter
Board *&Player::access_board() {
    return this->board;
}

// modifiers
void Player::receive_damage(int amount) {
    this->health -= amount;
}

void Player::restore_health(int amount) {
    this->health += amount;
}

void Player::use_mana(int amount) {
    this->magic -= amount;
}

void Player::gain_mana(int amount) {
    this->magic += amount;
}

// shuffles the cards in the Player's deck in a random order
void Player::shuffle_deck() {
    // code taken from the provided shuffle.cc file
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng{seed};

    shuffle(this->deck.begin(), this->deck.end(), rng);
}

// used to load cards into player's deck
void Player::add_to_deck(Card *card) {
    this->deck.emplace_back(card);
}

// moves a card from player's deck into their hand
void Player::draw_card() {
    if (this->hand.size() >= 5) return;
    if (this->deck.size() == 0) return;

    // put a copy of a ptr pointing to the Card at the back (which will
    // be designed as the "top") of the deck into the hand vector.
    this->hand.emplace_back(deck.back());
        
    // then we pop the pointer to that Card out from the deck pointer
    // to complete the transfer of a Card from the deck to the hand
    deck.pop_back();
}

// discards the ith card in the player’s hand, simply removing it from their 
// hand (the card does not go to the graveyard, trigger leave play effects or 
// anything else). 
void Player::discard(int index) {
    // checks for index out of range error
    if (index >= this->hand.size()) {
        cerr << "Invalid index | Player::discard() | player.cc" << endl;
        return;
    }

    // create a temp pointer to the card to avoid memory leak
    Card *temp = this->hand.at(index);
    // remove card from hand at position index
    this->hand.erase(hand.begin() + index);
    // free memory
    delete temp;
}


// the value of many parameters in the calls to methods below do not matter
const int IRRELEVANT = 1000;

// play i:
// plays card at position "index" from active Player's hand 
void Player::play_card(int pnum, int index, bool testing) {
    // checks for index out of range error
    if (index >= this->hand.size()) {
        cerr << "No card in hand at index | Player::play_card() | player.cc" << endl;
        return;
    }
    if (!testing) {
        // checks for mana cost
        if (this->get_magic() < this->hand.at(index)->get_cost()) {
            cerr << "Not enough magic | Player::play_card() | player.cc" << endl;
            return;
        }
    }
    // determines what type of Card is being played and invokes the
    // corresponding private method
    if (dynamic_cast<Minion *>(this->hand.at(index))) {
        play_minion(pnum, index, testing);

    } else if (dynamic_cast<Spell *>(this->hand.at(index))){
        play_spell(pnum, index, testing);

    } else if (dynamic_cast<Enchantment *>(this->hand.at(index))){
        cerr << "You cannot play an Enchantment like that | Player::play_card() | player.cc" << endl;

    } else if (dynamic_cast<Ritual *>(this->hand.at(index))){
        play_ritual(pnum, index, testing);

    } else {
        cerr << "You've somehow got an illegal card??? | Player::play_card() | player.cc" << endl;
    }
}

// play i p t:
// plays card at position "index" from active Player's hand onto the target
// players' minion on field at index targetIndex
void Player::play_card(
    int pnum, int index, int targetPlayer, int targetIndex, bool testing
) {
    // checks for index out of range error
    if (index >= this->hand.size()) {
        cerr << "No card in hand at index | Player::play_card() | player.cc" << endl;
        return;
    }
    if (!testing) {
        // checks for mana cost
        if (this->get_magic() < this->hand.at(index)->get_cost()) {
            cerr << "Not enough magic | Player::play_card() | player.cc" << endl;
            return;
        }
    }
    // determines what type of Card is being played and invokes the
    // corresponding private method
    if (dynamic_cast<Minion *>(this->hand.at(index))) {
        cerr << "You cannot play a Minion like that | Player::play_card() | \
player.cc" << endl;

    } else if (dynamic_cast<Spell *>(this->hand.at(index))){
        play_spell(pnum, index, targetPlayer, targetIndex, testing);

    } else if (dynamic_cast<Enchantment *>(this->hand.at(index))){
        play_enchantment(pnum, index, targetPlayer, targetIndex, testing);

    } else if (dynamic_cast<Ritual *>(this->hand.at(index))){
        cerr << "You cannot play a Ritual like that | Player::play_card() | \
player.cc" << endl;

    } else {
        cerr << "You've somehow got an illegal card??? | Player::play_card() | \
player.cc" << endl;
    }
}

// plays (moves) a Minion Card at position "index" from Player's hand 
// onto the Board
void Player::play_minion(int pnum, int index, bool testing) {
    // checks if playing field is full
    if (this->board->get_minions(pnum)->size() >= 5) {
        cerr << "Playing field is full, cannot play any more minions | \
Player::play_minion() | player.cc" << endl;
        return;
    }

    // deduct the cost of playing the card
    this->magic -= this->hand.at(index)->get_cost();
    if (testing && this->magic < 0) {
        this->magic = 0;
    }

    this->board->get_minions(pnum)->emplace_back(hand[index]);
    hand.erase(hand.begin() + index);

    // Minion enters field here so we call
    board->on_minion_entry(pnum, pnum, board->get_minions(pnum)->size()-1);
}

void Player::play_spell(int pnum, int index, bool testing){
    Spell *sp = dynamic_cast<Spell *>(
        this->board->access_player(pnum)->get_hand()->at(index));
    
    // use the spell ability
    if (!sp->use_ablility(
        pnum, pnum, index, IRRELEVANT, IRRELEVANT, ACTIVE_ABILITY
    )) {
        cerr << "Activation failed | Player::play_spell() | player.cc" << endl;
        return;
    }

    // deduct the cost of playing the card
    this->magic -= this->hand.at(index)->get_cost();
    if (testing && this->magic < 0) {
        this->magic = 0;
    }

    // then delete the card and remove from hand
    delete sp;
    this->board->access_player(pnum)->get_hand()->erase(
        this->board->access_player(pnum)->get_hand()->begin() + index);
}

void Player::play_spell(
    int pnum, int index, int targetPlayer, int targetIndex, bool testing
){
    // check if playing is valid
    if (board->get_minions(targetPlayer)->size() <= targetIndex &&
        targetIndex >= 0 && targetIndex != ('r'-'0'-1)    
    ) {
        cerr << "Invalid card selected | Player::play_spell() | player.cc" << endl;
        return;
    }

    Spell *sp = dynamic_cast<Spell *>(
        this->board->access_player(pnum)->get_hand()->at(index));
    
    // use the spell ability
    if(!sp->use_ablility(
        pnum, pnum, index, targetPlayer, targetIndex, ACTIVE_ABILITY
    )) {
        cerr << "Activation failed | Player::play_spell() | player.cc" << endl;
        return;
    }

    // deduct the cost of playing the card
    this->magic -= this->hand.at(index)->get_cost();
    if (testing && this->magic < 0) {
        this->magic = 0;
    }

    // then delete the card and remove from hand
    delete sp;
    this->board->access_player(pnum)->get_hand()->erase(
        this->board->access_player(pnum)->get_hand()->begin() + index);
}

void Player::play_enchantment(
    int pnum, int index, int targetPlayer, int targetIndex, bool testing
){
    // first check for targetIndex out of range on target
    if (targetIndex >= this->board->get_minions(targetPlayer)->size()) {
        cerr << "Invalid target | Player::play_enchantment() | player.cc" << endl;
        return;
    }
    Minion *targetMinion = dynamic_cast<Minion *>(
        this->board->get_minions(targetPlayer)->at(targetIndex));
    Enchantment *targetEnchantment = dynamic_cast<Enchantment *>(
        this->board->access_player(pnum)->get_hand()->at(index));
    
    // enchant the Minion with the Enchant
    targetMinion->attach_enchantment(targetEnchantment);

    // deduct the cost of playing the card
    this->magic -= this->hand.at(index)->get_cost();
    if (testing && this->magic < 0) {
        this->magic = 0;
    }

    // remove enchant from player's hand
    board->access_player(pnum)->hand.erase(
        board->access_player(pnum)->hand.begin() + index);
}

// plays (moves) a Ritual Card at position "index" from Player's hand 
// onto the Board
void Player::play_ritual(int pnum, int index, bool testing) {
    // need to directly access Board's fields here since we have to free
    // memory here

    // deduct the cost of playing the card
    this->magic -= this->hand.at(index)->get_cost();
    if (testing && this->magic < 0) {
        this->magic = 0;
    }

    if (pnum == 1) {
        // frees up the current Ritual slot
        delete this->board->ritual1;
        // then moves the card in hand at index position 
        this->board->ritual1 = hand[index];
        hand.erase(hand.begin() + index);
    } else if (pnum == 2) {
        delete this->board->ritual2;
        this->board->ritual2 = hand[index];
        hand.erase(hand.begin() + index);
    } else {
        cerr << "Invalid pnum | Player::play_ritual() | player.cc" << endl;
    }
}

// use i
void Player::use_minion_ability(int pnum, int index, bool testing){
    // validate index
    if (index >= board->get_minions(pnum)->size() || index <= -1) {
        cerr << "No minion in specified location | use_minion_ability() | \
player.cc" << endl;
        return;
    }

    Minion *mp = dynamic_cast<Minion *>(
        this->board->get_minions(pnum)->at(index));

    // use the active ability
    if (!mp->use_ablility(
        pnum, pnum, index, IRRELEVANT, IRRELEVANT, ACTIVE_ABILITY
    )) {
        cerr << "Activation failed | Player::use_minion_ability() | player.cc" << endl;
        return;
    }

    // deduct the cost of triggering the bility
    this->magic -= mp->get_ability_cost();
    if (testing && this->magic < 0) {
        this->magic = 0;
    }
}

// use i p t
void Player::use_minion_ability(
    int pnum, int index, int targetPlayer, int targetIndex, bool testing
){
    // validate index
    if (index >= board->get_minions(pnum)->size() || index <= -1) {
        cerr << "No minion in specified location | use_minion_ability() | \
player.cc" << endl;
        return;
    }

    Minion *mp = dynamic_cast<Minion *>(
        this->board->get_minions(pnum)->at(index));
    
    // use the active ability
    if (!mp->use_ablility(
        pnum, pnum, index, targetPlayer, targetIndex, ACTIVE_ABILITY
    )) {
        cerr << "Activation failed | Player::use_minion_ability() | player.cc" << endl;
        return;
    }

    // deduct the cost of triggering the bility
    this->magic -= mp->get_ability_cost();
    if (testing && this->magic < 0) {
        this->magic = 0;
    }
}
