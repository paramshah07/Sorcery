#include <iostream>
#include "player.h"
#include "board.h"
#include "card.h"
#include "minion.h"
#include "enchantment.h"
#include "ritual.h"
#include "special_abilities.h"

using namespace std;

// we choose to initialize all pointer values to nullptr
// and bound them manually in game_controller.cc
Board::Board():
    p1{nullptr}, p2{nullptr}, ritual1{nullptr}, ritual2{nullptr} {}

// dtor deletes grave1, grave2, ritual1, ritual2, minionsInPlay1, 
// and minionsInPlay2
Board::~Board() {
    delete ritual1;
    delete ritual2;
    for (int i = 0; i < grave1.size(); ++i) {
        delete grave1.at(i);
    }
    for (int i = 0; i < grave2.size(); ++i) {
        delete grave2.at(i);
    }
    for (int i = 0; i < minionsInPlay1.size(); ++i) {
        delete minionsInPlay1.at(i);
    }
    for (int i = 0; i < minionsInPlay2.size(); ++i) {
        delete minionsInPlay2.at(i);
    }
}

// Various getter methods
std::vector<Card *> *Board::get_grave(int pnum) {
    if (pnum == 1) {
        return &this->grave1;
    } else if (pnum == 2) {
        return &this->grave2;
    }
    cerr << "error: pnum needs to be 1 or 2 | Board::get_grave() | board.cc" << endl;
}

Card *Board::get_ritual(int pnum) {
    if (pnum == 1) {
        return this->ritual1;
    } else if (pnum == 2) {
        return this->ritual2;
    }
    cerr << "error: pnum needs to be 1 or 2 | Board::get_ritual() | board.cc" << endl;
}

std::vector<Card *> *Board::get_minions(int pnum) {
    if (pnum == 1) {
        return &this->minionsInPlay1;
    } else if (pnum == 2) {
        return &this->minionsInPlay2;
    }
    cerr << "error: pnum needs to be 1 or 2 | Board::get_minions() | board.cc" << endl;
}

// These are both getters and setters
Player *&Board::access_player(int pnum) {
    if (pnum == 1) {
        return this->p1;
    } else if (pnum == 2) {
        return this->p2;
    }
    cerr << "error: pnum needs to be 1 or 2 | Board::access_player() | board.cc" << endl;
}


// the value of many parameters in the calls to methods below do not matter
const int IRRELEVANT = 1000;

// triggers all ON_TURN_START abilities of all Cards on the board
void Board::on_turn_start(int pnum) {
    // calls the abilities of all cards on the board (and only those
    // with ON_TURN_START abilities will trigger)

    // All of pnum's minions on the board will regain their actions
    // and Pnum gains 1 mana

    int pOther;
    if (pnum == 1) { pOther = 2; } 
    else if (pnum == 2) { pOther = 1; }
    else { cerr << "Invalid pnum | on_turn_start() | board.cc" << endl; }

    // starts with pnum's ritual
    if (this->get_ritual(pnum) != nullptr) {
        // for rituals, other than the pnum and owner, no other parameters
        // matter
        this->get_ritual(pnum)->use_ablility(
            pnum, pnum, IRRELEVANT, IRRELEVANT, IRRELEVANT, ON_TURN_START);
    }
    // then calls abilities of each of pnum's minions 
    for (int i = 0; i < this->get_minions(pnum)->size(); ++i) {
        this->get_minions(pnum)->at(i)->use_ablility(
            pnum, pnum, i, IRRELEVANT, IRRELEVANT, ON_TURN_START);
        
        // regain action for pnum's minions
        dynamic_cast<Minion *>(this->get_minions(pnum)->at(i))->reset_actions();
    }
    // then calls pOther's ritual
    if (this->get_ritual(pOther) != nullptr) {
        // for rituals, other than the pnum and owner, no other parameters
        // matter
        this->get_ritual(pOther)->use_ablility(
            pnum, pOther, IRRELEVANT, IRRELEVANT, IRRELEVANT, ON_TURN_START);
    }
    // then calls abilities of each of pOther's minions 
    for (int i = 0; i < this->get_minions(pOther)->size(); ++i) {
        this->get_minions(pOther)->at(i)->use_ablility(
            pnum, pOther, i, IRRELEVANT, IRRELEVANT, ON_TURN_START);
    }

    // gain 1 mana for pnum
    this->access_player(pnum)->gain_mana(1);

    // player pnum draws a card
    this->access_player(pnum)->draw_card();
}

// triggers all ON_TURN_END abilities of all Cards on the board
void Board::on_turn_end(int pnum) {
    // calls the abilities of all cards on the board (and only those
    // with ON_TURN_END abilities will trigger)

    int pOther;
    if (pnum == 1) { pOther = 2; } 
    else if (pnum == 2) { pOther = 1; }
    else { cerr << "Invalid pnum | on_turn_start() | board.cc" << endl; }

    // starts with pnum's ritual
    if (this->get_ritual(pnum) != nullptr) {
        // for rituals, other than the pnum and owner, no other parameters
        // matter
        this->get_ritual(pnum)->use_ablility(
            pnum, pnum, IRRELEVANT, IRRELEVANT, IRRELEVANT, ON_TURN_END);
    }
    // then calls abilities of each of pnum's minions 
    for (int i = 0; i < this->get_minions(pnum)->size(); ++i) {
        this->get_minions(pnum)->at(i)->use_ablility(
            pnum, pnum, i, IRRELEVANT, IRRELEVANT, ON_TURN_END);
    }
    // then calls pOther's ritual
    if (this->get_ritual(pOther) != nullptr) {
        // for rituals, other than the pnum and owner, no other parameters
        // matter
        this->get_ritual(pOther)->use_ablility(
            pnum, pOther, IRRELEVANT, IRRELEVANT, IRRELEVANT, ON_TURN_END);
    }
    // then calls abilities of each of pOther's minions 
    for (int i = 0; i < this->get_minions(pOther)->size(); ++i) {
        this->get_minions(pOther)->at(i)->use_ablility(
            pnum, pOther, i, IRRELEVANT, IRRELEVANT, ON_TURN_END);
    }
}

// Processes minions entering the board.
// This method will be called once immediately after every minion entry
// (unlike on_minion_leave) and the entering minion coords will be passed
// as mandatory parameters (targetPlayer, enteringIndex).
void Board::on_minion_entry(int pnum, int targetPlayer, int enteringIndex) {
    // calls the abilities of all cards on the board (and only those
    // with ON_MINION_ENTRY abilities will trigger)

    int pOther;
    if (pnum == 1) { pOther = 2; } 
    else if (pnum == 2) { pOther = 1; }
    else { cerr << "Invalid pnum | on_minion_entry() | board.cc" << endl; }

    // starts with pnum's ritual
    if (this->get_ritual(pnum) != nullptr) {
        // we call it with 65 but the value here is irrelevant because
        // its the player's ritual so index doesnt matter
        this->get_ritual(pnum)->use_ablility(
            pnum, pnum, IRRELEVANT, targetPlayer, enteringIndex, ON_MINION_ENTRY);
    }
    // then calls abilities of each of pnum's minions 
    for (int i = 0; i < this->get_minions(pnum)->size(); ++i) {
        // (excluding the minion that just entered)
        if (pnum == targetPlayer && i == enteringIndex) continue;

        this->get_minions(pnum)->at(i)->use_ablility(
            pnum, pnum, i, targetPlayer, enteringIndex, ON_MINION_ENTRY);
    }
    // then calls pOther's ritual
    if (this->get_ritual(pOther) != nullptr) {
        // we call it with 65 but the value here is irrelevant because
        // its the player's ritual so index doesnt matter
        this->get_ritual(pOther)->use_ablility(
            pnum, pOther, IRRELEVANT, targetPlayer, enteringIndex, ON_MINION_ENTRY);
    }
    // then calls abilities of each of pOther's minions 
    for (int i = 0; i < this->get_minions(pOther)->size(); ++i) {
        // (excluding the minion that just entered)
        if (pOther == targetPlayer && i == enteringIndex) continue;

        this->get_minions(pOther)->at(i)->use_ablility(
            pnum, pOther, i, targetPlayer, enteringIndex, ON_MINION_ENTRY);
    }
}

// Detects minions leaving the board and updates the state of the board 
// approporiately. Will call this after any action that could possibly
// cause a Minion to leave play.
// The method will scan and process ALL Minions on the board that should 
// leave play in APNAP order, or if a specific minion is provided 
void Board::on_minion_leave(int pnum, int targetPlayer, int exitingIndex) {
    int pOther;
    if (pnum == 1) { pOther = 2; } 
    else if (pnum == 2) { pOther = 1; }
    else { cerr << "Invalid pnum | on_minion_leave() | board.cc" << endl; }

    // checks for any Minion leaves after any action

    // some abilities will call this method already providing a target minion
    // (so we dont have to perform any scans) (defaults to -1,-1 if no minion
    // is specified)
    // In this case, we just trigger any follow up abilities that are resulted
    // from this Minion's exit.
    if (1 <= targetPlayer && targetPlayer <= 2 &&
        0 <= exitingIndex && exitingIndex <= 4) 
    {
        Minion *exiting = dynamic_cast<Minion *>(
            this->get_minions(targetPlayer)->at(exitingIndex));

        // here, we create a special interaction for destroyed Minions:
        // (which deletes the destroyed Minion instead of moving it to graveyard)
        if (exiting->get_def() == -10000) {
            delete exiting;
            this->get_minions(targetPlayer)->erase(
                this->get_minions(targetPlayer)->begin() + exitingIndex);

        } else  if (exiting->get_def() <= 0) {
            // move specified minion into the graveyard
            this->get_grave(targetPlayer)->emplace_back(exiting);
            // remove the card from board
            this->get_minions(targetPlayer)->erase(
                this->get_minions(targetPlayer)->begin() + exitingIndex);

            // no need to remove enchantments in this part because enchantment
            // removal logic is handled specifically by the function that called
            // this method

        } else {
            // if sepcified leaving minion's def is > 0, then it must be the
            // result of unsummon being played on it (so far at least).
            // In this case we move the Minion to the target player's hand/deck
            if (this->access_player(targetPlayer)->get_hand()->size() < 5) {
                this->access_player(targetPlayer)->get_hand()->emplace_back(exiting);
            } else {
                this->access_player(targetPlayer)->get_deck()->emplace_back(exiting);
            }
            // remove the card from the board
            this->get_minions(targetPlayer)->erase(
                this->get_minions(targetPlayer)->begin() + exitingIndex);
        }


        // This function will trigger the ability of all cards on the board.
        // Only those abilities that trigger on minion leave will activate.
        // currently, no rituals are triggered from minions leaving play 
        // (so I wont check for any ritual abilities)

        // starting with pnum's minions (APNAP order)
        for (int j = 0; j < this->get_minions(pnum)->size(); ++j) {
            // the minion triggering the ability is (pnum, j)
            // the target minion is the exiting one (pnum, exitingIndex)
            this->get_minions(pnum)->at(j)->use_ablility(
                pnum, pnum, j, targetPlayer, exitingIndex, ON_MINION_EXIT
            );
        }
        // then onto pOther's minions
        for (int j = 0; j < this->get_minions(pOther)->size(); ++j) {
            // the minion triggering the ability is (pOther, j)
            // the target minion is the exiting one (pOther, exitingIndex)
            this->get_minions(pOther)->at(j)->use_ablility(
                pnum, pOther, j, targetPlayer, exitingIndex, ON_MINION_EXIT
            );
        }
        // note that for minion_exit-based abilities, the target minion
        // fields are irrelevant since none of those abilities
        // target another Card
        return;
    }

    // if a specific minion that's exiting the board is not given, then we
    // check all deaths of pnum's minions first (APNAP order)
    for (int i = 0; i < this->get_minions(pnum)->size(); ++i) {
        Minion *candidate = dynamic_cast<Minion *>(this->get_minions(pnum)->at(i));
        if (candidate->get_def() <= 0) {
            // place the candidate to the top of pnum's graveyard
            this->get_grave(pnum)->emplace_back(candidate);
            // remove the candidate from the board
            this->get_minions(pnum)->erase(this->get_minions(pnum)->begin() + i);
            // since we are erasing a value in a vector, fix the index
            --i;
            // destroy all of candidate's enchantments
            for (int j = candidate->get_enchants()->size()-1; j >= 0; --j) {
                candidate->get_enchants()->at(j)->detach_enchantment(candidate);
                delete candidate->get_enchants()->at(j);
                candidate->get_enchants()->pop_back();
            }


            // trigger abilities same as above
            // starting with pnum's minions
            for (int j = 0; j < this->get_minions(pnum)->size(); ++j) {
                // the minion triggering the ability is (pnum, j)
                // the target minion is IRRELEVANT
                this->get_minions(pnum)->at(j)->use_ablility(
                    pnum, pnum, j, IRRELEVANT, IRRELEVANT, ON_MINION_EXIT
                );
            }
            // then onto pOther's minions
            for (int j = 0; j < this->get_minions(pOther)->size(); ++j) {
                // the minion triggering the ability is (pOther, j)
                // the target minion is IRRELEVANT
                this->get_minions(pOther)->at(j)->use_ablility(
                    pnum, pOther, j, IRRELEVANT, IRRELEVANT, ON_MINION_EXIT
                );
            }
        }
    }
    
    // then check all deaths of pnum's opponent's minions after (APNAP order)
    for (int i = 0; i < this->get_minions(pOther)->size(); ++i) {
        Minion *candidate = dynamic_cast<Minion *>(this->get_minions(pOther)->at(i));
        if (candidate->get_def() <= 0) {
            // place the candidate to the top of pOther's graveyard
            this->get_grave(pOther)->emplace_back(candidate);
            // remove the candidate from the board
            this->get_minions(pOther)->erase(this->get_minions(pOther)->begin() + i);
            // since we are erasing a value in a vector, fix the index
            --i;
            // destroy all of candidate's enchantments
            for (int j = candidate->get_enchants()->size()-1; j >= 0; --j) {
                candidate->get_enchants()->at(j)->detach_enchantment(candidate);
                delete candidate->get_enchants()->at(j);
                candidate->get_enchants()->pop_back();
            }

            // same as above
            // starting with pnum's minions
            for (int j = 0; j < this->get_minions(pnum)->size(); ++j) {
                // the minion triggering the ability is (pnum, j)
                // the target minion is IRRELEVANT
                this->get_minions(pnum)->at(j)->use_ablility(
                    pnum, pnum, j, IRRELEVANT, IRRELEVANT, ON_MINION_EXIT
                );
            }
            // then onto pOther's minions
            for (int j = 0; j < this->get_minions(pOther)->size(); ++j) {
                // the minion triggering the ability is (pOther, j)
                // the target minion is IRRELEVANT
                this->get_minions(pOther)->at(j)->use_ablility(
                   pnum, pOther, j, IRRELEVANT, IRRELEVANT, ON_MINION_EXIT
                );
            }
        }
    }
}
