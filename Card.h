#pragma once

#include "../Players/Player.h"

#include <string>
#include <vector>
#include <memory>

using std::unique_ptr;
using std::string;


static const string GOBLIN = "Goblin";
static const string GIANT = "Giant";
static const string DRAGON = "Dragon";
static const string GANG = "Gang";
static const string SOLARECLIPSE = "SolarEclipse";
static const string POTIONSMERCHANT = "PotionsMerchant";


/**
 * Parent abstract Class that all card types inherit from.
 * Cards are split to two groups: Event, Encounter.
 * Common functions that exist to all cards:
 * -    getDescription -  Returns a string with descriptoin of the card.
 * -    playCard -  Plays  the card on the given player that used the card.    
*/
class Card{
public:
    /**
     * Gets the description of the card
     *
     * @return - the description of the card
    */
    virtual string getDescription() const = 0;
    
    /**
     * Plays the card on the given player.
     * @param player - The player that played card.
    */
    virtual string playCard(Player& player) const = 0;

    virtual ~Card() = default;

};


/**
 * Parent class for all Encounter type cards.
 * Common functions for all encounter type cards:
 * -    getName    -   Returns the name of the card.
 * -    getPower    -   Returns the combat power of the card.
 * -    getLoot     -   Returns the loot amount of the card.
 * -    getDamage   -   Returns the damage of the card.
 * -    getDescription  -   Returns a string with the description of the card and its details.
 * Each Encounter Card is defined by a name, combat power, loot and damage.
*/
class Encounter : public Card{
public:
    Encounter(string name, int combatPower, int loot, int damage);
    virtual ~Encounter() = default;

    virtual string getName() const;
    virtual int getPower() const;
    virtual int getLoot() const;
    virtual int getDamage() const;
    string getDescription() const;
    string playCard(Player& player) const override;

protected:
    int combatPower;
    int loot;
    int damage;
    string name;
};


/**
 * Goblin is an Encouter type Card.
 * It's paramaeters are constant and can't be modified.
*/
class Goblin :public Encounter{
public:
    Goblin();
    ~Goblin() override = default;

private:
    static const int Goblin_POWER = 5;
    static const int Goblin_LOOT = 2;
    static const int Goblin_DAMAGE = 10;

};


/**
 * Giant is an Encouter type Card.
 * It's paramaeters are constant and can't be modified.
*/
class Giant :public Encounter {
public:
    Giant();
    ~Giant() override = default;

private:
    static const int GIANT_POWER = 12;
    static const int GIANT_LOOT = 5;
    static const int GIANT_DAMAGE = 25;
};


/**
 * Dragon is an Encouter type Card.
 * It's paramaeters are constant and can't be modified.
*/
class Dragon :public Encounter {
public:
    Dragon();
    ~Dragon() override = default;

private:
    static const int DRAGON_POWER = 17;
    static const int DRAGON_LOOT = 100;
    static const int DRAGON_DAMAGE = 9001;

};


/**
 * Gang is an Encouter type Card.
 * It is unique by that it doesn't have any default values, instead it contains a group of other
 * Encouter type cards. 
 * C'tor returns an empty Gang.
 * -    addMember   -   adds an encouter card by name to the gang and adds its corresponding values to the
 *                      gang total values.
 * -    getName     -   returns a string with the gang member count.
*/
class Gang :public Encounter{
public:
    Gang();
    ~Gang() override = default;

    /**
     * Adds a member to the gang that called the function.
     * @param name -    The name of the encounter type that should be added
    */
    void addMember(const string name);

    void pushMember(unique_ptr<Gang> gang);

    string getName() const override;

    /**
     * The getters return the sum of the stats of all of the members.
    */
    int getPower() const override;
    int getLoot() const override;
    int getDamage() const override;

private:
    std::vector<unique_ptr<Encounter>> members;
    static const int NO_DATA = 0;
};





/**
 * Event type Cards are used to describe events that affect the player.
 * The Event class is a parent abstract class with two functions to use:
 * -    getDescription  -   Returns a string containing a description of the event.
 * -    playCard        -   Plays the effect of the card on the player accordingly.
*/
class Event: public Card{
public:
    virtual string getDescription() const = 0;
    virtual string playCard(Player& player) const = 0;
    virtual ~Event() = default;
};


/**
 * The Solar Eclipse modifies players force according to their jobs.
 * -    getDescription  -   Returns a string containing a description of the event.
 * -    playCard        -   Plays the effect of the card on the player accordingly.
*/
class SolarEclipse: public Event{
public:
    SolarEclipse() = default;
    ~SolarEclipse() override = default;


    string getDescription() const override;
    string playCard(Player& player) const override;
};


/**
 * The potions Merchant sells health potions that heal the player for a price.
 * Each player buys from the merchant according to their personality.
 * -    getDescription  -   Returns a string containing a description of the event.
 * -    playCard        -   Plays the effect of the card on the player accordingly.
*/
class PotionsMerchant: public Event{
public:
    PotionsMerchant() = default;
    ~PotionsMerchant() override = default;


    string getDescription() const override;
    string playCard(Player& player) const override;
};
