#include "Player.h"

void Player::increaseLife(int change) {
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

void Player::printPlayer() {
    printf("%s | pos(%g, %g) | hp %d/%d | gold %d | speed %g\n",
           name.c_str(), x, y, hp, maxHp, gold, speed);
}

void buyPotion(Player& p) {
    if(p.spendMoney(30)) {
        p.increaseLife(40);
    } else {
        printf( "estas pelao!\n");
    }
}

void fallInLava(Player& p) {
    p.increaseLife(-150);
}

void pickUpBoots(Player& p) {
    p.accelerate(10);
}

int main() {
    Player hero;
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
