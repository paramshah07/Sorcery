#include "magic_fatigue.h"
#include "minion.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Enchantment to its specified base stats
MagicFatigue::MagicFatigue() {
    this->name = "Magic Fatigue";
    this->cost = 0;
    this->description = "Enchanted minion's activated ability costs 2 more.";
    this->atk_mod = "";
    this->def_mod = "";
}

// dtor doesnt need to do anything special
MagicFatigue::~MagicFatigue() {}

// attaches to, and modifies mp
void MagicFatigue::attach_enchantment(Minion *mp) {
    // modifies only if mp has an active ability
    if (mp->ability_type == ACTIVE_ABILITY) {
        mp->active_ability_cost += 2;
    }
}

// detaches from, and modifies mp
void MagicFatigue::detach_enchantment(Minion *mp) {
    // modifies only if mp has an active ability
    if (mp->ability_type == ACTIVE_ABILITY) {
        mp->active_ability_cost -= 2;
    }
}
