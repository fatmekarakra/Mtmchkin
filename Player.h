#pragma once

#include <string>
#include <memory>

#include "Types.h"

using std::unique_ptr;
using std::string;

class Job;              // To enable use of the class.
class Personality;      // To enable use of the class.


/**
 * The Player class describes a player and handles all of its functionality.
 * Each Player is defined by a name, job, personality, level, force, healthPoints and coins.
 * For each value exists a getter.
 * The following methods are available:
 * -    C'tor           -   Constructs the player by a name, job and personality.
 * -    Copy C'tor      -   Copies and existing player.
 * -    setPersonality  -   Changes the player's personality to the passed personality.
 * -    setJob          -   Changes the player's job to the passed job.
 * -    setForce        -   Changes the player's job to the passed value, if less than zero then changes it to zero.
 * -    HPIsFull        -   Returns true if the player's health is full.
 * -    payCoins        -   Takes the passed amount out of the player's coins.
 * -    earnCoin        -   Adds the passed value to the player's coins.
 * -    levelUp         -   Adds one level to the player.
 * -    buff            -   Adds the passed value to the player's force.
 * -    heal            -   Adds the passed value to the player's HealthPoints.
 * -    damage          -   Takes the passed value out of the player's force.
 * -    isKnokedOut     -   Returns true if the player's HealthPoints are zero.
 * -    
*/
class Player {
public:

    /**
     * C'tor for the player.
     * @param name          -   The name for the player.
     * @param job           -   The job of the player.
     * @param personality   -   The player's personality.
     * The rest of the values are set to default.
    */
    Player(const string name, const string job, const string personality);
    

    /**
     * Copy C'tor for the player.
    */
    Player(const Player& player);

    ~Player() = default;

    Player& operator=(const Player& player);


    /**
     * Sets the player's personality to a given one.
     * @param personality   -   The new personality to use.
    */
    void setPersonality(const string personality);

    
    /**
     * Sets the player's job to a new given one.
     * @param job   -   The new job to have.
    */
    void setJob(const string job);


    /**
     * Modifies the player's force to the given one.
     * @param force -   The new force to have.
    */
    void setForce(const int force);

    /**
     * Checks whether a player's HP is full or not.
    */
    bool HPIsFull() const;

    /**
     * Takes out the price out of the player's coins if possible (No debt is allowed).
     * @param price -   The price to pay.
    */
    void payCoins(const int price);

    /**
     * Adds the coins to the player's coins.
     * @param coins -   The amount to add to the player's existing coin amount.
    */
    void earnCoins(const int coins);

    /**
     * Adds a level to the player.
    */
    void levelUp();

    /**
     * Adds the force to the player's existing force if the amount is non-negative.
     * @param force -   The amount to add.
    */
    void buff(const int force);

    /**
     * Adds the amount to the player's existing HP. If the HP passes the maximum HP then it is returned to the
     * maximum HP.
     * @param added -   The amount to add.
    */
    void heal(const int addedHP);

    /**
     * Takes out the amount passed out of the player's health, if the new HP is less than zero then 
     * it is changed back to zero.
     * @param damage    -   The amount to take out.
    */
    void damage(const int damage);

    /**
     * Checks whether a player is dead or not.
    */
    bool isKnockedOut() const;

    /**
     * Applies the solar buff effect on the player.
     * 
     * @return  -   The change on the player.
    */
    int solarBuff();


    /**
     * Buys health potions for the player.
     * 
     * @return  -   The amount bought.
    */
    int buyPotions();

    /**
     * Gets the description of the player
     * 
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     * 
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     * 
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     * 
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     * 
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     * 
     * @return - coins of the player
    */
    int getCoins() const;

    /**
     * Gets the amount of Combat Power according the player's job.
     * 
     * @return  -   The player's comabt power.
    */
    int getCombatPower();

    /**
     * Gets the player's personality.
     * 
     * @return  -   The player's personality.
    */
    string getPersonality() const;

    /**
     * Gets the player's job.
     * 
     * @return  -   The player's job.
    */
    string getJob() const;


private:
    unique_ptr<Personality> m_personality;
    unique_ptr<Job> m_job;

    string name;
    int level;
    int force;
    int HP;
    int coins;

    static const int MAX_LEVEL = 10;
    static const int MAX_HP = 100;
    static const int STARTING_FORCE = 5;
    static const int STARTING_COINS = 10;
    static const int STARTING_LEVEL = 1;
};





