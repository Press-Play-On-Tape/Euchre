#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::incMode(bool ignoreCounter, bool increasePlayer) {

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

    if (ignoreCounter || this->counter == delay[static_cast<uint8_t>(this->gameState)]) {

        this->counter = 0;
        this->deal++;

        if (increasePlayer) {

            switch (this->gameState) {

                case GameState::Game_StartPlay ... GameState::Game_Follow_02:

                    Utils::print(Debug::State, "incMode() ..this->gameStatus.incCurrentPlayer()\n");                
                    this->gameStatus.incCurrentPlayer();
                    break;

                default: break;

            }

        }

        if (this->nextState != GameState::None) {
            
            Utils::print(Debug::State, " ..this->nextState != GameState::None\n");

            if (this->cookie->getNumberOfPlayers() == 2) {
                    
                switch (this->nextState) {

                    case GameState::Game_DealerExtraCard:

                        if (this->isHuman(this->gameStatus.getDealer())) {

                            Utils::print(Debug::State, "dealer is human\n");


                            // If the dealer is now not playing then skip this state ..

                            if (!this->isPlayingThisHand(this->gameStatus.getDealer())) {

                                this->nextState++;
                                Utils::print(Debug::State, "1 isHuman() %i %i %i\n", this->isHuman(this->gameStatus.getCurrentPlayer()) , this->gameStatus.getPlayerView() , this->gameStatus.getCurrentPlayer());

                                if (this->isHuman(this->gameStatus.getCurrentPlayer()) && this->gameStatus.getPlayerView() != this->gameStatus.getCurrentPlayer()) {

                                    Utils::print(Debug::State, "1 incMode() Transition from state %i", (uint16_t)this->gameState);
                                    Utils::print(Debug::State, "1 Swap\n");  

                                    this->savedState = this->nextState; 
                                    this->gameState = GameState::Swap_Init;
                                    this->nextState = GameState::None;
                                    this->gameStatus.flipPlayerView(this->cookie->getPlayer2Pos());
                                    this->getSwapCaption(this->savedState);

                                }
                                else {

                                    Utils::print(Debug::State, "2 incMode() Transition from state %i", (uint16_t)this->gameState);

                                    this->gameState = this->nextState;
                                    this->nextState = GameState::None;  

                                }

                            }
                            else {
                                
                                if  (this->gameStatus.getPlayerView() != this->gameStatus.getDealer()) {

                                    Utils::print(Debug::State, "3 incMode() Transition from state %i", (uint16_t)this->gameState);
                                    Utils::print(Debug::State, "3 Swap 1\n");  

                                    this->savedState = this->nextState; 
                                    this->gameState = GameState::Swap_Init;
                                    this->nextState = GameState::None;
                                    this->gameStatus.flipPlayerView(this->cookie->getPlayer2Pos());
                                    this->getSwapCaption(this->savedState);

                                }
                                else {

                                    Utils::print(Debug::State, "4 incMode() Transition from state %i", (uint16_t)this->gameState);

                                    this->gameState = this->nextState;
                                    this->nextState = GameState::None;  

                                    Utils::print(Debug::State, " to state %i\n", (uint16_t)this->gameState);

                                }

                            }

                        }
                        else {

                            // The dealer is not human so move to the state and the code will automatically select a card and continue ..                                                        

                            Utils::print(Debug::State, "4a incMode() Transition from state %i", (uint16_t)this->gameState);

                            this->gameState = this->nextState;
                            this->nextState = GameState::None;  

                            Utils::print(Debug::State, " to state %i\n", (uint16_t)this->gameState);

                        }

                        break;

                    default:

                        Utils::print(Debug::State, "5 isHuman() %i %i %i\n", this->isHuman(this->gameStatus.getCurrentPlayer()) , this->gameStatus.getPlayerView() , this->gameStatus.getCurrentPlayer());

                        if (this->isHuman(this->gameStatus.getCurrentPlayer()) && this->gameStatus.getPlayerView() != this->gameStatus.getCurrentPlayer()) {

                            Utils::print(Debug::State, "5 incMode() Transition from state %i", (uint16_t)this->gameState);
                            Utils::print(Debug::State, "5 Swap\n");  

                            this->savedState = this->nextState; 
                            this->gameState = GameState::Swap_Init;
                            this->nextState = GameState::None;
                            this->gameStatus.flipPlayerView(this->cookie->getPlayer2Pos());
                            this->getSwapCaption(this->savedState);

                        }
                        else {

                            Utils::print(Debug::State, "6 incMode() Transition from state %i", (uint16_t)this->gameState);

                            this->gameState = this->nextState;
                            this->nextState = GameState::None;  

                        }

                        break;

                }

            }
            else {

                Utils::print(Debug::State, "7 incMode() Transition from state %i", (uint16_t)this->gameState);

                this->gameState = this->nextState;
                this->nextState = GameState::None;

                Utils::print(Debug::State, "7 to state %i\n", (uint16_t)this->gameState);

            }

        }
        else {

            Utils::print(Debug::State, "8 ..this->nextState == GameState::None\n");
            Utils::print(Debug::State, " incMode() Transition from state %i", (uint16_t)this->gameState);

            this->gameState++;

            switch (this->gameState) {

                case GameState::Game_Follow_01 ... GameState::Game_Follow_02:

                    Utils::print(Debug::State, "9 test case GameState::Game_Follow_01 ... GameState::Game_Follow_02 ");

                    if (!this->isPlayingThisHand(this->gameStatus.getCurrentPlayer())) {

                        Utils::print(Debug::State, "9  player not playing so skip ");

                        this->gameState++;
                        this->gameStatus.incCurrentPlayer();

                    }
                    break;

                case GameState::Game_Follow_03:

                    Utils::print(Debug::State, "10 test case GameState::Game_Follow_03 ");

                    if (!this->isPlayingThisHand(this->gameStatus.getCurrentPlayer())) {

                        uint8_t winner = this->gameStatus.whoWon();
                        this->gameStatus.incTricks(winner);

                        Utils::print(Debug::State, "10  player not playing so skip ");
                        Utils::print(Debug::State, "Player %i wins.\n", winner);
                        
                        if (this->hands[0].getCardsInHand() > 0) {

                            Utils::print(Debug::State, "11 this->nextState = GameState::Game_EndOfTrick;\n");

                            this->gameState = GameState::Game_EndOfTrick;

                        }
                        else {

                            Utils::print(Debug::State, "12 this->nextState = GameState::Game_EndOfHand;\n");

                            this->gameState = GameState::Game_EndOfHand;
                            this->eog = 0;
                        }

                    }

                    break;


                default: break;

            }

            Utils::print(Debug::State, " to state %i\n", (uint16_t)this->gameState);


            // Should we swap hands?

            switch (this->gameState) {

                case GameState::Game_Bid_01 ... GameState::Game_Open_Bid_03:

                    if (this->cookie->getNumberOfPlayers() == 2) {

                        uint8_t offset = (static_cast<uint8_t>(this->gameState) - static_cast<uint8_t>(GameState::Game_Bid_00) + 1) % 4;

                        if (this->isHuman((this->gameStatus.getDealer() + offset) % 4) && this->gameStatus.getPlayerView() != (this->gameStatus.getDealer() + offset) % 4) {

                            Utils::print(Debug::State, "14 Swap currentPlayer \n", this->gameStatus.getCurrentPlayer());                    

                            this->savedState = this->gameState;
                            this->gameState = GameState::Swap_Init;
                            this->gameStatus.flipPlayerView(this->cookie->getPlayer2Pos());
                            this->getSwapCaption(this->savedState);

                        }

                    }

                    break;

                case GameState::Game_LeadCard ... GameState::Game_Follow_03:

                    Utils::print(Debug::State, "15 State %i \n", this->gameState);

                    if (this->cookie->getNumberOfPlayers() == 2) {

                        Utils::print(Debug::State, "15 currentPlayer %i, getPlayerView %i, Swap 3\n", this->gameStatus.getCurrentPlayer(), this->gameStatus.getPlayerView());                    

                        if (this->isHuman(this->gameStatus.getCurrentPlayer()) && this->gameStatus.getPlayerView() != this->gameStatus.getCurrentPlayer()) {

                            this->savedState = this->gameState;
                            this->gameState = GameState::Swap_Init;
                            this->gameStatus.flipPlayerView(this->cookie->getPlayer2Pos());
                            this->getSwapCaption(this->savedState);

                        }

                    }

                    break;

            }

        }

    }

}

void Game::getSwapCaption(GameState gameState) {

    this->swapCaption = SwapCaption::None;

    switch (gameState) {

        case GameState::Game_Bid_00      ... GameState::Game_Bid_03:
        case GameState::Game_Open_Bid_00 ... GameState::Game_Open_Bid_03:
            this->swapCaption = SwapCaption::YourBid;
            break;

        case GameState::Game_StartPlay ... GameState::Game_LeadCard:
            this->swapCaption = SwapCaption::LeadACard;
            break;

        case GameState::Game_Follow_01 ... GameState::Game_Follow_03:
            this->swapCaption = SwapCaption::FollowALead;
            break;

        case GameState::Game_DealerExtraCard:
            this->swapCaption = SwapCaption::DiscardACard;
            break;

        case GameState::Game_NewHand_Init:
            this->swapCaption = SwapCaption::Redeal;
            break;

    }

}

void Game::print() {

    #ifdef DEBUG
    Utils::print(Debug::None, "----------------------------------------------------------------------------\n");
    this->deck.print();

    for (uint8_t i = 0; i < 4; i++) {

        this->hands[i].print();

    }
    #endif

}

bool Game::handlePlayerBid(uint8_t playerIdx) {

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
                this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::Pass) + playerIdx)); 
                this->nextState = GameState::None;
                this->counter = 0;
                this->deal++;
                return true;

            case 1 ... 2:

                if (this->dialogCursor == 1) {
                    this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::TakeIt) + playerIdx)); 
                }
                else {
                    this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::TakeItAlone) + playerIdx)); 
                }

                this->hands[playerIdx].setCallStatus(CallStatus::FirstRound);
                this->nextState = GameState::Game_DealerExtraCard;
                this->gameStatus.setTrumps(this->dealerCard.getSuit(CardSuit::None));
                this->gameStatus.setPlayAlone(this->dialogCursor == 2);
                this->counter = 0;
                this->deal++;

                for (uint8_t i = 0; i < 4; i++) {

                    this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                }

                return true;

        }

    } 

    return false;

}

void Game::handlePlayerSecondBid(uint8_t playerIdx) {

    bool stickIt = this->cookie->getStickIt() && (this->gameState == GameState::Game_Open_Bid_03);

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
                    this->nextState = GameState::Game_NewHand_Init;
                    this->incMode(true, false);
                }
                else {
                    this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::Pass) + playerIdx)); 
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
                this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::TakeIt) + playerIdx)); 
                this->hands[playerIdx].setCallStatus(CallStatus::SecondRound);
                this->gameState = GameState::Game_StartPlay;
                this->counter = 0;
                this->gameStatus.setTrumps(static_cast<CardSuit>((this->dialogCursor - 1) / 2));
                this->gameStatus.setPlayAlone(false);

                for (uint8_t i = 0; i < 4; i++) {

                    this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                }

                break;

            case 2:
            case 4:
            case 6:
            case 8:
                this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::TakeItAlone) + playerIdx)); 
                this->hands[playerIdx].setCallStatus(CallStatus::SecondRound);
                this->gameState = GameState::Game_StartPlay;
                this->counter = 0;
                this->gameStatus.setTrumps(static_cast<CardSuit>((this->dialogCursor - 2) / 2));
                this->gameStatus.setPlayAlone(true);

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

        if (this->cookie->getHighlightPlayable()) {

            for (uint8_t i = this->bidCursor - 1; i >= 0; i++) {

                if (!(this->hands[playerIdx].getCard(i).getSuit(this->gameStatus.getTrumps()) != suitLed && this->hands[playerIdx].hasSuit(suitLed, this->gameStatus.getTrumps()))) {
                    this->bidCursor = i;
                    break;
                }

            }

        }
        else {
            this->bidCursor--;
        }

    } 

    if (PC::buttons.pressed(BTN_RIGHT) && this->bidCursor < this->hands[playerIdx].getCardsInHand() - 1) { 

        if (this->cookie->getHighlightPlayable()) {

            for (uint8_t i = this->bidCursor + 1; i < this->hands[playerIdx].getCardsInHand(); i++) {

                if (!(this->hands[playerIdx].getCard(i).getSuit(this->gameStatus.getTrumps()) != suitLed && this->hands[playerIdx].hasSuit(suitLed, this->gameStatus.getTrumps()))) {
                    this->bidCursor = i;
                    break;
                }

            }

        }
        else {

            this->bidCursor++;

        }

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


    Utils::print(Debug::Bid, "Hand %i, H: %i, D: %i, S: %i, C: %i\n", handNumber, hearts, diamonds, spades, clubs);

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

    if (highScore > this->upperThreshold && handNumber != 2) {

        this->gameStatus.setTrumps(highSuit);
        this->gameStatus.setPlayAlone(true);
        this->hands[handNumber].setCallStatus(CallStatus::SecondRound);

        return true;

    }
    else if (highScore > this->threshold) {

        this->gameStatus.setTrumps(highSuit);
        this->gameStatus.setPlayAlone(false);
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


bool Game::isPlayingThisHand(uint8_t playerIdx) {

    return (this->bidWinner() == ((playerIdx + 2) % 4) && !this->gameStatus.getPlayAlone()) || this->bidWinner() != ((playerIdx + 2) % 4);

}

bool Game::isHuman(uint8_t playerIdx) {

    if (this->cookie->getNumberOfPlayers() == 1) {

        return playerIdx == 0;

    }
    else {

        return (playerIdx == 0 || this->cookie->getPlayer2Pos() == playerIdx);

    }

}

void Game::firstValidCard(uint8_t playerIdx) {

    this->bidCursor = 255;

    if (this->cookie->getHighlightPlayable()) {

        CardSuit suitLed = this->gameStatus.getSuitLed();

        for (uint8_t i = 0; i < this->hands[playerIdx].getCardsInHand(); i++) {

            if (!(this->hands[playerIdx].getCard(i).getSuit(this->gameStatus.getTrumps()) != suitLed && this->hands[playerIdx].hasSuit(suitLed, this->gameStatus.getTrumps()))) {
                this->bidCursor = i;
                break;
            }

        }

    }

    if (this->bidCursor == 255) {
        this->bidCursor = 0;
    }

}