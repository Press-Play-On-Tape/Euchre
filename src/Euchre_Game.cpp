#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game_Init() {

    this->gameState = GameState::Game_NewHand_Init;
    this->nextState = GameState::None;
    this->gameStatus.init();
    this->gameStatus.setDealer(3);

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game() {


    Utils::print(Debug::None, "GameState: %i, deal: %i, dealer(): % i, currentPlayer: %i, getPlayerView(): %i, counter: %i\n", (uint16_t)this->gameState, this->deal, this->gameStatus.getDealer(), this->gameStatus.getCurrentPlayer(), this->gameStatus.getPlayerView(),this->counter);


    // Handle player actions ..

    if (PC::buttons.released(BTN_C)) {

        this->savedState = this->gameState;
        this->gameState = GameState::Pause_Init;

    }



    // Handle state machine ..

    switch (this->gameState) {

        case GameState::Game_NewHand_Init:

            Utils::print(Debug::Play, "Game_NewHand_Init -------------------\n");

            this->deck.init();

            for (uint8_t i = 0; i < 4; i++) {
                this->hands[i].init(i);
            }

            this->counter = 0;
            this->deal = 0;
            this->dealerCard.init(Cards::NoCard);
            this->gameStatus.initHand((this->gameStatus.getDealer() + 1) % 4);

            this->print();

            this->upperThreshold = 180;
            this->threshold = 150;
            this->bidCursor = 0;
            this->dialogCursor = 0;
            this->gameState = GameState::Game_NewHand_00;
            this->gameStatus.init();
            [[fallthrough]]

        case GameState::Game_NewHand_00 ... GameState::Game_NewHand_07:

            if (counter == 0) {

                Card card = this->deck.dealCard();
                this->hands[this->deal / 2].addCard(card);
                this->hands[this->deal / 2].shuffleHand();

            }
            
            this->incMode();
            break;

        case GameState::Game_NewHand_08 ... GameState::Game_NewHand_19:

            if (counter == 0) {

                Card card = this->deck.dealCard();
                this->hands[(this->deal - 8) / 3].addCard(card);
                this->hands[(this->deal - 8) / 3].shuffleHand();

            }

            this->incMode();
            break;

        case GameState::Game_DealerCard:

            if (counter == 0) {

                this->dealerCard = this->deck.dealCard();


// Player 1 does it alone

// this->dealerCard.init(CardSuit::Hearts, Cards::Nine);

// this->hands[0].getCard(0).init(CardSuit::Spades, Cards::Jack);
// this->hands[0].getCard(1).init(CardSuit::Diamonds, Cards::Ten);
// this->hands[0].getCard(2).init(CardSuit::Diamonds, Cards::King);
// this->hands[0].getCard(3).init(CardSuit::Spades, Cards::Nine);
// this->hands[0].getCard(4).init(CardSuit::Spades, Cards::King);

// this->hands[1].getCard(0).init(CardSuit::Diamonds, Cards::Jack);
// this->hands[1].getCard(1).init(CardSuit::Hearts, Cards::King);
// this->hands[1].getCard(2).init(CardSuit::Hearts, Cards::Jack);
// this->hands[1].getCard(3).init(CardSuit::Hearts, Cards::Queen);
// this->hands[1].getCard(4).init(CardSuit::Hearts, Cards::Ace);

// this->hands[2].getCard(0).init(CardSuit::Spades, Cards::Ten);
// this->hands[2].getCard(2).init(CardSuit::Spades, Cards::Ace);
// this->hands[2].getCard(1).init(CardSuit::Clubs, Cards::Ace);
// this->hands[2].getCard(3).init(CardSuit::Diamonds, Cards::Jack);
// this->hands[2].getCard(4).init(CardSuit::Diamonds, Cards::Ace);

// this->hands[3].getCard(0).init(CardSuit::Spades, Cards::Queen);
// this->hands[3].getCard(1).init(CardSuit::Diamonds, Cards::Nine);
// this->hands[3].getCard(2).init(CardSuit::Diamonds, Cards::Queen);
// this->hands[3].getCard(3).init(CardSuit::Clubs, Cards::Queen);
// this->hands[3].getCard(4).init(CardSuit::Clubs, Cards::King);

// this->print();

            }

            this->incMode();
            this->bidCursor = 0;
            break;

        case GameState::Game_Bid_00:
        case GameState::Game_Bid_01:
        case GameState::Game_Bid_02:
        case GameState::Game_Bid_03:
            {
                uint8_t offset = (static_cast<uint8_t>(this->gameState) - static_cast<uint8_t>(GameState::Game_Bid_00) + 1) % 4;

                if (this->isHuman((this->gameStatus.getDealer() + offset) % 4)) {

                    if (this->counter == 0 && this->handlePlayerBid((this->gameStatus.getDealer() + offset) % 4)) {

                        this->counter = 1;

                    }
                    else if (this->counter > 0) {

                        this->incMode();

                    }

                }
                else {

                    if (counter == 0) {

                        if ((this->gameStatus.getDealer() + offset) % 4 != 2 && this->hands[(this->gameStatus.getDealer() + offset) % 4].bid(this->dealerCard.getSuit(CardSuit::None), this->dealerCard, false) > this->upperThreshold) {

                            this->hands[(this->gameStatus.getDealer() + offset) % 4].setCallStatus(CallStatus::FirstRound);
                            this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::TakeItAlone) + ((this->gameStatus.getDealer() + offset) % 4)) ); 
                            this->gameStatus.setTrumps(dealerCard.getSuit(CardSuit::None));
                            this->gameStatus.setPlayAlone(true);
                            this->nextState = GameState::Game_DealerExtraCard;

                            for (uint8_t i = 0; i < 4; i++) {

                                this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                            }

                        }
                        else if (this->hands[(this->gameStatus.getDealer() + offset) % 4].bid(this->dealerCard.getSuit(CardSuit::None), this->dealerCard, false) > this->threshold) {

                            this->hands[(this->gameStatus.getDealer() + offset) % 4].setCallStatus(CallStatus::FirstRound);
                            this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::TakeIt) + ((this->gameStatus.getDealer() + offset) % 4)) ); 
                            this->gameStatus.setTrumps(dealerCard.getSuit(CardSuit::None));
                            this->gameStatus.setPlayAlone(false);
                            this->nextState = GameState::Game_DealerExtraCard;

                            for (uint8_t i = 0; i < 4; i++) {

                                this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                            }

                        }
                        else {

                            this->hands[(this->gameStatus.getDealer() + offset) % 4].setCallStatus(CallStatus::Pass);
                            this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::Pass) + ((this->gameStatus.getDealer() + offset) % 4)) ); 

                        }

                    }

                    this->incMode();

                }

            }

            break;

        case GameState::Game_Open_Bid_00:
        case GameState::Game_Open_Bid_01:
        case GameState::Game_Open_Bid_02:
        case GameState::Game_Open_Bid_03:
            {
                uint8_t offset = (static_cast<uint8_t>(this->gameState) - static_cast<uint8_t>(GameState::Game_Open_Bid_00) + 1) % 4;

                if (this->isHuman((this->gameStatus.getDealer() + offset) % 4)) {

                    this->handlePlayerSecondBid((this->gameStatus.getDealer() + offset) % 4);

                }
                else {

                    if (counter == 0) {

                        Utils::print(Debug::Bid, "Round Two of Bidding --------------------------------------------------------\n");                    

                        if (this->doSecondBid((this->gameStatus.getDealer() + offset) % 4)) {

                            for (uint8_t i = 0; i < 4; i++) {

                                this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                            }
                                                            
                            this->nextState = GameState::Game_StartPlay;


                        }
                        else {
                            
                            if (this->gameState == GameState::Game_Open_Bid_03) {
                                                                
                                this->nextState = GameState::Game_NewHand_Init;

                            }
                            else {
                                
                                this->nextState = GameState::None;

                            }

                        }

                    }

                    this->incMode();

                }

            }

            break;

        case GameState::Game_DealerExtraCard:

            // If the dealer is a human then we need to allow them to pickup / discard a card ..

            if (this->isHuman(this->gameStatus.getDealer())) {

                if (this->hands[this->gameStatus.getDealer()].getCardsInHand() == 5) {

                    this->hands[this->gameStatus.getDealer()].addCard(this->dealerCard);
                    this->dealerCard.init(Cards::NoCard);
                    this->hands[this->gameStatus.getDealer()].shuffleHandTrumps(this->gameStatus.getTrumps());

                }

                uint8_t card = this->handleDiscardACard(this->gameStatus.getDealer() % 4);

                if (card != Cards::NoCard) {;

                    this->hands[this->gameStatus.getDealer() % 4].removeCard(this->dialogCursor);
                    this->firstValidCard(this->gameStatus.getCurrentPlayer());
                    this->gameState = GameState::Game_StartPlay;

                }

            }
            else {


                // Non-human dealers quietly pickup and discard the dealt dard ..

                if (counter == 0) {

                    this->hands[this->gameStatus.getDealer()].selectBestFive(this->gameStatus.getTrumps(), this->dealerCard);

                }

                this->nextState = GameState::None;
                this->incMode();

            }

            break;


        case GameState::Game_StartPlay:

            this->gameState++;
            // this->gameStatus.initHand((this->gameStatus.getDealer() + 1) % 4);
            this->dialogCursor = 0;
            this->dealerCard.init(Cards::NoCard);
            this->counter = 0;


            // If the player clockwise of the dealer is not playing then skip to the next player ..

            if (!this->isPlayingThisHand(this->gameStatus.getCurrentPlayer())) {

                this->nextState = GameState::None;
                this->incMode(true, false);

            }


            // If two players and the other player is the dealer then swap to their view to allow them to discard a card ..

            else if (this->isHuman(this->gameStatus.getCurrentPlayer()) && this->gameStatus.getPlayerView() != this->gameStatus.getCurrentPlayer()) {

                this->savedState = this->gameState; 
                this->gameState = GameState::Swap_Init;
                this->nextState = GameState::None;
                this->gameStatus.flipPlayerView(this->cookie->getPlayer2Pos());
                this->getSwapCaption(this->savedState);
                break;

            }

            [[fallthrough]]       

        case GameState::Game_LeadCard:

            #ifdef DEBUG_PLAY
            
                // Render out the cards before play ..

                Utils::print(Debug::Play, "Start of Play --------------------------------------------------------\n");
                this->hands[0].print();
                this->hands[1].print();
                this->hands[2].print();
                this->hands[3].print();
                Utils::print(Debug::Play, "Current player %i\n", this->gameStatus.getCurrentPlayer());
                Utils::print(Debug::Play, "----------------------------------------------------------------------\n");

            #endif


            // If the current player is a human then handle their card choice ..

            if (this->isHuman(this->gameStatus.getCurrentPlayer())) {

                uint8_t selectedCard = this->handlePlayACard(this->gameStatus.getCurrentPlayer(), CardSuit::None);

                if (selectedCard != Cards::NoCard) {

                    Card card = this->hands[this->gameStatus.getCurrentPlayer()].getCard(selectedCard);
                    this->hands[this->gameStatus.getCurrentPlayer()].removeCard(selectedCard);
                    this->firstValidCard(this->gameStatus.getCurrentPlayer());
                    this->gameStatus.playCard(card);

                    Utils::print(Debug::Play, "Player %i leads a ", this->gameStatus.getCurrentPlayer());
                    card.print();
                    Utils::print(Debug::Play, ".\n");

                    this->gameStatus.setFirstPlayer(this->gameStatus.getCurrentPlayer());
                    this->incMode(true);

                }

            }   
            else {

                if (this->counter == 0) {

                    uint8_t i = this->hands[this->gameStatus.getCurrentPlayer()].leadACard(this->gameStatus.getTrumps(), this->gameStatus, this->hands[this->gameStatus.getCurrentPlayer()].isBidWinner(), this->hands[(this->gameStatus.getCurrentPlayer() + 2) % 4].isBidWinner(), this->hands[this->gameStatus.getCurrentPlayer()].isBidWinner() && this->gameStatus.getPlayAlone());
                    Card card = this->hands[this->gameStatus.getCurrentPlayer()].getCard(i);

                    this->hands[this->gameStatus.getCurrentPlayer()].removeCard(i);
                    this->gameStatus.setFirstPlayer(this->gameStatus.getCurrentPlayer());
                    this->firstValidCard(this->gameStatus.getCurrentPlayer());
                    this->gameStatus.playCard(card);

                    Utils::print(Debug::Play, "Player %i leads a ", this->gameStatus.getCurrentPlayer());
                    card.print();
                    Utils::print(Debug::Play, ".\n");

                }

                this->incMode();

            }         

            break;

        case GameState::Game_Follow_01:
        case GameState::Game_Follow_02:
        case GameState::Game_Follow_03:

            // If the current player is a human then handle their card choice ..
            
            if (this->isHuman(this->gameStatus.getCurrentPlayer())) {

                switch (this->counter) {

                    case 0:
                        {                        
                            uint8_t selectedCard = this->handlePlayACard(this->gameStatus.getCurrentPlayer(), this->gameStatus.getSuitLed());

                            if (selectedCard != Cards::NoCard) {

                                Card card = this->hands[this->gameStatus.getCurrentPlayer()].getCard(selectedCard);
                                this->hands[this->gameStatus.getCurrentPlayer()].removeCard(selectedCard);
                                this->gameStatus.playCard(card);
                                this->firstValidCard(this->gameStatus.getCurrentPlayer());

                                Utils::print(Debug::Play, "Player %i follows with a ", this->gameStatus.getCurrentPlayer());
                                card.print();
                                Utils::print(Debug::Play, ".\n");

                                if (this->gameState == GameState::Game_Follow_03) {

                                    uint8_t winner = this->gameStatus.whoWon();
                                    this->gameStatus.incTricks(winner);

                                    Utils::print(Debug::Play, "Player %i wins.\n", winner);
                                    
                                    if (this->hands[0].getCardsInHand() > 0) {
                                        this->nextState = GameState::Game_EndOfTrick;
                                    }
                                    else {
                                        this->nextState = GameState::Game_EndOfHand;
                                        this->eog = 0;
                                    }

                                }
                                else {

                                    this->nextState = GameState::None;

                                }

                                this->counter = 1;

                            }

                        }
                        break;

                    default:
                        this->incMode();
                        break;


                }

            }   
            else {

                if (this->counter == 0) {
                        
                    uint8_t i = this->hands[this->gameStatus.getCurrentPlayer()].followACard(this->gameStatus);
                    Card card = this->hands[this->gameStatus.getCurrentPlayer()].getCard(i);
                    this->hands[this->gameStatus.getCurrentPlayer()].removeCard(i);
                    this->firstValidCard(this->gameStatus.getCurrentPlayer());
                    this->gameStatus.playCard(card);

                    Utils::print(Debug::Play, "Player %i follows with a ", this->gameStatus.getCurrentPlayer());
                    card.print();
                    Utils::print(Debug::Play, ".\n");


                    if (this->gameState == GameState::Game_Follow_03) {

                        uint8_t winner = this->gameStatus.whoWon();
                        this->gameStatus.incTricks(winner);
                                    
                        Utils::print(Debug::Play, "Player %i wins.\n", winner);

                        if (this->hands[0].getCardsInHand() > 0) {
                            this->counter = 0;
                            this->nextState = GameState::Game_EndOfTrick;
                        }
                        else {
                            this->nextState = GameState::Game_EndOfHand;
                            this->eog = 0;
                        }

                    }
                    else {
                        this->nextState = GameState::None;
                    }

                }

                this->incMode();

            }

            break;

        case GameState::Game_EndOfTrick:

            if (PC::buttons.pressed(BTN_A)) { 

                if (this->hands[0].getCardsInHand() == 0) {
    
                    this->gameState = GameState::Game_EndOfHand;
                    this->eog = 0;

                }
                else {

                    uint8_t winner = this->gameStatus.whoWon();
                    this->gameStatus.initHand(winner);
                    this->nextState = GameState::Game_LeadCard;
                    this->dialogCursor = 0;
                    this->text = nullptr;
                    this->incMode(true, false);

                }

            }

            break;

        case GameState::Game_EndOfHand:
            {
                uint8_t winner = this->gameStatus.whoWon();

                if (this->counter == 0) {

                    Utils::print(Debug::Play, "Player %i wins.  Player %i bid.\n", winner, this->bidWinner());

                    this->counter = 1;

                    if (this->bidWinner() == 0 || this->bidWinner() == 2) {

                        switch (this->gameStatus.getTricks0and2()) {

                            case 0 ... 2:
                                this->gameStatus.incHands((this->bidWinner() + 1) % 4, 2);
                                break;

                            case 3 ... 4:
                                this->gameStatus.incHands(this->bidWinner(), 1);
                                break;

                            case 5:
                                if (!this->gameStatus.getPlayAlone()) {
                                    this->gameStatus.incHands(this->bidWinner(), 2);
                                }
                                else {
                                    this->gameStatus.incHands(this->bidWinner(), 4);
                                }
                                break;

                        }                

                    }

                    else if (this->bidWinner() == 1 || this->bidWinner() == 3) {

                        switch (this->gameStatus.getTricks1and3()) {

                            case 0 ... 2:
                                this->gameStatus.incHands((this->bidWinner() + 1) % 4, 2);
                                break;

                            case 3 ... 4:
                                this->gameStatus.incHands(this->bidWinner(), 1);
                                break;

                            case 5:
                                if (!this->gameStatus.getPlayAlone()) {
                                    this->gameStatus.incHands(this->bidWinner(), 2);
                                }
                                else {
                                    this->gameStatus.incHands(this->bidWinner(), 4);
                                }
                                break;

                        }                

                    }

                }
                else  if (this->gameStatus.getPoints0and2() >= Constants::WinningPoints || this->gameStatus.getPoints1and3() >= Constants::WinningPoints) {

                    this->gameState = GameState::GameOver_Init;

                }
                else if (PC::buttons.pressed(BTN_A)) { 

                    this->gameState = GameState::Game_NewHand_Init;
                    this->gameStatus.incDealer();

                }

            }

            break;

        case GameState::GameOver_Init:

            this->gameState = GameState::GameOver;

            [[fallthrough]]

        case GameState::GameOver:

            if (this->counter < 255) this->counter++;

            if (PC::buttons.pressed(BTN_A)) { 

                this->gameState = GameState::Title_Init;

            } 

            break;

    }

    this->renderGame(false);


    // House keeping ..

    for (uint8_t i = 0; i < 4; i++) {
        this->hands[i].update();
    }

}
