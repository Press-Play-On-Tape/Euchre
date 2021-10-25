#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::incMode() {

    uint8_t delay[] = { 0, 0, 0, 0, 0, 0, 
                        2, 5, 2, 5, 2, 5, 2, 5,                     // NewHand_00 ... NewHand_07
                        2, 2, 5, 2, 2, 5, 2, 2, 5, 2, 2, 5,         // NewHand_08 ... NewHand_19
                        5,                                          // DealerCard 
                        Constants::BidDialogueDelay, Constants::BidDialogueDelay, Constants::BidDialogueDelay, Constants::BidDialogueDelay,  // Bid_00 ... Bid_03
                        Constants::BidDialogueDelay, Constants::BidDialogueDelay, Constants::BidDialogueDelay, Constants::BidDialogueDelay,  // Open_Bid_00 ... Open_Bid_03
                        1,                                          // DealerExtraCard
                        0,                                          // StartPlay
                        10,                                         // Lead Card
                        10, 10, 10,                                 // Follow_01 - Follow_03
                        5,
                        };

    this->counter++;
//printf(" incMode(0) %i == %i\n", this->counter, delay[static_cast<uint8_t>(this->gameState)]);
    if (this->counter == delay[static_cast<uint8_t>(this->gameState)]) {

        if (this->nextState != GameState::None) {

printf(" incMode(1) Transition from state %i", (uint16_t)this->gameState);
            this->gameState = this->nextState;
            this->nextState = GameState::None;
printf(" to state %i\n", (uint16_t)this->gameState);
        }
        else {

printf(" incMode(2) Transition from state %i", (uint16_t)this->gameState);
            this->gameState++;
printf(" to state %i\n", (uint16_t)this->gameState);

        }

        this->counter = 0;
        this->deal++;
        this->gameStatus.incCurrentPlayer();

    }

}

void Game::print() {

    printf("----------------------------------------------------------------------------\n");
    this->deck.print();

    for (uint8_t i = 0; i < 4; i++) {

        this->hands[i].print();

    }

}

void Game::handlePlayerBid(uint8_t playerIdx) {

    if (PC::buttons.pressed(BTN_LEFT) && this->dialogCursor > 0) { 

        this->dialogCursor--;

    } 

    if (PC::buttons.pressed(BTN_RIGHT) && this->dialogCursor < 2) { 

        this->dialogCursor++;

    } 

    if (PC::buttons.pressed(BTN_A)) { 

        switch (this->dialogCursor) {

            case 0:
                this->hands[playerIdx].setCallStatus(CallStatus::Pass);
                this->gameState++;
                this->counter = 0;
                this->deal++;
                break;

            case 1 ... 2:
                this->hands[playerIdx].setCallStatus(CallStatus::FirstRound);
                this->gameState = GameState::Game_DealerExtraCard;
                this->gameStatus.setTrumps(this->dealerCard.getSuit(CardSuit::None));
                this->counter = 0;
                this->deal++;
                this->playAlone = (this->dialogCursor == 2);

                for (uint8_t i = 0; i < 4; i++) {

                    this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                }

                break;


        }

    } 

}

void Game::handlePlayerSecondBid(uint8_t playerIdx) {

    bool stickIt = this->gameStatus.getStickIt() && (this->gameState == GameState::Game_Open_Bid_03);

    if (this->dialogCursor == 0 && stickIt) this->dialogCursor = 1;

    if (PC::buttons.pressed(BTN_LEFT) && this->dialogCursor > (stickIt ? 1 : 0)) { 

        this->dialogCursor--;

    } 

    if (PC::buttons.pressed(BTN_RIGHT) && this->dialogCursor < 8) { 

        this->dialogCursor++;

    } 

    if (PC::buttons.pressed(BTN_UP) && this->dialogCursor > 2) { 

        this->dialogCursor = this->dialogCursor - 2;

    } 

    if (PC::buttons.pressed(BTN_DOWN) && this->dialogCursor > 0 && this->dialogCursor < 7) { 

        this->dialogCursor = this->dialogCursor + 2;

    } 

    if (PC::buttons.pressed(BTN_A)) { 

        switch (this->dialogCursor) {

            case 0:
                if (this->gameState == GameState::Game_Open_Bid_03) {

                    this->gameState = GameState::Game_NewHand_Init;

                }
                else {
                    this->hands[playerIdx].setCallStatus(CallStatus::Pass);
                    this->gameState++;
                    this->counter = 0;
                    this->deal++;
                }
                break;

            case 1:
            case 3:
            case 5:
            case 7:
                this->hands[playerIdx].setCallStatus(CallStatus::SecondRound);
                this->gameState = GameState::Game_StartPlay;
                this->counter = 0;
                this->gameStatus.setTrumps(static_cast<CardSuit>((this->dialogCursor - 1) / 2));
                this->playAlone = false;

                for (uint8_t i = 0; i < 4; i++) {

                    this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                }

                break;

            case 2:
            case 4:
            case 6:
            case 8:
                this->hands[playerIdx].setCallStatus(CallStatus::SecondRound);
                this->gameState = GameState::Game_StartPlay;
                this->counter = 0;
                this->gameStatus.setTrumps(static_cast<CardSuit>((this->dialogCursor - 2) / 2));
                this->playAlone = true;

                for (uint8_t i = 0; i < 4; i++) {

                    this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                }

                break;

        }

    } 

}

uint8_t Game::handleDiscardACard(uint8_t playerIdx) {

    if (PC::buttons.pressed(BTN_LEFT) && this->bidCursor > 0) { 

        this->bidCursor--;

    } 

    if (PC::buttons.pressed(BTN_RIGHT) && this->bidCursor < this->hands[playerIdx].getCardsInHand() - 1) { 

        this->bidCursor++;

    } 

    if (PC::buttons.pressed(BTN_A)) { 

        return this->bidCursor;

    } 

    return Cards::NoCard;

}

uint8_t Game::handlePlayACard(uint8_t playerIdx, CardSuit suitLed) {

    if (PC::buttons.pressed(BTN_LEFT) && this->bidCursor > 0) { 

        this->bidCursor--;

    } 

    if (PC::buttons.pressed(BTN_RIGHT) && this->bidCursor < this->hands[playerIdx].getCardsInHand() - 1) { 

        this->bidCursor++;

    } 

    if (PC::buttons.pressed(BTN_A)) { 

        if (suitLed != CardSuit::None) {

            if (this->hands[playerIdx].getCard(this->bidCursor).getSuit(this->gameStatus.getTrumps()) != suitLed && this->hands[playerIdx].hasSuit(suitLed, this->gameStatus.getTrumps())) {
                return Cards::NoCard;
            }

            return this->bidCursor;

        }
        else {

            return this->bidCursor;

        }

    } 

    return Cards::NoCard;

}


bool Game::doSecondBid(uint8_t handNumber) {

    uint16_t hearts =    this->hands[handNumber].bid(CardSuit::Hearts);
    uint16_t diamonds =  this->hands[handNumber].bid(CardSuit::Diamonds);
    uint16_t clubs =     this->hands[handNumber].bid(CardSuit::Clubs);
    uint16_t spades =    this->hands[handNumber].bid(CardSuit::Spades);

    printf("Hand %i, H: %i, D: %i, S: %i, C%i\n", handNumber, hearts, diamonds, spades, clubs);

    CardSuit highSuit = CardSuit::Hearts;
    uint16_t highScore = hearts;

    if (highScore < diamonds) {
        highSuit = CardSuit::Diamonds;
        highScore = diamonds;
    }

    if (highScore < clubs) {
        highSuit = CardSuit::Clubs;
        highScore = clubs;
    }
    if (highScore < spades) {
        highSuit = CardSuit::Spades;
        highScore = spades;
    }

    if (highScore > this->threshold) {

        this->gameStatus.setTrumps(highSuit);
        this->hands[handNumber].setCallStatus(CallStatus::SecondRound);

        return true;

    }
    else {

        this->hands[handNumber].setCallStatus(CallStatus::Pass);
        return false;

    }

}

uint8_t Game::bidWinner() {

    if (this->hands[0].isBidWinner()) return 0;
    if (this->hands[1].isBidWinner()) return 1;
    if (this->hands[2].isBidWinner()) return 2;
    if (this->hands[3].isBidWinner()) return 3;

    return 0;
    
}