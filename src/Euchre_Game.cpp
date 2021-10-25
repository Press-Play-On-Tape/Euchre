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
    this->dealer = 0;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game() {

// printf("%i\n", (uint16_t)this->gameState);
    // Handle player actions ..

    switch (this->gameState) {

        case GameState::Game_NewHand_Init:
printf("Game_NewHand_Init -------------------\n");

            this->deck.init();

            for (uint8_t i = 0; i < 4; i++) {
                this->hands[i].init(i);
            }

            this->counter = 0;
            this->deal = 0;
            this->dealerCard.init(Cards::NoCard);

            this->print();

            this->threshold = 160;
            this->bidCursor = 0;
            this->dialogCursor = 0;
            this->playAlone = false;
            this->gameState = GameState::Game_NewHand_00;
            this->gameStatus.init();
            [[fallthrough]]

        case GameState::Game_NewHand_00 ... GameState::Game_NewHand_07:

            if (counter == 0) {

                Card card = this->deck.dealCard();
                this->hands[this->deal / 2].addCard(card);
                this->hands[this->deal / 2].shuffleHand();
print();

            }
            
            this->incMode();
            break;

        case GameState::Game_NewHand_08 ... GameState::Game_NewHand_19:

            if (counter == 0) {

                Card card = this->deck.dealCard();
                this->hands[(this->deal - 8) / 3].addCard(card);
                this->hands[(this->deal - 8) / 3].shuffleHand();
print();
            }

            this->incMode();
            break;

        case GameState::Game_DealerCard:

            if (counter == 0) {

                this->dealerCard = this->deck.dealCard();

// this->dealerCard.init(CardSuit::Hearts, Cards::Seven);
// this->hands[0].getCard(0).init(CardSuit::Spades, Cards::Four);
// this->hands[0].getCard(1).init(CardSuit::Spades, Cards::Jack);
// this->hands[0].getCard(2).init(CardSuit::Diamonds, Cards::King);
// this->hands[0].getCard(3).init(CardSuit::Hearts, Cards::Jack);
// this->hands[0].getCard(4).init(CardSuit::Hearts, Cards::King);

                printf("Hands -----------------------\n");
                for (uint8_t i = 0; i < 4; i++) {

                    printf("Hand %i >> ", i);
                    uint16_t score = this->hands[i].bid(this->dealerCard.getSuit(CardSuit::None), this->dealerCard, false);

                }

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

                if ((this->dealer + offset) % 4 == 0) {

                    this->handlePlayerBid((this->dealer + offset) % 4);

                }
                else {

                    if (counter == 0) {

                        if (this->hands[(this->dealer + offset) % 4].bid(this->dealerCard.getSuit(CardSuit::None), this->dealerCard, false) > this->threshold) {

                            this->hands[(this->dealer + offset) % 4].setCallStatus(CallStatus::FirstRound);
                            this->gameStatus.setTrumps(dealerCard.getSuit(CardSuit::None));
                            this->nextState = GameState::Game_DealerExtraCard;

                        }
                        else {

                            this->hands[(this->dealer + offset) % 4].setCallStatus(CallStatus::Pass);

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

                if ((this->dealer + offset) % 4 == 0) {

                    this->handlePlayerSecondBid((this->dealer + offset) % 4);

                }
                else {

                    if (counter == 0) {
    printf("Round Two of Bidding --------------------------------------------------------\n");                    

                        this->doSecondBid((this->dealer + offset) % 4);

                    }

                    this->incMode();

                }

            }

            break;

        case GameState::Game_DealerExtraCard:

            if (this->dealer == 0) {

                if (this->hands[0].getCardsInHand() == 5) {

                    this->hands[0].addCard(this->dealerCard);
                    this->dealerCard.init(Cards::NoCard);

                }

                uint8_t card = this->handleDiscardACard(this->dealer % 4);

                if (card != Cards::NoCard) {;

                    this->hands[this->dealer % 4].removeCard(this->dialogCursor);
                    this->gameState = GameState::Game_StartPlay;

                }

            }
            else {

                if (counter == 0) {

                    this->hands[this->dealer].selectBestFive(this->gameStatus.getTrumps(), this->dealerCard);

                }

                this->incMode();

            }

            break;


        case GameState::Game_StartPlay:
            this->gameState++;
            this->gameStatus.initHand((this->dealer + 1) % 4);
            this->dialogCursor = 0;
            this->dealerCard.init(Cards::NoCard);
            this->counter = 0;
            [[fallthrough]]       


        case GameState::Game_LeadCard:


printf("Start of Play --------------------------------------------------------\n");
this->hands[0].print();
this->hands[1].print();
this->hands[2].print();
this->hands[3].print();
printf("Current player %i\n", this->gameStatus.getCurrentPlayer());
printf("----------------------------------------------------------------------\n");
                    printf("Lead GameState: %i\n", (uint16_t)this->gameState);


            if (this->gameStatus.getCurrentPlayer() == 0) {

                uint8_t selectedCard = this->handlePlayACard(this->gameStatus.getCurrentPlayer(), CardSuit::None);

                if (selectedCard != Cards::NoCard) {

                    Card card = this->hands[this->gameStatus.getCurrentPlayer()].getCard(selectedCard);
                    this->hands[this->gameStatus.getCurrentPlayer()].removeCard(selectedCard);

                    this->gameStatus.playCard(card);

                    printf("Player %i leads a ", this->gameStatus.getCurrentPlayer());
                    card.print();
                    printf(".\n");

                    this->gameStatus.incCurrentPlayer();
                    this->gameState = GameState::Game_Follow_01;
                    this->bidCursor = 0;

                }

            }   
            else {

                uint8_t i = this->hands[this->gameStatus.getCurrentPlayer()].leadACard(this->gameStatus.getTrumps(), this->gameStatus, this->hands[this->gameStatus.getCurrentPlayer()].isBidWinner(), this->hands[(this->gameStatus.getCurrentPlayer() + 2) % 4].isBidWinner());
                // printf("Card Selected %i\n", i);
                Card card = this->hands[this->gameStatus.getCurrentPlayer()].getCard(i);
                // printf("sdfsdfsdfsdfsdf\n");
                // printf("Card Selected ");
                // card.print();
                // printf(".");
                this->hands[this->gameStatus.getCurrentPlayer()].removeCard(i);
// printf("...3a\n");

                this->gameStatus.playCard(card);
// printf("...3b\n");

                printf("Player %i leads a ", this->gameStatus.getCurrentPlayer());
                card.print();
                printf(".\n");

                this->gameStatus.incCurrentPlayer();
                this->gameState = GameState::Game_Follow_01;

            }         

            break;

        case GameState::Game_Follow_01:
        case GameState::Game_Follow_02:
        case GameState::Game_Follow_03:

            if (this->gameStatus.getCurrentPlayer() == 0) {

                uint8_t selectedCard = this->handlePlayACard(this->gameStatus.getCurrentPlayer(), this->gameStatus.getSuitLed());

                if (selectedCard != Cards::NoCard) {

                    Card card = this->hands[this->gameStatus.getCurrentPlayer()].getCard(selectedCard);
                    this->hands[this->gameStatus.getCurrentPlayer()].removeCard(selectedCard);
// printf("....1A\n");
                    this->gameStatus.playCard(card);
// printf("....1B\n");

                    printf("Player %i follows with a ", this->gameStatus.getCurrentPlayer());
                    card.print();
                    printf(".\n");
                    printf("GameState: %i\n", (uint16_t)this->gameState);

                    this->gameStatus.incCurrentPlayer();
                    this->bidCursor = 0;

                    if (this->gameState == GameState::Game_Follow_03) {
printf("Ypu pressed a key\n");
                        uint8_t winner = this->gameStatus.whoWon();
                        printf("Player %i wins.\n", winner);
                        this->gameStatus.incTricks(winner);
                        
                        if (this->hands[0].getCardsInHand() > 0) {

                            if (winner == 0 || winner == 2) {

                                switch (this->gameStatus.getTricks0and2()) {

                                    case 0 ... 2:
                                        this->gameStatus.incHands((winner + 1) % 4, 2);
                                        break;

                                    case 3 ... 4:
                                        this->gameStatus.incHands(winner, 1);
                                        break;

                                    case 5:
                                        if (this->playAlone) {
                                            this->gameStatus.incHands(winner, 2);
                                        }
                                        else {
                                            this->gameStatus.incHands(winner, 4);
                                        }
                                        break;

                                }                

                            }

                            if (winner == 1 || winner == 3) {

                                switch (this->gameStatus.getTricks1and3()) {

                                    case 0 ... 2:
                                        this->gameStatus.incHands((winner + 1) % 4, 2);
                                        break;

                                    case 3 ... 4:
                                        this->gameStatus.incHands(winner, 1);
                                        break;

                                    case 5:
                                        if (this->playAlone) {
                                            this->gameStatus.incHands(winner, 2);
                                        }
                                        else {
                                            this->gameStatus.incHands(winner, 4);
                                        }
                                        break;

                                }                

                            }
                            
                            this->gameState = GameState::Game_EndOfTrick;
                        }
                        else {
                            printf("this->gameState = GameState::Game_EndOfHand;\n");
                            this->gameState = GameState::Game_EndOfHand;
                        }

                    }
                    else {

                        printf("GameState: %i, this->gameState++;\n ", (uint16_t)this->gameState);                        
                        this->gameState++;
                        this->counter = 0;//SJH??
                    }

                }

            }   
            else {

                if (this->counter == 0) {
printf("----------------------------------------------------------------------\n");
                        
                    uint8_t i = this->hands[this->gameStatus.getCurrentPlayer()].followACard(this->gameStatus);
                    Card card = this->hands[this->gameStatus.getCurrentPlayer()].getCard(i);
                    this->hands[this->gameStatus.getCurrentPlayer()].removeCard(i);
    // printf("...2A\n");
                    this->gameStatus.playCard(card);
    // printf("...2B\n");

                    printf("Player %i follows with a ", this->gameStatus.getCurrentPlayer());
                    card.print();
                    printf(".\n");
                    printf("GameState: %i\n ", (uint16_t)this->gameState);     


                    if (this->gameState == GameState::Game_Follow_03) {

                        uint8_t winner = this->gameStatus.whoWon();
                        printf("Player %i wins.\n", winner);
                        this->gameStatus.incTricks(winner);

                        if (this->hands[0].getCardsInHand() > 0) {
                            this->nextState = GameState::Game_EndOfTrick;
                        }
                        else {
                            this->nextState = GameState::Game_EndOfHand;
                        }

                    }
                    else {
                        this->nextState = GameState::None;
                    }
                    // else { SJH
                    //     this->gameState++;
                    // }

                }

printf("this->counter %i\n", this->counter);
                this->incMode();

            }

            break;

        case GameState::Game_EndOfTrick:

            if (PC::buttons.pressed(BTN_A)) { 
printf("case GameState::Game_EndOfTrick:\n");                
                if (this->hands[0].getCardsInHand() == 0) {
    
                    this->gameState = GameState::Game_EndOfHand;

                }
                else {

                    uint8_t winner = this->gameStatus.whoWon();
                    this->gameStatus.initHand(winner);
                    this->gameState = GameState::Game_LeadCard;
                    this->dialogCursor = 0;
                    this->text = nullptr;

                }

            }

            break;

        case GameState::Game_EndOfHand:
            {
                uint8_t winner = this->gameStatus.whoWon();
                printf("Player %i wins.  Player %i bid.\n", winner, this->bidWinner());

                if (PC::buttons.pressed(BTN_A)) { 
   
                    this->dealer = (this->dealer + 1) % 4;
                    this->text = nullptr;
                    this->gameState = GameState::Game_NewHand_Init;
                    printf("Change to init\n");

                }

            }

            break;

        case GameState::Game_Xxx:

            if (PC::buttons.pressed(BTN_A)) { 

                this->gameState = GameState::Game_NewHand_Init;

            } 

            break;

    }

    this->renderGame();


    // House keeping ..

    for (uint8_t i = 0; i < 4; i++) {
        this->hands[i].update();
    }

}
