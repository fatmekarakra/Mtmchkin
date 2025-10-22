using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "./Players/Player.h"
#include "./Cards/Card.h"

/**
 * Handles Reading a file for the players or Cards.
 * Returns an error if one occurs respectivly.
*/

class PlayerErrors : public runtime_error {
public:
    PlayerErrors() : runtime_error("Invalid Players File") {}
};

class CardErrors : public runtime_error {
public:
    CardErrors() : runtime_error("Invalid Cards File") {}
};


/**
 * Reads a file containing player names and returns a vector of the players.
 * @param sourceFileName    -   The file to read.
 * @return  -   The vector containing all players in the file.
*/
void playerFiles(vector<Player>& players, const string sourceFileName);

/**
 * Reads a file containing a deck of cards and returns a vector of pointers for the cards.
 * @param sourceFileName    -   The file to read.
 * @return  -   The vector containing pointers to the deck's cards.
*/
void cardFiles(vector<unique_ptr<Card>>& Cards, const string sourceFileName);