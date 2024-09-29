#include "raise_dead.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Spell to its specified base stats
RaiseDead::RaiseDead() {
    this->name = "Raise Dead";
    this->cost = 1;
    this->description = "Resurrect the top minion in your graveyard and set its defence to 1.";
    this->ability = SpecialAbilities::raise_dead;
}

// dtor doesnt need to do anything special
RaiseDead::~RaiseDead() {}
