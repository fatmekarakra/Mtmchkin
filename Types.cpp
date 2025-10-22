#include "Types.h"
#include "Player.h"


int Job::solarBuff(Player& player){
    int force =  (player.getForce() < 1) ? 0 : -1;
    player.setForce(player.getForce() + force);
    return force;
}


int Job::getCombatPower(Player& player){
    return player.getForce() + player.getLevel();
}




int Sorcerer::solarBuff(Player& player){
    player.setForce(player.getForce() + 1);
    return 1;
}

int Warrior::getCombatPower(Player& player){
    return player.getForce() * 2 + player.getLevel();
}



string Warrior::getJob() const{
    return WARRIOR;
}


string Sorcerer::getJob() const{
    return SORCERER;
}




int Personality::buyPotions(Player& player){
    return 0;
}


int Responsible::buyPotions(Player& player){
    int counter = 0;
    while (!player.HPIsFull() && player.getCoins() >= POTION_PRICE){
        counter++;
        player.heal(POTION_HEALTH);
        player.payCoins(POTION_PRICE);
    }
    return counter;
}

int RiskTaking::buyPotions(Player& player){
    if (player.getHealthPoints() < HP_THRESHHOLD && player.getCoins() >= POTION_PRICE){
        player.heal(POTION_HEALTH);
        player.payCoins(POTION_PRICE);
        return BOUGHT;
    }
    return DID_NOT_BUY;
}



string Responsible::getPersonality(){
    return RESPONSIBLE;
}


string RiskTaking::getPersonality(){
    return RISKTAKING;
}
