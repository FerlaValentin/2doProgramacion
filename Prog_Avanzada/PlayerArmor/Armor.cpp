#include "Armor.hpp"

#include <string>
#include <cmath>

int ARM::Armor::applyDamageReduction(int damage){
    const int absorbed_damage = std::ceil(damage * proteccion_);

    vida_ = std::max(0, vida_ - absorbed_damage);

    return damage - absorbed_damage;
}

void ARM::Armor::printArmor() const{
    printf("[ARMOR [VIDA]: %d [PROTECCION]: %0.2f]\n", vida_, proteccion_);
}