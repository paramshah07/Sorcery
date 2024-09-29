#include <iostream>
#include <cmath>
#include "ascii_graphics.h"
#include "display.h"
#include "board.h"
#include "player.h"
#include "card.h"
#include "minion.h"
#include "spell.h"
#include "ritual.h"
#include "enchantment.h"

using namespace std;
    
Display::Display(Board *b): b{b} {}

Display::~Display() {}

// helper functions for render
void print_minion(Minion *mp, int rownum) {
    // minion with no active ability
    if (mp->get_ability_cost() == -1) {
        cout << display_minion_triggered_ability(
            mp->get_name(), mp->get_cost(), mp->get_atk(),
            mp->get_def(), mp->get_desc()
        )[rownum];
    } else {
        // minion with active ability
        cout << display_minion_activated_ability(
            mp->get_name(), mp->get_cost(), mp->get_atk(),
            mp->get_def(), mp->get_ability_cost(), mp->get_desc()
        )[rownum];
    }
}

void print_spell(Spell *sp, int rownum) {
    cout << display_spell(
        sp->get_name(), sp->get_cost(), sp->get_desc()
    )[rownum];
}

void print_enchantment(Enchantment *ep, int rownum) {
    // enchantmet that doesn't modify Minion stats
    if (ep->get_atk_mod() == "" && ep->get_def_mod() == "") {
        cout << display_enchantment(
            ep->get_name(), ep->get_cost(), ep->get_desc()
        )[rownum];
    } else {
        // enchantment that modifies Minion stats
        cout << display_enchantment_attack_defence(
            ep->get_name(), ep->get_cost(), ep->get_desc(), 
            ep->get_atk_mod(), ep->get_def_mod()
        )[rownum];
    }    
}

void print_ritual(Ritual *rp, int rownum) {
    cout << display_ritual(
        rp->get_name(), rp->get_cost(), rp->get_ritual_cost(),
        rp->get_desc(), rp->get_num_charges()
    )[rownum];
}

// prints board to cout
void Display::render_board() const {
    string EMPTY_SPACE = "                                 "; // 33 spaces

    // top left
    cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    // top edge of board
    for (int i = 0; i < 165; ++i) {
        cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    // top right
    cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT;
    cout << endl;

    // next 11 rows (first row of card slots)
    for (int i = 0; i < 11; ++i) {

        // print the left border of the board
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        
        // if p1's ritual slot on the board is empty, print an empty box
        if (b->get_ritual(1) == nullptr) {
            cout << CARD_TEMPLATE_BORDER[i];
        } else {
            // else print the ritual
            Ritual *rp = dynamic_cast<Ritual *>(b->get_ritual(1));
            print_ritual(rp, i);
        }

        // then print some empty spaces
        cout << EMPTY_SPACE;

        // print p1 on the board
        cout << display_player_card(1,
            b->access_player(1)->get_name(),
            b->access_player(1)->get_health(), 
            b->access_player(1)->get_magic()
        )[i];

        // then print some empty spaces
        cout << EMPTY_SPACE;

        // then print p1's graveyard (if its non-empty)
        // otherwise print an empty box
        if (b->get_grave(1)->size() == 0) {
            cout << CARD_TEMPLATE_BORDER[i];
        } else {
            // else print the top Minion in the graveyard
            Minion *top = dynamic_cast<Minion *>(b->get_grave(1)->back());
            print_minion(top, i);
        }

        // print the right border of the board
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;

        // next line
        cout << endl;
    }

    // next 11 rows (row of p1's minions)
    for (int i = 0; i < 11; ++i) {

        // print the left border of the board
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;

        // loop 5 times, one for each card slot on the board
        for (int j = 0; j < 5; ++j) {
            // prints each card (if there is a card)
            if (b->get_minions(1)->size() > j) {
                Minion *jth = dynamic_cast<Minion *>(b->get_minions(1)->at(j));
                print_minion(jth, i);
            } else {
                // if there is no card, prints a blank box
                cout << CARD_TEMPLATE_BORDER[i];
            }
        }

        // print the right border of the board
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;

        // newline
        cout << endl;
    }

    // next 10 rows (the SORCERY logo)
    for (int i = 0; i < 10; ++i) {
        cout << CENTRE_GRAPHIC[i] << endl;
    }

    // next 11 rows (row of p2's minions)
    for (int i = 0; i < 11; ++i) {

        // print the left border of the board
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;

        // loop 5 times, one for each card slot on the board
        for (int j = 0; j < 5; ++j) {
            // prints each card (if there is a card)
            if (b->get_minions(2)->size() > j) {
                Minion *jth = dynamic_cast<Minion *>(b->get_minions(2)->at(j));
                print_minion(jth, i);
            } else {
                // if there is no card, prints a blank box
                cout << CARD_TEMPLATE_BORDER[i];
            }
        }

        // print the right border of the board
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;

        // newline
        cout << endl;
    }

    // last 11 rows (last row of card slots)
    for (int i = 0; i < 11; ++i) {

        // print the left border of the board
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        
        // if p2's ritual slot on the board is empty, print an empty box
        if (b->get_ritual(2) == nullptr) {
            cout << CARD_TEMPLATE_BORDER[i];
        } else {
            // else print the ritual
            Ritual *rp = dynamic_cast<Ritual *>(b->get_ritual(2));
            print_ritual(rp, i);
        }

        // then print some empty spaces
        cout << EMPTY_SPACE;

        // print p2 on the board
        cout << display_player_card(2,
            b->access_player(2)->get_name(),
            b->access_player(2)->get_health(), 
            b->access_player(2)->get_magic()
        )[i];

        // then print some empty spaces
        cout << EMPTY_SPACE;

        // then print p2's graveyard (if its non-empty)
        // otherwise print an empty box
        if (b->get_grave(2)->size() == 0) {
            cout << CARD_TEMPLATE_BORDER[i];
        } else {
            // else print the top Minion in the graveyard
            Minion *top = dynamic_cast<Minion *>(b->get_grave(2)->back());
            print_minion(top, i);
        }

        // print the right border of the board
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;

        // next line
        cout << endl;
    }

    // bottom left
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    // bottom edge of board
    for (int i = 0; i < 165; ++i) {
        cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    // bottom right
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT;
    cout << endl;
}

// print hand to cout
void Display::render_hand(int pnum) const {
    // Cards in the hand can be any kind of Card so we have to do some
    // type checking before casting
    if (pnum == 1) {
        for (int i = 0; i < 11; ++i) {
            // loops up to 5 times (max hand of 5 cards)
            for (int j = 0; j < b->access_player(1)->get_hand()->size() && j < 5; ++j) {
                // attempts to cast as a Minion *
                Minion *mp = dynamic_cast<Minion *>(b->access_player(1)->get_hand()->at(j));
                if (mp) {
                    print_minion(mp, i);
                    continue;
                }
                // attempts to cast as a Spell *
                Spell *sp = dynamic_cast<Spell *>(b->access_player(1)->get_hand()->at(j));
                if (sp) {
                    print_spell(sp, i);
                    continue;
                }
                // attempts to cast as a Enchantment *
                Enchantment *ep = dynamic_cast<Enchantment *>(b->access_player(1)->get_hand()->at(j));
                if (ep) {
                    print_enchantment(ep, i);
                    continue;
                }
                // attempts to cast as a Ritual *
                Ritual *rp = dynamic_cast<Ritual *>(b->access_player(1)->get_hand()->at(j));
                if (rp) {
                    print_ritual(rp, i);
                    continue;
                }
            }
            cout << endl;
        }
    } else if (pnum == 2) {
        // do the same for p2
        for (int i = 0; i < 11; ++i) {
            // loops up to 5 times (max hand of 5 cards)
            for (int j = 0; j < b->access_player(2)->get_hand()->size() && j < 5; ++j) {
                // attempts to cast as a Minion *
                Minion *mp = dynamic_cast<Minion *>(b->access_player(2)->get_hand()->at(j));
                if (mp) {
                    print_minion(mp, i);
                    continue;
                }
                // attempts to cast as a Spell *
                Spell *sp = dynamic_cast<Spell *>(b->access_player(2)->get_hand()->at(j));
                if (sp) {
                    print_spell(sp, i);
                    continue;
                }
                // attempts to cast as a Enchantment *
                Enchantment *ep = dynamic_cast<Enchantment *>(b->access_player(2)->get_hand()->at(j));
                if (ep) {
                    print_enchantment(ep, i);
                    continue;
                }
                // attempts to cast as a Ritual *
                Ritual *rp = dynamic_cast<Ritual *>(b->access_player(2)->get_hand()->at(j));
                if (rp) {
                    print_ritual(rp, i);
                    continue;
                }
            }
            cout << endl;
        }
    } else {
        cerr << "Invalid render: playerNum should be 1 or 2 | Display::render_hand() | display.cc" << endl;
    }
}

// print Minion + attached Enchantments to cout
void Display::render_minion(int pnum, int index) const {
    // first checks for valid index
    if (index >= this->b->get_minions(pnum)->size()) {
        cerr << "Index out of range | Display::render_minion() | display.cc" << endl;
        return;
    }

    // prints the minion Card
    Minion *mp = dynamic_cast<Minion *>(this->b->get_minions(pnum)->at(index));
    for (int i = 0; i < 11; ++i) {
        print_minion(mp, i);
        cout << endl;
    }

    // then checks how many enchantments the Minion has and allocates
    // space to print accordingly
    int numEnchants = mp->get_enchants()->size();
    for (int k = 0; k < ceil(numEnchants/(double)5); ++k) {
        // then prints the enchantments that follow
        for (int i = 0; i < 11; ++i) {
            for (int j = 0; j < mp->get_enchants()->size(); ++j) {
                Enchantment *ep = mp->get_enchants()->at(j);
                print_enchantment(ep,i);
            }
            cout << endl;
        }
    }
}
