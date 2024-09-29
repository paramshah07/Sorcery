#include <string>
#include <iostream>
#include "card.h"
#include "special_abilities.h"

using namespace std;

Card::~Card() {}

// getter methods
string Card::get_name() const {
    return this->name;
}

int Card::get_cost() const {
    return this->cost;
}

string Card::get_desc() const {
    return this->description;
}

// WTF IS THIS LMAOOOOO
bool (*Card::get_ability() const)(int, int, int, int, int) {
    return ability;
}
