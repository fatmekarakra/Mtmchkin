#pragma once

#include <string>
using std::string;
class Player;

static const string RESPONSIBLE = "Responsible";
static const string RISKTAKING = "RiskTaking";

static const string WARRIOR = "Warrior";
static const string SORCERER = "Sorcerer";

static const int POTION_PRICE = 5;
static const int POTION_HEALTH = 10;


/**
 * A parent abstract class to describe player's jobs.
 * -    getJob          -   Returns the name of the job.
 * -    solarBuff       -   Applies a solar buff effect on the player.
 * -    getCombatPower  -   Returns the combat power of the player.
*/
class Job{
public:
    virtual ~Job() = default;

    virtual string getJob() const = 0;
    virtual int solarBuff(Player& player);
    virtual int getCombatPower(Player& player);
};


/**
 * Warrior job has a unique combat power calculation.
*/
class Warrior : public Job{
public:
    Warrior() = default;
    ~Warrior() override = default;

    string getJob() const override;
    int getCombatPower(Player& player) override;
};


/**
 * Sorcerer is affected positively bu the solarBuff
*/
class Sorcerer : public Job{
public:
    Sorcerer() = default;
    ~Sorcerer() override = default;


    string getJob() const override;
    int solarBuff(Player& player) override;
};



/**
 * An Abstract parent class to host all the personalities.
 * -    getPersonality  -   Returns the name of the personality.
 * -    buyPotions      -   Buys health potions and returns the amount bought.
*/
class Personality{
public:
    virtual ~Personality() = default;
    virtual string getPersonality() = 0;
    virtual int buyPotions(Player& player);
};


/**
 * Responsible personality buys as much as possible HP potions.
*/
class Responsible : public Personality{
public:
    Responsible() = default;
    ~Responsible() override = default;

    string getPersonality() override;
    int buyPotions(Player& player) override;
};


/**
 * RiskTaking personality buys HP potions only if in need and only buys one at a time.
*/
class RiskTaking : public Personality{
public:
    RiskTaking() = default;
    ~RiskTaking() override = default;

    string getPersonality() override;
    int buyPotions(Player& player) override;

private:
    static const int HP_THRESHHOLD = 50;
    static const int BOUGHT = 1;
    static const int DID_NOT_BUY = 0;
};


