// Player.h
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdio>
#include <string>

#define clamp(a,b,c)  std::min((c),std::max((a),(b)))

class Player {
    public:
    std::string name;
    void increaseLife(int change);
    bool spendMoney(int change);
    void accelerate(float multiplier);
    void printPlayer();
    
    private:
    float x = 0.0f;
    float y = 0.0f;
    float speed = 5.0f;
    int hp = 100;
    int maxHp = 100;
    int gold = 50;
    //speed ente minSpeed y maxSpeed
    float minSpeed = 0.0f;
    float maxSpeed = 10000.0f;
};

void buyPotion(Player& p);
void fallInLava(Player& p);
void pickUpBoots();

#endif // PLAYER_HPP
