#include <memory>
#include <algorithm>
#include <vector>
using namespace std;

#include "Mtmchkin.h"
#include "utilities.h"

#include "Files.h"

#include "./Players/Player.h"
#include "./Cards/Card.h"

/**
 * return true if player1 should be before player2
*/
bool compare(const Player& player1, const Player& player2);


Mtmchkin::Mtmchkin(const string& deckPath, const string& playersPath) {

    /*===== TODO: Open and read cards file =====*/


    cardFiles(cards, deckPath);

    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/

    
    playerFiles(players, playersPath);
    
    alivePlayers = players.size();
    game_is_over = false;

    /*============================================*/


    this->m_turnIndex = 1;
}

void Mtmchkin::playTurn(Player& player) {

    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Draw a card from the deck
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the card
     * 4. Print the turn outcome with "printTurnOutcome"
    */
    int cardIndex = (m_turnIndex - 1) % cards.size();
    Card &currentCard = *cards.at(cardIndex);
    
    printTurnDetails(m_turnIndex, player, currentCard);
    
    string outcome = currentCard.playCard(player);
    printTurnOutcome(outcome);

    if (player.isKnockedOut()) alivePlayers--;
    if (player.getLevel() == MAX_LEVEL) game_is_over = true;

    m_turnIndex++;
}

void Mtmchkin::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/

    for (long unsigned int i = 0; i < players.size(); i++){
        if(players.at(i).isKnockedOut()) continue;
        playTurn(players.at(i));
    }
    
    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();
    
    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    vector<Player> sorted = players;
    sort(sorted.begin(), sorted.end(), compare);
    for (long unsigned int i = 0; i < sorted.size(); i++){
        printLeaderBoardEntry(i + 1, sorted.at(i));
    }


    /*=======================================================================================*/

    printBarrier();
}

bool Mtmchkin::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    return alivePlayers == 0 || game_is_over; 
    /*===================================================*/
}

void Mtmchkin::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
    
    for (long unsigned int i = 0; i < players.size(); i++){
        printStartPlayerEntry(i + 1, players.at(i));
    }
    
    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/
    
    sort(players.begin(), players.end(), compare);
    if (alivePlayers > 0) printWinner(players.front());
    else printNoWinners();

    /*========================================================================*/
}




bool compare(const Player& player1, const Player& player2){
    if (player1.getLevel() > player2.getLevel()) return true;
    if (player1.getLevel() < player2.getLevel()) return false;
    if (player1.getCoins() > player2.getCoins()) return true;
    if (player1.getCoins() < player2.getCoins()) return false;
    if (player1.getName().compare(player2.getName()) <= 0) return true;
    return false;
    
}