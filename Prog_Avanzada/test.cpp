#include "Player.hpp"

#include <cstdio>
#include <cmath>

#include "Armor.hpp"

void Player::changeLife(int change) {
    hp = clamp(0, hp + change, maxHp);
}

bool Player::spendMoney(int change) {
    if(gold-change < 0) return false;
    gold -= change;
    return true;
}

void Player::accelerate(float multiplier){
    speed = clamp(minSpeed, speed * multiplier, maxSpeed);
}

void Player::printPlayer() const{
    printf("%s | pos(%g, %g) | hp %d/%d | gold %d | speed %g\n",
           name.c_str(), x, y, hp, maxHp, gold, speed);
}

void Player::takeDamage(int damage){
    for(int i = 0; i < kArmorSlots; i++){
        if((armor_[i] == nullptr)) continue;

        damage = (armor_[i])->applyDamageReduction(damage);
        if(armor_[i]->hasArmorBroken()){
            delete armor_[i];
            armor_[i] = nullptr;
        }
    }
    changeLife(-damage);
}

int ARM::Armor::applyDamageReduction(int damage){
    const int absorbed_damage = std::ceil(damage * proteccion_);

    vida_ = std::max(0, vida_ - absorbed_damage);

    return damage - absorbed_damage;
}

void buyPotion(Player& p) {
    if(p.spendMoney(30)) {
        p.changeLife(40);
    } else {
        printf( "estas pelao!\n");
    }
}

void fallInLava(Player& p) {
    p.changeLife(-150);
}

void pickUpBoots(Player& p) {
    p.accelerate(10);
}

int main() {
    Player hero;
    ARM::Armor armor;
    hero.name = "Aria";
    hero.printPlayer();

    int precioArmadura = 200;
    if(hero.spendMoney(precioArmadura)) {
        //equipar armadura
    } else {
        printf("estas pelao!\n");
    }

    buyPotion(hero);
    hero.printPlayer();

    buyPotion(hero);
    hero.printPlayer();

    pickUpBoots(hero);
    pickUpBoots(hero);
    hero.printPlayer();

    fallInLava(hero);
    fallInLava(hero);
    hero.printPlayer();

    return 0;
}
