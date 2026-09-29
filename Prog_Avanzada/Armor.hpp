#ifndef ARMOR_H
#define ARMOR_H

namespace ARM{
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
    bool hasArmorBroken() const {return vida_ == 0;}
    
    private:
    int vida_;
    float proteccion_;
    };
}

#endif