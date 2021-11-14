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
        Card lastHand[4];
        CardSuit suitLed = CardSuit::None;
        CardSuit trumps = CardSuit::None;

        uint8_t firstPlayer;
        uint8_t currentPlayer;
        uint8_t lastPlayerIdx;
        uint8_t dealer;

        uint8_t tricks[4] = { 0, 0, 0, 0 };
        uint8_t points0and2 = 0;
        uint8_t points1and3 = 0;
        uint8_t playerView = 0;
        bool playAlone = false;

    public:

        uint8_t getFirstPlayer()                                                { return this->firstPlayer; }    
        uint8_t getCurrentPlayer()                                              { return this->currentPlayer; }    
        uint8_t getLastPlayerIdx()                                              { return this->lastPlayerIdx; }    

        uint8_t getTricks(uint8_t playerIdx)                                    { return this->tricks[playerIdx]; }    
        uint8_t getTricks0and2()                                                { return this->tricks[0] + this->tricks[2]; }    
        uint8_t getTricks1and3()                                                { return this->tricks[1] + this->tricks[3]; }    
        uint8_t getPoints0and2()                                                { return this->points0and2; }    
        uint8_t getPoints1and3()                                                { return this->points1and3; }    
        uint8_t getDealer()                                                     { return this->dealer; }   
        uint8_t getPlayerView()                                                 { return this->playerView; } 
        bool getPlayAlone()                                                     { return this->playAlone; }    

        CardSuit getSuitLed()                                                   { return this->suitLed; }    
        CardSuit getTrumps()                                                    { return this->trumps; }    

        HasSuit getHasSuit(uint8_t playerIdx, CardSuit suit)                    { return this->hasSuit[playerIdx][static_cast<uint8_t>(suit)]; }
        bool getHasBeenPlayed(CardSuit suit, uint8_t cardNumber)                { return this->hasBeenPlayed[static_cast<uint8_t>(suit)][cardNumber]; }
        bool getHasBeenPlayed(Card card)                                        { return this->hasBeenPlayed[static_cast<uint8_t>(card.getSuit(CardSuit::None))][card.getNumber()]; }
        Card getCurrentHand(uint8_t playerIdx)                                  { return this->currentHand[playerIdx]; }
        Card getLastHand(uint8_t playerIdx)                                     { return this->lastHand[playerIdx]; }

        void setFirstPlayer(uint8_t val)                                        { this->firstPlayer = val; }
        void setCurrentPlayer(uint8_t val)                                      { this->currentPlayer = val; }
        
        void setTrumps(CardSuit val)                                            { this->trumps = val; }
        void setPlayerView(uint8_t val)                                         { this->playerView = val; }
        void setDealer(uint8_t val)                                             { this->dealer = val; }

        void setHasSuit(uint8_t playerIdx, CardSuit suit, HasSuit val)          { this->hasSuit[playerIdx][static_cast<uint8_t>(suit)] = val; }
        void setHasBeenPlayed(CardSuit suit, uint8_t cardIndex, bool val)       { this->hasBeenPlayed[static_cast<uint8_t>(suit)][cardIndex] = val; }
        void setCurrentHand(uint8_t playerIdx, Card val)                        { this->currentHand[playerIdx] = val; }
        void setPlayAlone(bool val)                                             { this->playAlone = val; }

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
                this->lastHand[i].init(Cards::NoCard);
                this->tricks[i] = 0;
            	this->playAlone = false;

            }

        }

        void initHand(uint8_t currentPlayer) {

            this->suitLed = CardSuit::None;
            this->currentPlayer = currentPlayer;

            for (uint8_t i = 0; i < 4; i++) {

                this->lastHand[i].init(this->currentHand[i].getCardIndex());
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

        void incDealer() {

            this->dealer = (this->dealer + 1) % 4;

        }

        void playCard(Card &card) {

            this->setHasSuit(this->getCurrentPlayer(), card.getSuit(this->getTrumps()), card.getSuit(this->getTrumps()) != trumps ? HasSuit::False : HasSuit::True);
            this->setHasBeenPlayed(card.getSuit(this->getTrumps()), card.getNumber(), true);
            this->setCurrentHand(this->getCurrentPlayer(), card);

            if (this->suitLed == CardSuit::None) this->suitLed = card.getSuit(this->getTrumps());

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

            for (uint8_t i = 0; i < 4; i++) {

                if (i != ignorePlayerIdx && this->currentHand[i].getCardIndex() != Cards::NoCard) {

                    uint8_t test = this->currentHand[i].isTrump(this->getTrumps()) 
                                   ? this->currentHand[i].getCardValue(this->getTrumps()) 
                                   : (this->currentHand[i].getSuit(this->getTrumps()) == this->suitLed ? this->currentHand[i].getNumber() : 0);

                    if (highestScore < test) {
                        highestScore = test;
                        highestScoreIdx = i;
                    }

                }

            }
            
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

        void flipPlayerView(uint8_t player2Pos) {

            this->playerView = this->playerView == 0 ? player2Pos : 0;
            
        }


};

