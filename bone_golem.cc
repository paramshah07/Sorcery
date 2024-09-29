#include "bone_golem.h"
#include "special_abilities.h"

using namespace std;

// ctor constructs the corresponding Minion to its specified base stats
BoneGolem::BoneGolem() {
    this->name = "Bone Golem";
    this->cost = 2;
    this->description = "Gain +1/+1 whenever a minion leaves play.";
    this->atk = 1;
    this->def = 3;
    this->ability_type = ON_MINION_EXIT;
    this->ability = SpecialAbilities::bone_golem;
}

// dtor doesnt need to do anything special
BoneGolem::~BoneGolem() {}
