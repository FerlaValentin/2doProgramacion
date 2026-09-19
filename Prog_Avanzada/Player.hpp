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
    
    private:
    int vida_;
    float proteccion_;
};

struct Life {int v;};
struct Damage {int v;
    operator Life() {return Life(-v);}
}

class Player {
    public:
    std::string name;
    void changeLife(int change);
    bool spendMoney(int change);
    void accelerate(float multiplier);
    void printPlayer();
    void takeDamage(int damage) {
        changeLife(armor_.applyDamageReduction(damage));
    };
    void equipArmor(Armor armor){
        int slot = 0;
        for(slot; slot < 10; slot++){
            if(armor_[slot] == nullptr) break;
        }

        if(slot == 10) return; //TODO: informar al sistema

        armor_[slot] = new Armor{armor};
    };
    
    Player()
    : armor_(0)
    , x{0.0f}
    , y{0.0f}
    , speed{0.0f}
    , hp{100}
    , maxHp{100}
    , gold{50} {

    }
    private:
    Armor armor_ = {0, 0.0f};
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
