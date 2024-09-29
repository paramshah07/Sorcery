#include "silence.h"
#include "minion.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Enchantment to its specified base stats
Silence::Silence() {
    this->name = "Silence";
    this->cost = 1;
    this->description = "Enchanted minion cannot use abilities.";
    this->atk_mod = "";
    this->def_mod = "";
}

// dtor doesnt need to do anything special
Silence::~Silence() {}

// attaches to, and modifies mp
void Silence::attach_enchantment(Minion *mp) {
    // for ability-changing Enchantments, record mp's previous ability
    // before overriding it with the new ability
    this->prev_ability = mp->ability;
    mp->ability = this->ability;

    // also record mp's previous active ability cost (if mp had an active 
    // ability) before overriding it with the cost
    if (mp->ability_type == ACTIVE_ABILITY) {
        this->prev_active_ability_cost = mp->active_ability_cost;
        mp->active_ability_cost = this->active_ability_cost;
    }

    // also do the same for the ability type
    this->prev_ability_type = mp->ability_type;
    mp->ability_type = this->ability_type;
}

// detaches from, and modifies mp
void Silence::detach_enchantment(Minion *mp) {
    // then when we detach the Enchantment, we everything we did in the
    // attach_enchantment() method

    // revert mp's old abilty_type
    mp->ability_type = this->prev_ability_type;
    this->prev_ability_type = NO_ABILITY;

    // rever mp's old active ability cost (if applicable)
    if (mp->ability_type == ACTIVE_ABILITY) {
        mp->active_ability_cost = this->prev_active_ability_cost;
        this->prev_active_ability_cost = -1;
    }

    // revert mp's old ability
    mp->ability = this->prev_ability;
    this->prev_ability = nullptr;
}
