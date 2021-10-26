#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderCard(Orientation orientation, Card card, int16_t x, int16_t y, bool highlight, bool raise, bool showCards) {

    uint8_t highlight_offset = (raise ? 6 : 0);

    switch (orientation) {

        case Orientation::Bottom:

            if (!highlight) {

                PD::drawBitmap(x, y, Images::Card_Front);
                PD::drawBitmap(x + 5, y + 15, Images::Suits_Bot[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);
                PD::drawBitmap(x + 29, y + 36, Images::Suits_Top[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);

                switch (card.getSuit(CardSuit::None)) {

                    case CardSuit::Spades:
                    case CardSuit::Clubs:
                        PD::drawBitmap(x + 3, y + 6, Images::Numbers_Bot_Blk[card.getNumber() - 7]);
                        PD::drawBitmap(x + 28, y + 45, Images::Numbers_Top_Blk[card.getNumber() - 7]);
                        break;

                    case CardSuit::Diamonds:
                    case CardSuit::Hearts:
                        PD::drawBitmap(x + 3, y + 6, Images::Numbers_Bot_Red[card.getNumber() - 7]);
                        PD::drawBitmap(x + 28, y + 45, Images::Numbers_Top_Red[card.getNumber() - 7]);
                        break;
                                    
                }

            }
            else {

                PD::drawBitmap(x, y - highlight_offset, Images::Card_Front_Highlight);
                PD::drawBitmap(x + 5, y + 15 - highlight_offset, Images::Suits_Bot[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);
                PD::drawBitmap(x + 29, y + 36 - highlight_offset, Images::Suits_Top[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);

                switch (card.getSuit(CardSuit::None)) {

                    case CardSuit::Spades:
                    case CardSuit::Clubs:
                        PD::drawBitmap(x + 3, y + 6 - highlight_offset, Images::Numbers_Bot_Blk[card.getNumber() - 7]);
                        PD::drawBitmap(x + 28, y + 45 - highlight_offset, Images::Numbers_Top_Blk[card.getNumber() - 7]);
                        break;

                    case CardSuit::Diamonds:
                    case CardSuit::Hearts:
                        PD::drawBitmap(x + 3, y + 6 - highlight_offset, Images::Numbers_Bot_Red[card.getNumber() - 7]);
                        PD::drawBitmap(x + 28, y + 45 - highlight_offset, Images::Numbers_Top_Red[card.getNumber() - 7]);
                        break;
                                    
                }

            }

            break;
        
        case Orientation::Left:

            if (showCards) {
                    
                PD::drawBitmap(x, y, Images::Card_Front_Rot);
                PD::drawBitmap(x + 35, y + 6, Images::Suits_Left[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);

                switch (card.getSuit(CardSuit::None)) {

                    case CardSuit::Spades:
                    case CardSuit::Clubs:
                        PD::drawBitmap(x + 45, y + 4, Images::Numbers_Left_Blk[card.getNumber() - 7]);
                        break;

                    case CardSuit::Diamonds:
                    case CardSuit::Hearts:
                        PD::drawBitmap(x + 45, y + 4, Images::Numbers_Left_Red[card.getNumber() - 7]);
                        break;
                    
                }

            }
            else {

                PD::drawBitmap(x, y, Images::Card_Back_Rot);

            }
            
            break;


        case Orientation::Top:

            if (showCards) {
                    
                PD::drawBitmap(x, y, Images::Card_Front);
                PD::drawBitmap(x + 28, y + 36, Images::Suits_Top[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);

                switch (card.getSuit(CardSuit::None)) {

                    case CardSuit::Spades:
                    case CardSuit::Clubs:
                        PD::drawBitmap(x + 26, y + 46, Images::Numbers_Top_Blk[card.getNumber() - 7], ROT180, NOFLIP);
                        break;

                    case CardSuit::Diamonds:
                    case CardSuit::Hearts:
                        PD::drawBitmap(x + 26, y + 46, Images::Numbers_Top_Red[card.getNumber() - 7], ROT180, NOFLIP);
                        break;
                                    
                }

            }
            else {

                PD::drawBitmap(x, y, Images::Card_Back);

            }

            break;

        case Orientation::Right:

            if (showCards) {
                        
                PD::drawBitmap(x, y, Images::Card_Front_Rot);
                PD::drawBitmap(x + 16, y + 28, Images::Suits_Right[static_cast<uint8_t>(card.getSuit(CardSuit::None))], ROT180, NOFLIP);

                switch (card.getSuit(CardSuit::None)) {

                    case CardSuit::Spades:
                    case CardSuit::Clubs:
                        PD::drawBitmap(x + 6, y + 26, Images::Numbers_Right_Blk[card.getNumber() - 7], ROT180, NOFLIP);
                        break;

                    case CardSuit::Diamonds:
                    case CardSuit::Hearts:
                        PD::drawBitmap(x + 6, y + 26, Images::Numbers_Right_Red[card.getNumber() - 7], ROT180, NOFLIP);
                        break;
                    
                }

            }
            else {

                PD::drawBitmap(x, y, Images::Card_Back_Rot);

            }
            
            break;
    }
    
}

void Game::renderGame() {

    PD::fillScreen(3);



    // Highlight players card?
    
    bool highlightCard = false;

    switch (this->gameState) {

        case GameState::Game_DealerExtraCard:
            if (this->gameStatus.getDealer() % 4 == 0) { 
                highlightCard = true; 
            }
            break;

        case GameState::Game_LeadCard ... GameState::Game_Follow_03:
            if (this->gameStatus.getCurrentPlayer() == 0) { 
                highlightCard = true; 
            }
            break;

        default: break;

    }



    // Render Hands ---------------------------------------------------------------------------------------

    // Player 0

    uint8_t x0 = 40 + ((this->hands[0].getCardsInHand() - 1) * 16);
    uint8_t y1 = 40 + ((this->hands[1].getCardsInHand() - 1) * 16);
    uint8_t x2 = 40 + ((this->hands[2].getCardsInHand() - 1) * 16);
    uint8_t y3 = 40 + ((this->hands[1].getCardsInHand() - 1) * 16);

    switch (this->gameState) {

        case GameState::Game_NewHand_00 ... GameState::Game_EndOfTrick:

            for (uint8_t i = 0; i < this->hands[0].getCardsInHand(); i++) {

                this->renderCard(Orientation::Bottom, this->hands[0].getCard(i), (110 - (x0 / 2)) + (i * 16), 151, this->bidCursor == i && highlightCard, this->bidCursor == i && highlightCard, false);

            }

            if (this->gameStatus.getDealer() == 0) { PD::drawBitmap(110 + (x0 / 2) + 1, 165, Images::Dealer_Bot); }


            // Player 1

            for (uint8_t i = 0; i < this->hands[1].getCardsInHand(); i++) {

                this->renderCard(Orientation::Left, this->hands[1].getCard(i), -33, (88 - (y1 / 2)) + (i * 16), false, false, this->gameStatus.getShowHands());

            }

            if (this->gameStatus.getDealer() == 1) { PD::drawBitmap(2, (88 + (y1 / 2)) + 1, Images::Dealer_Left); }


            // Player 2

            for (uint8_t i = 0; i < this->hands[2].getCardsInHand(); i++) {

                this->renderCard(Orientation::Top, this->hands[2].getCard(i), (70 + (x2 / 2)) - (i * 16), -34, false, false, this->gameStatus.getShowHands());

            }

            if (this->gameStatus.getDealer() == 2) { PD::drawBitmap(110 - (x2 / 2) - 11, 2, Images::Dealer_Top); }


            // Player 3

            for (uint8_t i = 0; i < this->hands[3].getCardsInHand(); i++) {

                this->renderCard(Orientation::Right, this->hands[3].getCard(i), 194, (48 + (y3 / 2)) - (i * 16), false, false, this->gameStatus.getShowHands());

            }

            if (this->gameStatus.getDealer() == 3) { PD::drawBitmap(209, (88 - (y3 / 2)) - 11, Images::Dealer_Right); }


            // Display trick count ..

            switch (this->gameState) {

                case GameState::Game_StartPlay ... GameState::Game_EndOfHand:
                    PD::drawBitmap(110 + (x0 / 2) + 1, 165 - (this->gameStatus.getDealer() == 0 ? 10 : 0), Images::Tricks_Bot[this->gameStatus.getTricks(0)]); 
                    PD::drawBitmap(2 + (this->gameStatus.getDealer() == 1 ? 10 : 0), (88 + (y1 / 2)) + 1, Images::Tricks_Left[this->gameStatus.getTricks(1)]);
                    PD::drawBitmap(110 - (x2 / 2) - 11, 2 + (this->gameStatus.getDealer() == 2 ? 10 : 0), Images::Tricks_Top[this->gameStatus.getTricks(2)]);
                    PD::drawBitmap(209 - (this->gameStatus.getDealer() == 3 ? 10 : 0), (88 - (y3 / 2)) - 11, Images::Tricks_Right[this->gameStatus.getTricks(3)]);
                    break;

                default: break;

            }

            break;

        default: break;

    }


    // Dealer card 

    if (this->dealerCard.getCardIndex() != Cards::NoCard) {

        this->renderCard(Orientation::Bottom, this->dealerCard, 90, 59, false, false, true);
    
    }


    // Render Played Cards -----------------------------------------------------------------------------------

//    for (uint8_t i = this->gameStatus.getCurrentPlayer() + 1; i < this->gameStatus.getCurrentPlayer() + 5; i++) {
    // printf("First Player %i, ", this->gameStatus.getFirstPlayer());
    for (uint8_t i = this->gameStatus.getFirstPlayer(); i < this->gameStatus.getFirstPlayer() + 4; i++) {
    // printf(" %i", (i %4));

        if (i % 4 == 0) {
            if (this->gameStatus.getCurrentHand(0).getNumber() != Cards::NoCard) {
                this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(0), 95, 80, this->gameStatus.isPlayerWinning(0) && this->gameStatus.getShowWinner(), false, true);
            }
        }

        if (i % 4 == 1) {
            if (this->gameStatus.getCurrentHand(1).getNumber() != Cards::NoCard) {
                this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(1), 70, 65, this->gameStatus.isPlayerWinning(1) && this->gameStatus.getShowWinner(), false, this->gameStatus.getShowHands());
            }
        }

        if (i % 4 == 2) {
            if (this->gameStatus.getCurrentHand(2).getNumber() != Cards::NoCard) {
                this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(2), 85, 40, this->gameStatus.isPlayerWinning(2) && this->gameStatus.getShowWinner(), false, this->gameStatus.getShowHands());
            }
        }

        if (i % 4 == 3) {
            if (this->gameStatus.getCurrentHand(3).getNumber() != Cards::NoCard) {
                this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(3), 110, 55, this->gameStatus.isPlayerWinning(3) && this->gameStatus.getShowWinner(), false, this->gameStatus.getShowHands());
            }
        }

    }
    // printf(" \n");


    // Bid?

    switch (this->gameState) {

        case GameState::Game_Bid_00:
        case GameState::Game_Bid_01:
        case GameState::Game_Bid_02:
        case GameState::Game_Bid_03:
            {
                uint8_t offset = (static_cast<uint8_t>(this->gameState) - static_cast<uint8_t>(GameState::Game_Bid_00) + 1) % 4;
                this->renderBids();
                if ((this->gameStatus.getDealer() + offset) % 4 == 0)    { 

                    this->renderPlayerBid(); 
                }

            }
            break;

        case GameState::Game_Open_Bid_00:
        case GameState::Game_Open_Bid_01:
        case GameState::Game_Open_Bid_02:
        case GameState::Game_Open_Bid_03:
            {
                uint8_t offset = (static_cast<uint8_t>(this->gameState) - static_cast<uint8_t>(GameState::Game_Bid_00) + 1) % 4;
                this->renderBids();
                if ((this->gameStatus.getDealer() + offset) % 4 == 0) { 
                    this->renderPlayerSecondBid();
                }

            }
            break;

        case GameState::Game_DealerExtraCard:
            this->renderFinalBid();
            this->renderSoreboard(Constants::AllWinners, true, true);
            this->renderTrumps(this->gameStatus.getTrumps());
            if (this->gameStatus.getDealer() % 4 == 0) { 
                this->renderDiscardACard(); 
            }
            break;

        case GameState::Game_LeadCard ... GameState::Game_Follow_03:
            this->renderFinalBid();
            this->renderSoreboard(Constants::AllWinners, true, true);
            this->renderTrumps(this->gameStatus.getTrumps());
            if (this->gameStatus.getCurrentPlayer() == 0) { 
                this->renderPlayACard(); 
            }
            break;

        case GameState::Game_EndOfTrick:
            {
                uint8_t winner = this->gameStatus.whoWon();
                this->renderFinalBid();
                this->renderSoreboard(winner, PC::frameCount % 32 < 16, true);
                this->renderTrumps(this->gameStatus.getTrumps());
                this->renderTrickOver(winner);
            }
            break;

        case GameState::Game_EndOfHand:
            {
                uint8_t winner = 0;

                if (this->bidWinner() == 0 || this->bidWinner() == 2) {

                    switch (this->gameStatus.getTricks0and2()) {

                        case 0 ... 2:
                            winner = 1;
                            break;

                        default:
                            winner = 0;
                            break;

                    }                

                }

                if (this->bidWinner() == 1 || this->bidWinner() == 3) {

                    switch (this->gameStatus.getTricks1and3()) {

                        case 0 ... 2:
                            winner = 0;
                            break;

                        default:
                            winner = 1;
                            break;

                    }                

                }

                this->renderSoreboard(winner, true, PC::frameCount % 32 < 16);
                this->renderTrumps(this->gameStatus.getTrumps());
                this->renderHandOver(winner);
            }
            break;

    }


    PD::setCursor(200, 168);
    PD::print(static_cast<uint16_t>(this->gameState));

}

void Game::renderSoreboard(uint8_t winner, bool showTrick, bool showHand) {

    // Score board ..

    PD::drawBitmap(166, 0, Images::Scoreboard);
    if (winner == Constants::AllWinners || ((winner == 0 || winner == 2) && showTrick) || winner == 1 || winner == 3) PD::drawBitmap(195, 1, Images::Tricks_Bot[this->gameStatus.getTricks0and2()]);
    if (winner == Constants::AllWinners || ((winner == 0 || winner == 2) && showHand) || winner == 1 || winner == 3) PD::drawBitmap(206, 1, Images::Hands_Bot[this->gameStatus.getPoints0and2()]);
    if (winner == Constants::AllWinners || ((winner == 1 || winner == 3) && showTrick) || winner == 0 || winner == 2) PD::drawBitmap(195, 11, Images::Tricks_Bot[this->gameStatus.getTricks1and3()]);
    if (winner == Constants::AllWinners || ((winner == 1 || winner == 3) && showHand) || winner == 0 || winner == 2) PD::drawBitmap(206, 11, Images::Hands_Bot[this->gameStatus.getPoints1and3()]);

}

void Game::renderBids() {

    if (this->hands[0].showCallStatus()) {
        if (this->hands[0].getCallStatus() == CallStatus::Pass)                                             { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_Pass); }
        if (this->hands[0].getCallStatus() == CallStatus::FirstRound && !this->gameStatus.getPlayAlone())   { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_TakeIt); }
        if (this->hands[0].getCallStatus() == CallStatus::FirstRound &&  this->gameStatus.getPlayAlone())   { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_Alone); }
        if (this->hands[0].getCallStatus() == CallStatus::SecondRound && !this->gameStatus.getPlayAlone())  { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_Suits_Team[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
        if (this->hands[0].getCallStatus() == CallStatus::SecondRound && this->gameStatus.getPlayAlone())   { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_Suits_Alone[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
    }

    if (this->hands[1].showCallStatus()) {
        if (this->hands[1].getCallStatus() == CallStatus::Pass)                                             { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_Pass); }
        if (this->hands[1].getCallStatus() == CallStatus::FirstRound && !this->gameStatus.getPlayAlone())   { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_TakeIt); }
        if (this->hands[1].getCallStatus() == CallStatus::FirstRound &&  this->gameStatus.getPlayAlone())   { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_Alone); }
        if (this->hands[1].getCallStatus() == CallStatus::SecondRound && !this->gameStatus.getPlayAlone())  { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_Suits_Team[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
        if (this->hands[1].getCallStatus() == CallStatus::SecondRound && this->gameStatus.getPlayAlone())   { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_Suits_Alone[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
    }

    if (this->hands[2].showCallStatus()) {
        if (this->hands[2].getCallStatus() == CallStatus::Pass)                                             { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_Pass); }
        if (this->hands[2].getCallStatus() == CallStatus::FirstRound && !this->gameStatus.getPlayAlone())   { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_TakeIt); }
        if (this->hands[2].getCallStatus() == CallStatus::FirstRound &&  this->gameStatus.getPlayAlone())   { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_Alone); }
        if (this->hands[2].getCallStatus() == CallStatus::SecondRound && !this->gameStatus.getPlayAlone())  { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_Suits_Team[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
        if (this->hands[2].getCallStatus() == CallStatus::SecondRound && this->gameStatus.getPlayAlone())   { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_Suits_Alone[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
    }

    if (this->hands[3].showCallStatus()) {
        if (this->hands[3].getCallStatus() == CallStatus::Pass)                                             { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_Pass); }
        if (this->hands[3].getCallStatus() == CallStatus::FirstRound && !this->gameStatus.getPlayAlone())   { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_TakeIt); }
        if (this->hands[3].getCallStatus() == CallStatus::FirstRound &&  this->gameStatus.getPlayAlone())   { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_Alone); }
        if (this->hands[3].getCallStatus() == CallStatus::SecondRound && !this->gameStatus.getPlayAlone())  { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_Suits_Team[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
        if (this->hands[3].getCallStatus() == CallStatus::SecondRound && this->gameStatus.getPlayAlone())   { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_Suits_Alone[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
    }

}

void Game::renderFinalBid() {

    if (this->hands[0].isBidWinner()) { 
        
        if (this->gameStatus.getPlayAlone()) {
            PD::drawBitmap(90, Constants::Dialogue_00_Y, Images::Banner_Alone_Bot);
            PD::drawBitmap(94, Constants::Dialogue_00_Y + 1, Images::Suits_Bot[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }
        else {
            PD::drawBitmap(90, Constants::Dialogue_00_Y, Images::Banner_Team_Bot);
            PD::drawBitmap(94, Constants::Dialogue_00_Y + 1, Images::Suits_Bot[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }

    }

    if (this->hands[1].isBidWinner()) { 
        
        if (this->gameStatus.getPlayAlone()) {
            PD::drawBitmap(31, 68, Images::Banner_Alone_Left);
            PD::drawBitmap(32, 73, Images::Suits_Left[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }
        else {
            PD::drawBitmap(31, 68, Images::Banner_Team_Left);
            PD::drawBitmap(32, 73, Images::Suits_Left[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }

    }

    if (this->hands[2].isBidWinner()) { 
        
        if (this->gameStatus.getPlayAlone()) {
            PD::drawBitmap(90, 27, Images::Banner_Alone_Top);
            PD::drawBitmap(120, 28, Images::Suits_Top[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }
        else {
            PD::drawBitmap(90, 27, Images::Banner_Team_Top);
            PD::drawBitmap(120, 28, Images::Suits_Top[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }
    
    }

    if (this->hands[3].isBidWinner()) {
        
        if (this->gameStatus.getPlayAlone()) {
            PD::drawBitmap(180, 68, Images::Banner_Alone_Right);
            PD::drawBitmap(180, 98, Images::Suits_Right[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }
        else {
            PD::drawBitmap(180, 68, Images::Banner_Team_Right);
            PD::drawBitmap(180, 98, Images::Suits_Right[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }

    }

}

void Game::renderPlayerBid() {

    if (this->counter == 0) {

        PD::drawBitmap(52, 130, Images::Dialogue_Small_Background);

        if (this->dialogCursor == 0)    PD::drawBitmap(54, 132, Images::Dialogue_Pass);
        if (this->dialogCursor == 1)    PD::drawBitmap(92, 132, Images::Dialogue_Go);
        if (this->dialogCursor == 2)    PD::drawBitmap(130, 132, Images::Dialogue_Alone);

    }

}

void Game::renderPlayerSecondBid() {

    PD::drawBitmap(52, 90, Images::Dialogue_Large_Background);

    if (this->gameStatus.getStickIt() && (this->gameState == GameState::Game_Open_Bid_03))    PD::drawBitmap(54,   92, Images::Dialogue_Pass_Disabled);

    if (this->dialogCursor == 0)    PD::drawBitmap(54,   92, Images::Dialogue_Pass);
    if (this->dialogCursor == 1)    PD::drawBitmap(92,   92, Images::Dialogue_Go_Spades);
    if (this->dialogCursor == 2)    PD::drawBitmap(130,  92, Images::Dialogue_Alone_Spades);
    if (this->dialogCursor == 3)    PD::drawBitmap(92,  103, Images::Dialogue_Go_Clubs);
    if (this->dialogCursor == 4)    PD::drawBitmap(130, 103, Images::Dialogue_Alone_Clubs);
    if (this->dialogCursor == 5)    PD::drawBitmap(92,  114, Images::Dialogue_Go_Diamonds);
    if (this->dialogCursor == 6)    PD::drawBitmap(130, 114, Images::Dialogue_Alone_Diamonds);
    if (this->dialogCursor == 7)    PD::drawBitmap(92,  125, Images::Dialogue_Go_Hearts);
    if (this->dialogCursor == 8)    PD::drawBitmap(130, 125, Images::Dialogue_Alone_Hearts);

}

void Game::renderDiscardACard() {

    PD::drawBitmap(73, Constants::Dialogue_00_Y, Images::DiscardACard);

}

void Game::renderPlayACard() {

    PD::drawBitmap(80, Constants::Dialogue_00_Y, Images::PlayACard);

}

void Game::renderTrumps(CardSuit trumps) {

    PD::drawBitmap(0, 0, Images::Trumps);
    PD::drawBitmap(34, 1, Images::Suits_Bot[static_cast<uint8_t>(trumps)]);

}

void Game::renderTrickOver(uint8_t winner) {

    if ((this->gameStatus.getTrumps() != this->gameStatus.getSuitLed()) &&
        (this->gameStatus.getTrumps() == this->gameStatus.getCurrentHand(this->gameStatus.whoWon()).getSuit(this->gameStatus.getTrumps()))) {

        if (this->gameStatus.isPlayerWinning((this->gameStatus.whoWon() + 2) % 4, this->gameStatus.whoWon())) {

            text = Images::Text_Sorry;

        }
        else {
    
            text = Images::Text_Trumped;

        }

    }
    else {

        if (this->text == nullptr) {

            switch (random(0, 3)) {

                case 0:
                    text = Images::Text_Mine;
                    break;

                case 1:
                    text = Images::Text_Winner;
                    break;

                case 2:
                    text = Images::Text_WooHoo;
                    break;

            }

        }

    }

    switch (this->gameStatus.whoWon()) {

        case 0:
            PD::drawBitmap(88, 120, Images::Empty_Bottom); 
            PD::drawBitmap(91, 124, this->text); 
            break;

        case 1:
            PD::drawBitmap(20, 85, Images::Empty_Left); 
            PD::drawBitmap(30, 89, this->text); 
            break;

        case 2:
            PD::drawBitmap(96, 20, Images::Empty_Top); 
            PD::drawBitmap(99, 31, this->text); 
            break;

        case 3:
            PD::drawBitmap(140, 72, Images::Empty_Right); 
            PD::drawBitmap(144, 76, this->text); 
            break;

    }

}

void Game::renderHandOver(uint8_t winner) {

    if (this->bidWinner() == 0 || this->bidWinner() == 2) {

        switch (this->gameStatus.getTricks0and2()) {

            case 0 ... 2:
                PD::drawBitmap(45, 53, Images::Euchre);
                PD::drawBitmap(49, Constants::Dialogue_00_Y + 6, Images::TeamBeta);
                PD::drawBitmap(126, Constants::Dialogue_00_Y + 8, Images::EOG_02);
                break;

            case 3 ... 4:
                PD::drawBitmap(47, Constants::Dialogue_00_Y + 6, Images::TeamAlpha);
                PD::drawBitmap(128, Constants::Dialogue_00_Y + 8, Images::EOG_01);
                break;

            case 5:
                if (!this->gameStatus.getPlayAlone()) {
                    PD::drawBitmap(47, Constants::Dialogue_00_Y + 6, Images::TeamAlpha);
                    PD::drawBitmap(128, Constants::Dialogue_00_Y + 8, Images::EOG_02);
                }
                else {
                    PD::drawBitmap(47, Constants::Dialogue_00_Y + 6, Images::TeamAlpha);
                    PD::drawBitmap(128, Constants::Dialogue_00_Y + 8, Images::EOG_04);
                }
                break;

        }                

    }

    if (this->bidWinner() == 1 || this->bidWinner() == 3) {

        switch (this->gameStatus.getTricks1and3()) {

            case 0 ... 2:
                PD::drawBitmap(45, 53, Images::Euchre);
                PD::drawBitmap(47, Constants::Dialogue_00_Y + 4, Images::TeamAlpha);
                PD::drawBitmap(128, Constants::Dialogue_00_Y + 6, Images::EOG_02);
                break;

            case 3 ... 4:
                PD::drawBitmap(49, Constants::Dialogue_00_Y + 4, Images::TeamBeta);
                PD::drawBitmap(126, Constants::Dialogue_00_Y + 6, Images::EOG_01);
                break;

            case 5:
                if (!this->gameStatus.getPlayAlone()) {
                    PD::setCursor(40, 125);
                    PD::drawBitmap(49, Constants::Dialogue_00_Y + 4, Images::TeamBeta);
                    PD::drawBitmap(126, Constants::Dialogue_00_Y + 6, Images::EOG_02);
                }
                else {
                    PD::drawBitmap(49, Constants::Dialogue_00_Y + 4, Images::TeamBeta);
                    PD::drawBitmap(126, Constants::Dialogue_00_Y + 6, Images::EOG_04);
                }
                break;

        }                

    }

}

void Game::renderSuit(CardSuit suit) {

    switch (suit) {

        case CardSuit::Hearts:
            PD::print("H");
            break;

        case CardSuit::Diamonds:
            PD::print("D");
            break;

        case CardSuit::Clubs:
            PD::print("C");
            break;

        case CardSuit::Spades:
            PD::print("S");
            break;
            
    }

}