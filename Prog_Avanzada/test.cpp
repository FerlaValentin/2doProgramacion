#include <cstdio>

#include "Player.hpp"
#include "Armor.hpp"

int main() {
    Player hero;
    ARM::Armor helmet(100, 0.2f), chestplate(100, 0.75f), leggings(100, 0.4f), boots(100, 0.1f);
    hero.name = "Aria";
    hero.printPlayer();

    int precioArmadura = 50;
    if(hero.spendMoney(precioArmadura)) {
        hero.equipArmor(helmet);
        hero.equipArmor(chestplate);
        hero.equipArmor(leggings);
        hero.equipArmor(boots);
        hero.printArmors();
    } else {
        printf("estas pelao!\n");
    }

    hero.takeDamage(200);
    hero.printPlayer();
    hero.printArmors();

    // buyPotion(hero);
    // hero.printPlayer();

    // buyPotion(hero);
    // hero.printPlayer();

    // pickUpBoots(hero);
    // pickUpBoots(hero);
    // hero.printPlayer();

    // fallInLava(hero);
    // fallInLava(hero);
    // hero.printPlayer();

    return 0;
}
