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
    this->gameStatus.setDealer(0);

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

            this->upperThreshold = 80;
            this->threshold = 75;
            this->bidCursor = 0;
            this->dialogCursor = 0;
            this->gameState = GameState::Game_NewHand_00;
            this->gameStatus.init();
            // this->dealer = 3; ///SJH remove
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

                if ((this->gameStatus.getDealer() + offset) % 4 == 0) {

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
                            this->gameStatus.setTrumps(dealerCard.getSuit(CardSuit::None));
                            this->gameStatus.setPlayAlone(true);
                            this->nextState = GameState::Game_DealerExtraCard;

                            for (uint8_t i = 0; i < 4; i++) {

                                this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                            }

                        }
                        else if (this->hands[(this->gameStatus.getDealer() + offset) % 4].bid(this->dealerCard.getSuit(CardSuit::None), this->dealerCard, false) > this->threshold) {

                            this->hands[(this->gameStatus.getDealer() + offset) % 4].setCallStatus(CallStatus::FirstRound);
                            this->gameStatus.setTrumps(dealerCard.getSuit(CardSuit::None));
                            this->gameStatus.setPlayAlone(false);
                            this->nextState = GameState::Game_DealerExtraCard;

                            for (uint8_t i = 0; i < 4; i++) {

                                this->hands[i].shuffleHandTrumps(this->gameStatus.getTrumps());

                            }

                        }
                        else {

                            this->hands[(this->gameStatus.getDealer() + offset) % 4].setCallStatus(CallStatus::Pass);

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

                if ((this->gameStatus.getDealer() + offset) % 4 == 0) {

                    this->handlePlayerSecondBid((this->gameStatus.getDealer() + offset) % 4);

                }
                else {

                    if (counter == 0) {
    printf("Round Two of Bidding --------------------------------------------------------\n");                    

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

            if (this->gameStatus.getDealer() == 0) {

                if (this->hands[0].getCardsInHand() == 5) {

                    this->hands[0].addCard(this->dealerCard);
                    this->dealerCard.init(Cards::NoCard);
                    this->hands[0].shuffleHandTrumps(this->gameStatus.getTrumps());

                }

                uint8_t card = this->handleDiscardACard(this->gameStatus.getDealer() % 4);

                if (card != Cards::NoCard) {;

                    this->hands[this->gameStatus.getDealer() % 4].removeCard(this->dialogCursor);
                    this->gameState = GameState::Game_StartPlay;

                }

            }
            else {

                if (counter == 0) {

                    this->hands[this->gameStatus.getDealer()].selectBestFive(this->gameStatus.getTrumps(), this->dealerCard);

                }

                this->incMode();

            }

            break;


        case GameState::Game_StartPlay:

            this->gameState++;
            this->gameStatus.initHand((this->gameStatus.getDealer() + 1) % 4);
            this->dialogCursor = 0;
            this->dealerCard.init(Cards::NoCard);
            this->counter = 0;

            if (!this->isPlayingThisHand(this->gameStatus.getCurrentPlayer())) {

                this->gameState++;
                this->gameStatus.incCurrentPlayer();

            }

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

                    this->gameStatus.setFirstPlayer(this->gameStatus.getCurrentPlayer());
                    this->gameStatus.incCurrentPlayer();
                    this->bidCursor = 0;
                    this->counter = 0;

                    if (!this->isPlayingThisHand(this->gameStatus.getCurrentPlayer())) {

                        this->gameState = GameState::Game_Follow_02;
                        this->gameStatus.incCurrentPlayer();
                        
                    }
                    else {

                        this->gameState = GameState::Game_Follow_01;

                    }


                }

            }   
            else {

                if (this->counter == 0) {
                    uint8_t i = this->hands[this->gameStatus.getCurrentPlayer()].leadACard(this->gameStatus.getTrumps(), this->gameStatus, this->hands[this->gameStatus.getCurrentPlayer()].isBidWinner(), this->hands[(this->gameStatus.getCurrentPlayer() + 2) % 4].isBidWinner(), this->hands[this->gameStatus.getCurrentPlayer()].isBidWinner() && this->gameStatus.getPlayAlone());
                    // printf("Card Selected %i\n", i);
                    Card card = this->hands[this->gameStatus.getCurrentPlayer()].getCard(i);
                    // printf("sdfsdfsdfsdfsdf\n");
                    // printf("Card Selected ");
                    // card.print();
                    // printf(".");
                    this->hands[this->gameStatus.getCurrentPlayer()].removeCard(i);
                    this->gameStatus.setFirstPlayer(this->gameStatus.getCurrentPlayer());
    // printf("...3a\n");

                    this->gameStatus.playCard(card);
    // printf("...3b\n");

                    printf("Player %i leads a ", this->gameStatus.getCurrentPlayer());
                    card.print();
                    printf(".\n");

                }

                this->incMode();

            }         

            break;

        case GameState::Game_Follow_01:
        case GameState::Game_Follow_02:
        case GameState::Game_Follow_03:

            if (this->gameStatus.getCurrentPlayer() == 0) {

                switch (this->counter) {

                    case 0:
                        {                        
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

                                // this->gameStatus.incCurrentPlayer();
                                this->bidCursor = 0;

                                if (this->gameState == GameState::Game_Follow_03) {
            printf("Ypu pressed a key\n");
                                    uint8_t winner = this->gameStatus.whoWon();
                                    printf("Player %i wins.\n", winner);
                                    this->gameStatus.incTricks(winner);
                                    
                                    if (this->hands[0].getCardsInHand() > 0) {

                                        // this->counter = 0;
                                        printf("this->nextState = GameState::Game_EndOfTrick;\n");
                                        this->nextState = GameState::Game_EndOfTrick;

                                    }
                                    else {
                                        printf("this->nextState = GameState::Game_EndOfHand;\n");
                                        this->nextState = GameState::Game_EndOfHand;
                                    }

                                }
                                else {

                                    printf("GameState: %i, this->nextState = none;\n ", (uint16_t)this->gameState);                        
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
                            this->counter = 0;
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

// printf("this->counter %i\n", this->counter);
                this->incMode();

            }

            break;

        case GameState::Game_EndOfTrick:

            if (this->counter == 0) {

                // this->counter = 1;
                // uint8_t winner = this->gameStatus.whoWon();

                // if (winner == 0 || winner == 2) {

                //     switch (this->gameStatus.getTricks0and2()) {

                //         case 0 ... 2:
                //             this->gameStatus.incHands((winner + 1) % 4, 2);
                //             break;

                //         case 3 ... 4:
                //             this->gameStatus.incHands(winner, 1);
                //             break;

                //         case 5:
                //             if (!this->gameStatus.getPlayAlone()) {
                //                 this->gameStatus.incHands(winner, 2);
                //             }
                //             else {
                //                 this->gameStatus.incHands(winner, 4);
                //             }
                //             break;

                //     }                

                // }

                // if (winner == 1 || winner == 3) {

                //     switch (this->gameStatus.getTricks1and3()) {

                //         case 0 ... 2:
                //             this->gameStatus.incHands((winner + 1) % 4, 2);
                //             break;

                //         case 3 ... 4:
                //             this->gameStatus.incHands(winner, 1);
                //             break;

                //         case 5:
                //             if (!this->gameStatus.getPlayAlone()) {
                //                 this->gameStatus.incHands(winner, 2);
                //             }
                //             else {
                //                 this->gameStatus.incHands(winner, 4);
                //             }
                //             break;

                //     }                

                // }

            }


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
                    this->counter = 0;

                }

            }

            break;

        case GameState::Game_EndOfHand:
            {
                uint8_t winner = this->gameStatus.whoWon();

                if (this->counter == 0) {
                printf("Player %i wins.  Player %i bid.\n", winner, this->bidWinner());

                    this->counter = 1;
                    //uint8_t winner = this->gameStatus.whoWon();

                    if (winner == 0 || winner == 2) {

                        switch (this->gameStatus.getTricks0and2()) {

                            case 0 ... 2:
                                this->gameStatus.incHands((winner + 1) % 4, 2);
printf("Euchre +2\n");                                
                                break;

                            case 3 ... 4:
                                this->gameStatus.incHands(winner, 1);
printf("Normal +1\n");                                
                                break;

                            case 5:
                                if (!this->gameStatus.getPlayAlone()) {
printf("Team +2\n");                                
                                    this->gameStatus.incHands(winner, 2);
                                }
                                else {
printf("Alone +4\n");                                
                                    this->gameStatus.incHands(winner, 4);
                                }
                                break;

                        }                

                    }

                    if (winner == 1 || winner == 3) {

                        switch (this->gameStatus.getTricks1and3()) {

                            case 0 ... 2:
                                this->gameStatus.incHands((winner + 1) % 4, 2);
printf("Euchre +2\n");                                       
                                break;

                            case 3 ... 4:
 printf("Normal +1\n"); 
                                this->gameStatus.incHands(winner, 1);
                                break;

                            case 5:
                                if (!this->gameStatus.getPlayAlone()) {
printf("Team +2\n"); 
                                    this->gameStatus.incHands(winner, 2);
                                }
                                else {
printf("Alone +4\n");                                       
                                    this->gameStatus.incHands(winner, 4);
                                }
                                break;

                        }                

                    }

                }


                if (PC::buttons.pressed(BTN_A)) { 
   
                    this->gameStatus.setDealer((this->gameStatus.getDealer() + 1) % 4);
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
