#include <iostream>
#include "special_abilities.h"
#include "minion.h"
#include "enchantment.h"
#include "player.h"

using namespace std;

Minion::~Minion() {
    // Minion responsible for deeteing all attached enchantments
    for (int i = 0; i < this->enchants.size(); ++i) {
        delete this->enchants.at(i);
    }
}

// getter methods
int Minion::get_atk() const {
    return this->atk;
}

int Minion::get_def() const {
    return this->def;
}

int Minion::get_ability_cost() const {
    return this->active_ability_cost;
}

int Minion::get_actions() const {
    return this->action_counter;
}

// returns a pointer to the Minion's enchants
vector<Enchantment *> *Minion::get_enchants() {
    return &this->enchants;
}

// resets the Minion's action value
void Minion::reset_actions() {
    this->action_counter = this->actions_per_turn;
}

// attacks the specified player
void Minion::attack_player(Player *p) {
    if (action_counter <= 0) {
        cerr << "Can't attack--Minion has no more actions | \
Minion::attack_player() | minion.cc" << endl;
        return;
    }
    p->receive_damage(this->atk);
    action_counter -= 1;
}

// attack_minion() will modify the def of both Minions
void Minion::attack_minion(Minion *other) {
    if (action_counter <= 0) {
        cerr << "Can't attack--Minion has no more actions | \
Minion::attack_minion() | minion.cc" << endl;
        return;
    }
    // this Minion deals this->atk amount of damage to other and
    other->def -= this->atk;
    // other deals other->atk amount of damage to this
    this->def -= other->atk;
    action_counter -= 1;
}

// Uses a Minion's ability (whether its active, start/end of turn, or on 
// death/entry, we will perform checks in the method/ override it as neccessary)
bool Minion::use_ablility(
    int pnum, int owner, int index, int targetPlayer, int targetIndex, int type
) {
    if (type == ACTIVE_ABILITY && ability_type != ACTIVE_ABILITY) {
        cerr << "This minion has no active ability | Minion::use_ability() | \
minion.cc" << endl;
        return false;
    }
    if (type == ACTIVE_ABILITY && action_counter <= 0) {
        cerr << "Cant use active ability--Minion has no more actions | \
Minion::use_ability() | minion.cc" << endl;
        return false;
    }

    // do nothing if the wrong type of ability is called
    if (type != this->ability_type) return false;

    // trigger the ability of the Minion (the enchantments will modify the
    // ability of the minion when attached if applicable)
    if (!ability(pnum, owner, index, targetPlayer, targetIndex)) return false;
    
    // lower the action counter of this Minion by 1 if an active ability was used
    if (type == ACTIVE_ABILITY) this->action_counter -= 1;

    return true;
}

// These will modify the private fields of Minion based on the applied
// enchantment 
// Enchant will not not neccessarily cause modification to all of the
// included fields, but any modification is possible
void Minion::attach_enchantment(Enchantment *enchant) {
    // adds the enchantment to the vector of enchantments
    this->enchants.emplace_back(enchant);
    // then calls the attach_enchantment() method on the referenced 
    // Enchantment which modifies the fields of this
    enchant->attach_enchantment(this);
}

void Minion::detach_enchantment() {
    // if no enchantments attached, do nothing on the most recently
    if (this->enchants.size() == 0) return;
    // calls the detach_enchantment() method on the most recently
    // attached enchantment which modifies the fields of this
    enchants.back()->detach_enchantment(this);
    // finally, detach the enchantment
    enchants.pop_back();
}
