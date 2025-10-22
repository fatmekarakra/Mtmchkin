#include "Player.h"
#include "Types.h"

#include <string>
#include <memory>
using std::unique_ptr;
using std::string;




Player::Player(const string name, const string job, const string personality) : 
        m_personality(), m_job(), name(name), level(STARTING_LEVEL), force(STARTING_FORCE), HP(MAX_HP),
         coins(STARTING_COINS){
    setPersonality(personality);
    setJob(job);
}


Player::Player(const Player& player) : 
         m_personality(), m_job(), name(player.getName()), level(player.getLevel()),
        force(player.getForce()), HP(player.getHealthPoints()), coins(player.getCoins()){
    setPersonality(player.m_personality->getPersonality());
    setJob(player.m_job->getJob());
}

void Player::setPersonality(const string personality){
    unique_ptr<Personality> new_personality;
    if (personality == RESPONSIBLE){
        new_personality = unique_ptr<Responsible>(new Responsible());
    } else if (personality == RISKTAKING){
        new_personality = unique_ptr<RiskTaking>(new RiskTaking());
    }
    m_personality = move(new_personality);
}


void Player::setJob(const string job){
    unique_ptr<Job> new_job;
    if (job == WARRIOR){
        new_job = unique_ptr<Warrior>(new Warrior());
    } else if (job == SORCERER){
        new_job = unique_ptr<Sorcerer>(new Sorcerer());
    }
    m_job = move(new_job);
}


string Player::getDescription() const{
    return this->getName() + ", " + this->m_job->getJob() + " with " + this->m_personality->getPersonality()
        + " behavior (level " + std::to_string(this->getLevel()) + ", " + "force "
        + std::to_string(this->getForce()) + ")";
    
}


Player& Player::operator=(const Player& player){
    name = player.getName();
    level = player.getLevel();
    force = player.getForce();
    HP = player.getHealthPoints();
    coins = player.getCoins();
    setJob(player.getJob());
    setPersonality(player.getPersonality());
    return *this;
}



string Player::getName() const{
    return name;
}

int Player::getLevel() const{
    return level;
}

int Player::getForce() const{
    return force;
}

int Player::getHealthPoints() const{
    return HP;
}

int Player::getCoins() const{
    return coins;
}

void Player::earnCoins(const int coins){
    if (coins < 0) return;
    this->coins += coins;
}

void Player::setForce(const int force){
    this->force = force;
}

bool Player::HPIsFull() const{
    return HP == MAX_HP;
}

void Player::levelUp(){
    if (level < MAX_LEVEL){
        level++;
    }
}

void Player::payCoins(const int price){
    if (price > this->coins) return;
    this->coins -= price;
}

void Player::buff(int force){
    if (force < 0){
        return;
    }
    this->force += force;
}

void Player::damage(const int damage){
    if (damage < 0){
        return;
    }
    this->HP -= damage;
    if (this->HP < 0){
        this->HP = 0;
    } 
}


bool Player::isKnockedOut() const{
    return (this->HP == 0);
}

void Player::heal(int addedHP){
    if(addedHP > 0){
        this->HP += addedHP;
        if (this->HP > this->MAX_HP){
            this->HP = this->MAX_HP;
        }
    }
}



int Player::getCombatPower(){
    return this->m_job->getCombatPower(*this);
}


int Player::solarBuff(){
    return this->m_job->solarBuff(*this);
}


int Player::buyPotions(){
    return this->m_personality->buyPotions(*this);
}


string Player::getPersonality() const{
    return this->m_personality->getPersonality();
}


string Player::getJob() const{
    return this->m_job->getJob();
}