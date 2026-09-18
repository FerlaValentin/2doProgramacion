// Player.h
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdio>
#include <string>

#define clamp(a,b,c)  std::min((a),std::max((b),(c)))

class Player {
    public:
    std::string name;
    void increaseLife(int change);
    bool spendMoney(int change);
    void accelerate(int change);
    void printPlayer();
    
    private:
    float x = 0.0f;
    float y = 0.0f;
    float speed = 5.0f;
    int hp = 100;
    int maxHp = 100;
    int gold = 50;
    //speed ente minSpeed y maxSpeed
    int minSpeed = 0;
    int maxSpeed = 10000;
};

void buyPotion(Player& p);
void fallInLava(Player& p);
void pickUpBoots();

#endif // PLAYER_HPP

//Player.cpp
#include <Player.hpp>

void Player::increaseLife(int change) {
    hp = clamp(0, hp + change, maxHp);
}

bool Player::spendMoney(int change) {
    if(gold-change < 0) return false;
    gold -= change;
    return true;
}

void Player::accelerate(int change){
    speed = clamp(minSpeed, change, maxSpeed);
}

void Player::printPlayer() {
    printf("%s | pos(%g, %g) | hp %d/%d | gold %d | speed %g\n",
           name.c_str(), x, y, hp, maxHp, gold, speed);
}

void buyPotion(Player& p) {
    if(p.spendMoney(30)) {
        p.increaseLife(40);
    } else {
        printf( "estas pelao");
    }
}

void fallInLava(Player& p) {
    p.increaseLife(-150);
}

void pickUpBoots(Player& p) {
    p.accelerate(speed * 10);
}


// game.cpp
#include <Player.hpp>

int main() {
    Player hero;
    hero.name = "Aria";
    //printPlayer(hero);

    int precioArmadura = 200;
    if(hero.spendMoney(precioArmadura)) {
        //equipar armadura
    } else {
        printf("estas pelao!");
    }

    hero.buyPotion();
    printPlayer(hero);

    hero.buyPotion();
    printPlayer(hero);

    hero.pickUpBoots();
    hero.pickUpBoots();
    printPlayer(hero);

    hero.fallInLava();
    hero.fallInLava();
    printPlayer(hero);

    return 0;
}
