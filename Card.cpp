#include "Card.h"
#include "utilities.h"
#include "../Players/Player.h"
#include "../Players/Types.h"

#include <memory>
using std::unique_ptr;

#include <iostream>
using namespace std;




/**
 * Initilizes the stats for Encounter type cards.
*/
Encounter::Encounter(string name, int combatPower, int loot, int damage):
        combatPower(combatPower), loot(loot), damage(damage), name(name){};


/**
 * Encounters are defined by the players combat power according to their job.
 * The function returns the result of the encounter.
*/
string Encounter::playCard(Player& player) const{
    if (player.getCombatPower() > this->getPower()){        //Player Won!
         player.levelUp();
         player.earnCoins(this->getLoot());
         return getEncounterWonMessage(player, this->getLoot());
    } 
    else                                                            //Player Lost!
    {
        player.damage(this->getDamage());
        return getEncounterLostMessage(player, this->getDamage());
    }
}


/**
 * The following are all getters for Encounter Cards -----------
*/
string Encounter::getName() const{
    return this->name;
}

int Encounter::getDamage() const{
    return this->damage;
}

int Encounter::getLoot() const{
    return this->loot;
}

int Encounter::getPower() const{
    return this->combatPower;
}


/**
 * Returns a string containing a description of an encounter card according to its values.
*/
string Encounter::getDescription() const{
    string description = this->getName() + " (power " + std::to_string(this->getPower()) + ", loot "
     + std::to_string(this->getLoot()) + ", damage " + std::to_string(this->getDamage()) + ")";
    return description;
}


/**
 * The following are all C'tors for specific Encouter type cards that all call the Encounter parent
 * by their default values. 
*/
Goblin::Goblin():
        Encounter(GOBLIN, Goblin_POWER, Goblin_LOOT, Goblin_DAMAGE){};

Giant::Giant():
        Encounter(GIANT, GIANT_POWER,GIANT_LOOT,GIANT_DAMAGE){};

Dragon::Dragon():
        Encounter(DRAGON, DRAGON_POWER,DRAGON_LOOT,DRAGON_DAMAGE){};

Gang::Gang():
        Encounter(GANG, NO_DATA, NO_DATA, NO_DATA){};


/**
 * The following are the custom getters for the gang card.
*/
int Gang::getPower() const{
    int sum = 0;
    for (long unsigned int i = 0; i < members.size() ; i++){
        sum += members.at(i)->getPower();
    }
    return sum;
}

int Gang::getLoot() const{
    int sum = 0;
    for (long unsigned int i = 0; i < members.size() ; i++){
        sum += members.at(i)->getLoot();
    }
    return sum;

}

int Gang::getDamage() const{
    int sum = 0;
    for (long unsigned int i = 0; i < members.size() ; i++){
        sum += members.at(i)->getDamage();
    }
    return sum;

}

/**
 * Adds a memeber to the gang, recievs the name that shoud be added and makes an Encounter card accordingly
 * and adds all of the cards values to the gang total values.
 * The function assumes correct use, @param name should be an exisiting Encouter type.
*/
void Gang::addMember(const string name){
    unique_ptr<Encounter> new_member;
    if (name == GOBLIN){
        new_member = unique_ptr<Goblin>(new Goblin());
    } else if (name == GIANT){
        new_member = unique_ptr<Giant>(new Giant());
    } else if (name == DRAGON){
        new_member = unique_ptr<Dragon>(new Dragon());
    }
    this->members.push_back(move(new_member));
}


void Gang::pushMember(unique_ptr<Gang> gang){
    this->members.push_back(move(gang));
}


/**
 * Custom getter for the name of the gang that contains the size of the gang.
*/
string Gang::getName() const{
    string name = "Gang of " + std::to_string(members.size()) + " members";
    return name;
}


/**
 * Returns the name of the event, SolarEcilpse.
*/
string SolarEclipse::getDescription() const{
    return SOLARECLIPSE;
}


/**
 * Calls the effect of the solar ecilpse on a player according to it's job.
 * The function returns the result of the event.
*/
string SolarEclipse::playCard(Player& player) const{
    int effect = player.solarBuff();
    return getSolarEclipseMessage(player, effect);
}


/**
 * Returns the name of the event, PostionsMerchant.
*/
string PotionsMerchant::getDescription() const{
    return POTIONSMERCHANT;
}


/**
 * Calls the effect of the solar ecilpse on a player according to it's job.
 * The function returns the result of the event.
*/
string PotionsMerchant::playCard(Player& player) const{
    int amount = player.buyPotions();
    return getPotionsPurchaseMessage(player, amount);
}
