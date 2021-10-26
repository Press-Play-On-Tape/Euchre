#pragma once

#include "Pokitto.h"
#include "Card.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct GameStatus {

    private:

        HasSuit hasSuit[4][4];
        bool hasBeenPlayed[4][13];
        Card currentHand[4];
        CardSuit suitLed;
        CardSuit trumps = CardSuit::None;

        uint8_t firstPlayer;
        uint8_t currentPlayer;
        uint8_t lastPlayerIdx;
        uint8_t numberOfPlayers;
        uint8_t dealer;

        bool stickIt = false;
        bool showHands = true;
        bool showWinner = true;
        bool playAlone = false;

        uint8_t tricks[4] = { 0, 0, 0, 0 };
        uint8_t points0and2 = 0;
        uint8_t points1and3 = 0;
        uint8_t player2Pos = 1;

    public:

        uint8_t getFirstPlayer()                                                { return this->firstPlayer; }    
        uint8_t getCurrentPlayer()                                              { return this->currentPlayer; }    
        uint8_t getLastPlayerIdx()                                              { return this->lastPlayerIdx; }    

        uint8_t getTricks(uint8_t playerIdx)                                    { return this->tricks[playerIdx]; }    
        uint8_t getTricks0and2()                                                { return this->tricks[0] + this->tricks[2]; }    
        uint8_t getTricks1and3()                                                { return this->tricks[1] + this->tricks[3]; }    
        uint8_t getPoints0and2()                                                { return this->points0and2; }    
        uint8_t getPoints1and3()                                                { return this->points1and3; }    
        uint8_t getNumberOfPlayers()                                            { return this->numberOfPlayers; }    
        uint8_t getPlayer2Pos()                                                 { return this->player2Pos; }    
        uint8_t getDealer()                                                     { return this->dealer; }    

        bool getShowHands()                                                     { return this->showHands; }    
        bool getStickIt()                                                       { return this->stickIt; }    
        bool getShowWinner()                                                    { return this->showWinner; }    
        bool getPlayAlone()                                                     { return this->playAlone; }    

        CardSuit getSuitLed()                                                   { return this->suitLed; }    
        CardSuit getTrumps()                                                    { return this->trumps; }    

        HasSuit getHasSuit(uint8_t playerIdx, CardSuit suit)                    { return this->hasSuit[playerIdx][static_cast<uint8_t>(suit)]; }
        bool getHasBeenPlayed(CardSuit suit, uint8_t cardNumber)                { return this->hasBeenPlayed[static_cast<uint8_t>(suit)][cardNumber]; }
        bool getHasBeenPlayed(Card card)                                        { return this->hasBeenPlayed[static_cast<uint8_t>(card.getSuit(CardSuit::None))][card.getNumber()]; }
        Card getCurrentHand(uint8_t playerIdx)                                  { return this->currentHand[playerIdx]; }

        void setFirstPlayer(uint8_t val)                                        { this->firstPlayer = val; }
        void setCurrentPlayer(uint8_t val)                                      { this->currentPlayer = val; }
        
        void setTrumps(CardSuit val)                                            { this->trumps = val; }
        void setNumberOfPlayers(uint8_t val)                                    { this->numberOfPlayers = val; }
        void setPlayer2Pos(uint8_t val)                                         { this->player2Pos = val; }
        void setDealer(uint8_t val)                                             { this->dealer = val; }

        void setShowHands(bool val)                                             { this->showHands = val; }
        void setStickIt(bool val)                                               { this->stickIt = val; }
        void setShowWinner(bool val)                                            { this->showWinner = val; }
        void setPlayAlone(bool val)                                             { this->playAlone = val; }

        void setHasSuit(uint8_t playerIdx, CardSuit suit, HasSuit val)          { this->hasSuit[playerIdx][static_cast<uint8_t>(suit)] = val; }
        void setHasBeenPlayed(CardSuit suit, uint8_t cardIndex, bool val)       { this->hasBeenPlayed[static_cast<uint8_t>(suit)][cardIndex] = val; }
        void setCurrentHand(uint8_t playerIdx, Card val)                        { this->currentHand[playerIdx] = val; }

    public:

        void init() {

            for (uint8_t i = 0; i < 4; i++) {

                for (uint8_t j = 0; j < 4; j++) {

                    this->hasSuit[i][j] = HasSuit::Unknown;

                }

                for (uint8_t j = 0; j < 13; j++) {

                    this->hasBeenPlayed[i][j] = false;

                }

                this->currentHand[i].init(Cards::NoCard);
                this->tricks[i] = 0;
                this->playAlone = false;

            }

        }

        void initHand(uint8_t currentPlayer) {

            this->suitLed = CardSuit::None;
            this->currentPlayer = currentPlayer;

            for (uint8_t i = 0; i < 4; i++) {

                this->currentHand[i].init(Cards::NoCard);

            }

            this->lastPlayerIdx = (currentPlayer + 3) % 4;

        }

        void incTricks(uint8_t playerIdx) {

            this->tricks[playerIdx]++;

        }

        void incHands(uint8_t playerIdx, uint8_t points) {

            if (playerIdx == 0 || playerIdx == 2)   this->points0and2 = this->points0and2 + points;
            if (playerIdx == 1 || playerIdx == 3)   this->points1and3 = this->points1and3 + points;

        }

        void incCurrentPlayer() {

            this->currentPlayer = (this->currentPlayer + 1) % 4;

        }


        void playCard(Card &card) {
// printf("PlayCard A\n");
            this->setHasSuit(this->getCurrentPlayer(), card.getSuit(this->getTrumps()), card.getSuit(this->getTrumps()) != trumps ? HasSuit::False : HasSuit::True);
// printf("PlayCard B\n");
            this->setHasBeenPlayed(card.getSuit(this->getTrumps()), card.getNumber(), true);
// printf("PlayCard C\n");
            this->setCurrentHand(this->getCurrentPlayer(), card);

// printf("PlayCard D.  SuitLed %i ", (uint16_t)suitLed);
            if (this->suitLed == CardSuit::None) this->suitLed = card.getSuit(this->getTrumps());
// printf(" updated to %i.", (uint16_t)suitLed);            
// printf("PlayCard E\n");

        }

        bool isPartnerWinning(uint8_t playerIdx, CardSuit suitLed) {

            if (this->currentHand[playerIdx].getNumber() == Cards::NoCard) return false;

            uint8_t partnerCardValue = 0;

            if (this->currentHand[playerIdx].isTrump(trumps)) {

                partnerCardValue = this->currentHand[playerIdx].getCardValue(trumps);

            }
            else if (this->currentHand[playerIdx].getSuit(this->getTrumps()) == suitLed) {

                partnerCardValue = this->currentHand[playerIdx].getNumber();

            }

            if (partnerCardValue == 0) return false;


            // Other hands ..

            for (uint8_t i = playerIdx + 1; i < playerIdx + 4; i++) {

                uint8_t otherCardValue = 0;

                if (this->currentHand[i].getNumber() != Cards::NoCard) {

                    if (this->currentHand[i].isTrump(trumps)) {

                        otherCardValue = this->currentHand[i].getCardValue(trumps);

                    }
                    else if (this->currentHand[i].getSuit(this->getTrumps()) == suitLed) {

                        otherCardValue = this->currentHand[i].getNumber();

                    }

                }

                if (otherCardValue > partnerCardValue) return false;

            }

            return true;

        }


        uint8_t whoWon() {

            uint8_t highestScore = 0;
            uint8_t highestScoreIdx = 0;

            for (uint8_t i = 0; i < 4; i++) {

                uint8_t test = this->currentHand[i].isTrump(this->getTrumps()) 
                               ? this->currentHand[i].getCardValue(this->getTrumps()) 
                               : (this->currentHand[i].getSuit(this->getTrumps()) == this->suitLed ? this->currentHand[i].getNumber() : 0);

                if (highestScore < test) {
                    highestScore = test;
                    highestScoreIdx = i;
                }

            }

            return highestScoreIdx;

        }


        uint8_t isPlayerWinning(uint8_t playerIdx, uint8_t ignorePlayerIdx = Constants::NoPlayer) {

            uint8_t highestScore = 0;
            uint8_t highestScoreIdx = Constants::NoPlayer;
            uint8_t test = 0;
// printf("isPlayerWinning ");  

            for (uint8_t i = 0; i < 4; i++) {

                if (i != ignorePlayerIdx && this->currentHand[i].getCardIndex() != Cards::NoCard) {
// printf("%i %i ", i, test);
                    uint8_t test = this->currentHand[i].isTrump(this->getTrumps()) 
                                   ? this->currentHand[i].getCardValue(this->getTrumps()) 
                                   : (this->currentHand[i].getSuit(this->getTrumps()) == this->suitLed ? this->currentHand[i].getNumber() : 0);

                    if (highestScore < test) {
                        highestScore = test;
                        highestScoreIdx = i;
                    }

                }

            }
            
// printf(" >> playerIdx %i == highestScoreIdx %i\n", playerIdx , highestScoreIdx );
            return playerIdx == highestScoreIdx;

        }

        uint8_t getHighestTrumpInHand() {

            uint8_t highestScore = 0;

            for (uint8_t i = 0; i < 4; i++) {

                if (this->currentHand[i].getCardIndex() != Cards::NoCard && this->currentHand[i].isTrump(this->getTrumps()) && 
                    this->currentHand[1].getCardValue(this->getTrumps()) > highestScore) {                
                    highestScore = this->currentHand[i].getCardValue(this->getTrumps());
                }

            }

            return highestScore == 0 ? Cards::NoCard : highestScore;

        }

        uint8_t getHighestOfSuitInHand(CardSuit suit) {

            uint8_t highestScore = 0;

            for (uint8_t i = 0; i < 4; i++) {

                if (this->currentHand[i].getCardIndex() != Cards::NoCard && this->currentHand[i].getSuit(this->getTrumps()) == suit && 
                    this->currentHand[i].getCardValue(this->getTrumps()) > highestScore) {                
                    highestScore = this->currentHand[i].getCardValue(this->getTrumps());
                }

            }

            return highestScore == 0 ? Cards::NoCard : highestScore;

        }

};

