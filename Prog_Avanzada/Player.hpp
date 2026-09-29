// Player.h
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Armor.hpp"

#define clamp(a,b,c)  std::min((c),std::max((a),(b)))

class Player {
    public:
    std::string name;
    void changeLife(int change);
    bool spendMoney(int change);
    void accelerate(float multiplier);
    void printPlayer() const;
    void takeDamage(int damage);
    void equipArmor(ARM::Armor armor);
    void printArmors() const;
    
    Player()
    : armor_()
    , x{0.0f}
    , y{0.0f}
    , speed{0.0f}
    , hp{100}
    , maxHp{100}
    , gold{50} {

    }

    ~Player(){
        for(int slot = 0; slot < kArmorSlots; ++slot){
            if(armor_[slot] == nullptr) break;
            delete armor_[slot];
        }
    }

    private:
    static constexpr unsigned char kArmorSlots = 10;
    static constexpr float minSpeed = 0.0f;
    static constexpr float maxSpeed = 10000.0f;
    ARM::Armor* armor_[kArmorSlots];
    float x = 0.0f;
    float y = 0.0f;
    float speed = 5.0f;
    int hp = 100;
    int maxHp = 100;
    int gold = 50;
};

void buyPotion(Player& p);
void fallInLava(Player& p);
void pickUpBoots(Player& p);

#endif // PLAYER_HPP
