#include <iostream>
#include "enchantment.h"

using namespace std;

Enchantment::~Enchantment() {}

// getter method to return correct value for each Enchantment
string Enchantment::get_atk_mod() const {
    return this->atk_mod;
}

string Enchantment::get_def_mod() const {
    return this->def_mod;
}

bool Enchantment::use_ablility(
    int pnum, int owner, int index, int targetPlayer, int targetIndex, int type
) {
    // do nothing because enchentments will never have their use_ability
    // functions called.
    cerr << "called Enchantment::use_ablility() | enchantment.cc" << endl;
    return true;
}
