#include "Player.hpp"

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

static void UnequipArmor(ARM::Armor** armor_slot){
    *armor_slot = nullptr;
}

static void DestroyArmor(ARM::Armor** armor_slot){
    delete *armor_slot;
    UnequipArmor(armor_slot);
}

static void ReorganizeArmorSlots(ARM::Armor** armor_slots, int unequipped_armor_pos, int num_of_slots){
    for(int i = unequipped_armor_pos; i < num_of_slots - 1; ++i){
        if(armor_slots[i + 1] == nullptr)   break;
        armor_slots[i] = armor_slots[i + 1];
        armor_slots[i + 1] = nullptr;
    }
}

void Player::takeDamage(int damage){
    for(int i = 0; i < kArmorSlots; i++){
        if((armor_[i] == nullptr)) continue;

        damage = (armor_[i])->applyDamageReduction(damage);
        if(armor_[i]->hasArmorBroken()){
            DestroyArmor(&armor_[i]);
            ReorganizeArmorSlots(armor_, i, kArmorSlots);
            i--;
        }
    }
    changeLife(-damage);
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

void Player::equipArmor(ARM::Armor armor){
    int slot = 0;
    for(slot; slot < kArmorSlots; slot++){
        if(armor_[slot] == nullptr) break;
    }

    if(slot == kArmorSlots) return; //TODO: informar al sistema

    armor_[slot] = new ARM::Armor{armor};
}

void Player::printArmors() const{
    for(int slot = 0; slot < kArmorSlots; slot++){
        if(armor_[slot] == nullptr)
            printf("[EMPTY]\n");
        else
            armor_[slot]->printArmor();
    }
}