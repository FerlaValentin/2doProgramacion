// Player.h
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdio>
#include <string>

#define clamp(a,b,c)  std::min((c),std::max((a),(b)))

class Armor {
    public:
    Armor()
    : vida_{100}
    , proteccion_{0.1f}{

    }

    Armor(int vida, float proteccion)
    : vida_{vida}
    , proteccion_{proteccion} {

    }

    int applyDamageReduction(int damage);
    bool hasArmorBroken(){
        return vida_ == 0;
    }
    
    private:
    int vida_;
    float proteccion_;
};

class Player {
    public:
    std::string name;
    void changeLife(int change);
    bool spendMoney(int change);
    void accelerate(float multiplier);
    void printPlayer();
    void takeDamage(int damage);
    void equipArmor(Armor armor){
        int slot = 0;
        for(slot; slot < kArmorSlots; slot++){
            if(armor_[slot] == nullptr) break;
        }

        if(slot == kArmorSlots) return; //TODO: informar al sistema

        armor_[slot] = new Armor{armor};
    };
    
    Player()
    : armor_()
    , x{0.0f}
    , y{0.0f}
    , speed{0.0f}
    , hp{100}
    , maxHp{100}
    , gold{50} {

    }
    private:
    static constexpr unsigned char kArmorSlots = 10;
    static constexpr float minSpeed = 0.0f;
    static constexpr float maxSpeed = 10000.0f;
    Armor* armor_[kArmorSlots];
    float x = 0.0f;
    float y = 0.0f;
    float speed = 5.0f;
    int hp = 100;
    int maxHp = 100;
    int gold = 50;
};

void buyPotion(Player& p);
void fallInLava(Player& p);
void pickUpBoots();

#endif // PLAYER_HPP
