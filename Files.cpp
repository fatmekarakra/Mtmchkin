#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <cctype>

#include "./Players/Player.h"
#include "./Cards/Card.h"
#include "Files.h"

using namespace std;

static const int MAX_NUMBER_OF_PLAYER = 6;
static const int MIN_NUMBER_OF_PLAYER = 2;
static const int MIN_NUMBER_OF_CARDS = 2;
static const int SHORTEST_NAME = 3;
static const int LONGEST_NAME = 15;
static const int MIN_NUMBER_OF_MONSTERS = 2;

void GangAdder(Gang &gang, ifstream &source);
bool validName(string name);


void playerFiles(vector<Player>& players, const string sourceFileName){
    ifstream source(sourceFileName);
    if (!source) {
        throw PlayerErrors();
    }
    
    string line;
    try {
        while (getline(source, line)) {
            stringstream ss(line);

            string playerName;
            ss >> playerName;
            if(!validName(playerName)){
                throw PlayerErrors();
            }

            string playerJob;
            ss >> playerJob;
            if((playerJob != "Sorcerer") && (playerJob != "Warrior")){
                throw PlayerErrors();
            }

            string playerBehavior;
            ss >> playerBehavior;
            if((playerBehavior != "Responsible") && (playerBehavior != "RiskTaking")){
                throw PlayerErrors();
            }

            Player player(playerName, playerJob, playerBehavior);
            players.push_back(player);

            if (ss >> playerName) throw PlayerErrors();
        }

        if(players.size() > MAX_NUMBER_OF_PLAYER || players.size() < MIN_NUMBER_OF_PLAYER){
            throw PlayerErrors();
        }
    }
    catch (...) {
        throw PlayerErrors();
    }
}



void cardFiles(vector<unique_ptr<Card>>& Cards, const string sourceFileName){

    ifstream source(sourceFileName);
    if (!source) {
        throw CardErrors();
    }

    string cardName;
    bool no_ecnounter = true;

    while (source >> cardName) {

        if(cardName == GOBLIN)
        {   
            no_ecnounter = false;
            Cards.push_back(unique_ptr<Goblin>(new Goblin()));
        } 
        else if(cardName == DRAGON)
        {
            no_ecnounter = false;
            Cards.push_back(unique_ptr<Dragon>(new Dragon()));
        }
        else if(cardName == GIANT)
        {
            no_ecnounter = false;
            Cards.push_back(unique_ptr<Giant>(new Giant()));
        }
        else if (cardName == GANG)
        {
            no_ecnounter = false;
            unique_ptr<Gang> new_member = unique_ptr<Gang>(new Gang());
            GangAdder(*new_member, source);
            Cards.push_back(move(new_member));
        }
        else if (cardName == SOLARECLIPSE)
        {
            Cards.push_back(unique_ptr<SolarEclipse>(new SolarEclipse()));
        }
        else if (cardName == POTIONSMERCHANT)
        {
            Cards.push_back(unique_ptr<PotionsMerchant>(new PotionsMerchant()));
        }
        else{
            throw CardErrors();
        }
    }

    if(Cards.size() < MIN_NUMBER_OF_CARDS || no_ecnounter){
        throw CardErrors();
    }
}



void GangAdder(Gang &gang, ifstream &source){  
    string size;
    int gangSize;
    string cardName;

    source >> size;
    try {
        gangSize = stoi(size);
    } 
    catch (...) {
        throw CardErrors();
    }
    if(gangSize < MIN_NUMBER_OF_MONSTERS){
        throw CardErrors();
    }

    for(int i = 0; i < gangSize; i++){
        if(!(source >> cardName)) throw CardErrors();

        if((cardName != GOBLIN) && (cardName != DRAGON) && (cardName != GANG) && (cardName != GIANT)){
            throw CardErrors();
        }
        if (cardName == GANG){
            unique_ptr<Gang> inner_gang = unique_ptr<Gang>(new Gang());
            GangAdder(*inner_gang, source);
            gang.pushMember(move(inner_gang));
        }
        else
        {
            gang.addMember(cardName);
        }
    }
}


bool validName(string name){
    if (name.size() < SHORTEST_NAME || name.size() > LONGEST_NAME){
        return false;
    }
    for (char ch : name) {
        if (!isalpha(ch)) {
            return false;
        }
    }
    return true;
}