#include <iostream>
#include <fstream>
#include <sstream>
#include "special_abilities.h"
#include "board.h"
#include "display.h"
#include "player.h"
#include "air_elemental.h"
#include "earth_elemental.h"
#include "bone_golem.h"
#include "fire_elemental.h"
#include "potion_seller.h"
#include "novice_pyromancer.h"
#include "apprentice_summoner.h"
#include "master_summoner.h"
#include "banish.h"
#include "unsummon.h"
#include "recharge.h"
#include "disenchant.h"
#include "raise_dead.h"
#include "blizzard.h"
#include "giant_strength.h"
#include "enrage.h"
#include "haste.h"
#include "magic_fatigue.h"
#include "silence.h"
#include "dark_ritual.h"
#include "aura_of_power.h"
#include "standstill.h"

using namespace std;

// helper fuction that returns true if the file is empty, false otherwise
bool file_is_empty(ifstream &file) {
    return file.peek() == ifstream::traits_type::eof();
}

// returns the index of s in array if array contains s, -1 otherwise
int index_of(string s, char **array, int len) {
    for (int i = 0; i < len; ++i) {
        if (s == array[i]) return i;
    }
    return -1;
}

// simple helper function to alternate between player 1 and player 2's turns
int alternate(int turn) {
    if (turn == 1) return 2;
    return 1;
}

// creates and returns a pointer to a Card object with specified cardname
// allocated on the heap
Card *assign_card(string cardname) {
    Card *newcard = nullptr;
    if (cardname == "Air Elemental") {
        newcard = new AirElemental;
    } else if (cardname == "Earth Elemental") {
        newcard = new EarthElemental;
    } else if (cardname == "Bone Golem") {
        newcard = new BoneGolem;
    } else if (cardname == "Fire Elemental") {
        newcard = new FireElemental;
    } else if (cardname == "Potion Seller") {
        newcard = new PotionSeller;
    } else if (cardname == "Novice Pyromancer") {
        newcard = new NovicePyromancer;
    } else if (cardname == "Apprentice Summoner") {
        newcard = new ApprenticeSummoner;
    } else if (cardname == "Master Summoner") {
        newcard = new MasterSummoner;
    } else if (cardname == "Banish") {
        newcard = new Banish;
    } else if (cardname == "Unsummon") {
        newcard = new Unsummon;
    } else if (cardname == "Recharge") {
        newcard = new Recharge;
    } else if (cardname == "Disenchant") {
        newcard = new Disenchant;
    } else if (cardname == "Raise Dead") {
        newcard = new RaiseDead;
    } else if (cardname == "Blizzard") {
        newcard = new Blizzard;
    } else if (cardname == "Giant Strength") {
        newcard = new GiantStrength;
    } else if (cardname == "Enrage") {
        newcard = new Enrage;
    } else if (cardname == "Haste") {
        newcard = new Haste;
    } else if (cardname == "Magic Fatigue") {
        newcard = new MagicFatigue;
    } else if (cardname == "Silence") {
        newcard = new Silence;
    } else if (cardname == "Dark Ritual") {
        newcard = new DarkRitual;
    } else if (cardname == "Aura of Power") {
        newcard = new AuraOfPower;
    } else if (cardname == "Standstill") {
        newcard = new Standstill;
    }
    return newcard;
}

// initializes SpecialAbilities::board before main()
Board *SpecialAbilities::board = nullptr;

//-----------------------------------------------------------------------------------------------
//==============================START OF MAIN====================================================
//-----------------------------------------------------------------------------------------------
int main(int argc, char **argv) {

    // begin by setting up the -init command
    ifstream init_file;
    int init = index_of("-init", argv, argc);
    if (init != -1) {
        init_file = ifstream{argv[init+1]};
    }
    // whenever read input from player, we check if we should be reading it
    // from the init file instead


    // game begins by asking for Player Names
    string name;
    cout << "Player 1, please choose your name: ";

    if (init == -1 || file_is_empty(init_file)) {
        getline(cin, name);
    } else {
        getline(init_file, name);
    }
    
    Player p1(name); // construct Player object #1
    cout << "Player 2, please choose your name: ";

    if (init == -1 || file_is_empty(init_file)) {
        getline(cin, name);
    } else {
        getline(init_file, name);
    }

    Player p2(name); // construct Player object #2

    Board board; // costruct the game board

    // links the Board / Abilities / Players / Display
    board.access_player(1) = &p1;
    board.access_player(2) = &p2;
    p1.access_board() = &board;
    p2.access_board() = &board;
    Display display{&board};
    SpecialAbilities::set_board(&board);

    // Load each Player's deck of cards.
    int idx1 = index_of("-deck1", argv, argc);
    int idx2 = index_of("-deck2", argv, argc);
    ifstream deck;
    string card;
    // if argument -deck1 is not specified, load default.deck
    if (idx1 == -1) {
        deck = ifstream{"default.deck"};
    } else {
        deck = ifstream{argv[idx1+1]}; // expects a filename (of the deck file)
        // to come after the -deck1 cmd line arg.
    }
    // read all Cards in the deck file and load it into p1's deck
    while (getline(deck, card)) {
        p1.add_to_deck(assign_card(card));
    }
    // if argument -deck2 is not specified, load default.deck
    if (idx2 == -1) {
        deck = ifstream{"default.deck"};
    } else {
        deck = ifstream{argv[idx2+1]}; // expects a filename (of the deck file)
        // to come after the -deck2 cmd line arg.
    }
    // read all Cards in the deck file and load it into p2's deck
    while (getline(deck, card)) {
        p2.add_to_deck(assign_card(card));
    }


    // ===========================================================================================
    // game logic starts here ====================================================================

    bool testing = false;
    if (index_of("-testing", argv, argc) != -1) testing = true; // testing mode

    // shuffle each player's deck of cards
    p1.shuffle_deck();
    p2.shuffle_deck();

    // players start with 5 cards in their hand as specified by the requirements
    for (int i = 0; i < 5; ++i) {
        p1.draw_card();
        p2.draw_card();
    }

    // game loop
    string command;
    int turn = 1; // game starts on Player 1's turn
    while (true) {
        cout << board.access_player(turn)->get_name() << " (P" << turn << ")'s turn: ";

        if (init == -1 || file_is_empty(init_file)) {
            cin >> command;
        } else {
            init_file >> command;
        }
        
        if (command == "help") {
            string help_message = R""""(
Commands: help -- Display this message.
          end -- End the current player’s turn.
          quit -- End the game.
          attack minion other-minion -- Orders minion to attack other-minion.
          attack minion -- Orders minion to attack the opponent.
          play card target-player target-card -- Play card, optionally targeting target-card owned by target-player.
          use minion target-player target-card -- Use minion’s special ability, optionally targeting target-card owned by target-player.
          inspect minion -- View a minion’s card and all enchantments on that minion.
          hand -- Display all cards in your hand.
          board -- Display all cards on the board.
            )"""";
            cout << help_message << endl;
        } else if (command == "quit") {
            break;

        } else if (command == "end") {
            // trigger end of turn events first for active player...
            board.on_turn_end(turn);

            // alternates active "turn"
            turn = alternate(turn);

            // then trigger start of turn events for next player...
            board.on_turn_start(turn);
            
        } else if (command == "draw" && testing) {
            // enabled only in -testing mode
            board.access_player(turn)->draw_card();

        } else if (command == "discard" && testing) {
            // enabled only in -testing mode
            int idx; // 1-5

            if (init == -1 || file_is_empty(init_file)) {
                cin >> idx;
            } else {
                init_file >> idx;
            }

            board.access_player(turn)->discard(idx-1);

        } else if (command == "attack") {
            // after the attack command, must parse the different possible 
            // attack commands
            string details;

            if (init == -1 || file_is_empty(init_file)) {
                getline(cin, details);
            } else {
                getline(init_file, details);
            }

            istringstream detailStream(details);
            char idx; // 1-5
            vector<int> targetIndexes;
            while (detailStream >> idx) {
                targetIndexes.emplace_back(idx-'0'-1);
            } // now targetIndexes stores the parameters of the attack command
            // We read as chars and then convert it to ints because 'r' is a
            // possible argument

            // case 1: attack i
            if (targetIndexes.size() == 1) {
                // check for valid attacking minion index
                if (targetIndexes[0] >= board.get_minions(turn)->size() ||
                    targetIndexes[0] < 0
                ) {
                    cout << "No attacking minion in specified location." << endl;
                    continue;
                }

                // get the minion performing the atk
                Minion *mp = dynamic_cast<Minion *>(
                    board.get_minions(turn)->at(targetIndexes[0]));
                // attack enemy player
                mp->attack_player(board.access_player(alternate(turn)));

            } else if (targetIndexes.size() == 2) {
                // case 2: attack i j

                // check for valid attacking minion index
                if (targetIndexes[0] >= board.get_minions(turn)->size() ||
                    targetIndexes[0] < 0
                ) {
                    cout << "No attacking minion in specified location." << endl;
                    continue;
                }
                // check for valid attacked minion index
                if (targetIndexes[1] >= board.get_minions(alternate(turn))->size() ||
                    targetIndexes[1] < 0
                ) {
                    cout << "No target minion in specified location." << endl;
                    continue;
                }

                // get attacking minion
                Minion *m1 = dynamic_cast<Minion *>(
                    board.get_minions(turn)->at(targetIndexes[0]));
                // get attacked minion
                Minion *m2 = dynamic_cast<Minion *>(
                    board.get_minions(alternate(turn))->at(targetIndexes[1]));
                // perform the attack
                m1->attack_minion(m2);

                // minions may exit play, so we call
                board.on_minion_leave(turn);

            } else {
                cout << "Incorrect usage of attack. See -help for list a of commands." << endl;
            }

        } else if (command == "play") {
            // after the play command, must parse the different possible 
            // play commands
            string details;

            if (init == -1 || file_is_empty(init_file)) {
                getline(cin, details);
            } else {
                getline(init_file, details);
            }

            istringstream detailStream(details);
            char idx; // 1-5
            vector<int> targetIndexes;
            while (detailStream >> idx) {
                targetIndexes.emplace_back(idx-'0'-1);
            } // now targetIndexes stores the parameters of the play command
            // We read as chars and then convert it to ints because 'r' is a
            // possible argument

            // case 1: play i
            if (targetIndexes.size() == 1) {
                board.access_player(turn)->play_card(turn, targetIndexes[0], testing);

            } else if (targetIndexes.size() == 3) {
                // case 2: play i p t
                board.access_player(turn)->play_card(
                    turn, targetIndexes[0], targetIndexes[1]+1, targetIndexes[2], testing);

            } else {
                cout << "Incorrect usage of play. See -help for list a of commands." << endl;
            }

            // minions may exit play, so we call
            board.on_minion_leave(turn);

        } else if (command == "use") {
            // after the use command, must parse the different possible 
            // use commands
            string details;

            if (init == -1 || file_is_empty(init_file)) {
                getline(cin, details);
            } else {
                getline(init_file, details);
            }

            istringstream detailStream(details);
            char idx; // 1-5
            vector<int> targetIndexes;
            while (detailStream >> idx) {
                targetIndexes.emplace_back(idx-'0'-1);
            } // now targetIndexes stores the parameters of the use command
            // We read as chars and then convert it to ints because 'r' is a
            // possible argument

            // case 1: use i
            if (targetIndexes.size() == 1) {
                board.access_player(turn)->use_minion_ability(turn, targetIndexes[0], testing);

            } else if (targetIndexes.size() == 3) {
                // case 2: use i p t
                board.access_player(turn)->use_minion_ability(
                    turn, targetIndexes[0], targetIndexes[1]+1, targetIndexes[2], testing);
                
            } else {
                cout << "Incorrect usage of use. See -help for list a of commands." << endl;
            }

            // minions may exit play, so we call
            board.on_minion_leave(turn);

        } else if (command == "inspect") {
            int idx; // 1-5

            if (init == -1 || file_is_empty(init_file)) {
                cin >> idx;
            } else {
                init_file >> idx;
            }
            
            display.render_minion(turn, idx-1); // unimplemented

        } else if (command == "hand") {
            display.render_hand(turn);

        } else if (command == "board") {
            display.render_board();

        } else {
            cout << "Unknown command. See -help for a list of commands." << endl;
        }

        // if at any point a Player's hp falls to 0, the game is over
        if (p1.get_health() <= 0) {
            cout << "Player 2 wins!" << endl;
            break;
        }
        if (p2.get_health() <= 0) {
            cout << "Player 1 wins!" << endl;
            break;
        }
    }
}
