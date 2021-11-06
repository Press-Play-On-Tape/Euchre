#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderCard(Orientation orientation, Card card, int16_t x, int16_t y, bool highlight, bool raise, bool showCards, bool highlightAbleToPlay, bool ableToPlay) {

    uint8_t highlight_offset = (raise ? 6 : 0);

    switch (orientation) {

        case Orientation::Bottom:

            if (!highlight) {

                if (ableToPlay) {

//                    if (this->cookie)
                    if (highlightAbleToPlay) {
                        PD::drawBitmap(x, y, Images::Card_Front_Highlight);
                    }
                    else {
                        PD::drawBitmap(x, y, Images::Card_Front);
                    }
                    PD::drawBitmap(x + 5, y + 15, Images::Suits_Bot[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);
                    PD::drawBitmap(x + 29, y + 36, Images::Suits_Top[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);
//
                    switch (card.getSuit(CardSuit::None)) {

                        case CardSuit::Spades:
                        case CardSuit::Clubs:
                            PD::drawBitmap(x + 4, y + 6, Images::Numbers_Bot_Blk[card.getNumber() - 7]);
                            PD::drawBitmap(x + 28, y + 45, Images::Numbers_Top_Blk[card.getNumber() - 7]);
                            break;

                        case CardSuit::Diamonds:
                        case CardSuit::Hearts:
                            PD::drawBitmap(x + 4, y + 6, Images::Numbers_Bot_Red[card.getNumber() - 7]);
                            PD::drawBitmap(x + 28, y + 45, Images::Numbers_Top_Red[card.getNumber() - 7]);
                            break;
                                        
                    }

                }
                else {

                    // PD::drawBitmap(x, y, Images::Card_Front_Disabled);
                    // PD::drawBitmap(x + 5, y + 15, Images::Suits_Disabled_Bot[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);
                    PD::drawBitmap(x, y, Images::Card_Front);
                    PD::drawBitmap(x + 5, y + 15, Images::Suits_Bot[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);

                    switch (card.getSuit(CardSuit::None)) {

                        case CardSuit::Spades:
                        case CardSuit::Clubs:
//                            PD::drawBitmap(x + 4, y + 6, Images::Numbers_Bot_Blk_Disabled[card.getNumber() - 7]);
//                            // PD::drawBitmap(x + 28, y + 45, Images::Numbers_Top_Blk_Disabled[card.getNumber() - 7]);
                            PD::drawBitmap(x + 4, y + 6, Images::Numbers_Bot_Blk[card.getNumber() - 7]);
                            PD::drawBitmap(x + 28, y + 45, Images::Numbers_Top_Blk[card.getNumber() - 7]);
                            break;

                        case CardSuit::Diamonds:
                        case CardSuit::Hearts:
//                            PD::drawBitmap(x + 4, y + 6, Images::Numbers_Bot_Red_Disabled[card.getNumber() - 7]);
//                            // PD::drawBitmap(x + 28, y + 45, Images::Numbers_Top_Red_Disabled[card.getNumber() - 7]);
                            PD::drawBitmap(x + 4, y + 6, Images::Numbers_Bot_Red[card.getNumber() - 7]);
                            PD::drawBitmap(x + 28, y + 45, Images::Numbers_Top_Red[card.getNumber() - 7]);
                            break;
                                        
                    }

                }

            }
            else {

                PD::drawBitmap(x, y - highlight_offset, Images::Card_Front_Highlight);
                PD::drawBitmap(x + 5, y + 15 - highlight_offset, Images::Suits_Bot[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);
                PD::drawBitmap(x + 29, y + 36 - highlight_offset, Images::Suits_Top[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);

                switch (card.getSuit(CardSuit::None)) {

                    case CardSuit::Spades:
                    case CardSuit::Clubs:
                        PD::drawBitmap(x + 4, y + 6 - highlight_offset, Images::Numbers_Bot_Blk[card.getNumber() - 7]);
                        PD::drawBitmap(x + 28, y + 45 - highlight_offset, Images::Numbers_Top_Blk[card.getNumber() - 7]);
                        break;

                    case CardSuit::Diamonds:
                    case CardSuit::Hearts:
                        PD::drawBitmap(x + 4, y + 6 - highlight_offset, Images::Numbers_Bot_Red[card.getNumber() - 7]);
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
                        PD::drawBitmap(x + 46, y + 4, Images::Numbers_Left_Blk[card.getNumber() - 7]);
                        break;

                    case CardSuit::Diamonds:
                    case CardSuit::Hearts:
                        PD::drawBitmap(x + 46, y + 4, Images::Numbers_Left_Red[card.getNumber() - 7]);
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

void Game::renderGame(bool pause) {

    PD::fillScreen(this->gameStatus.getPlayerView() == 0 ? 3 : 1);



    // Highlight players card?
    
    bool highlightCard = false;

    switch (this->gameState) {

        case GameState::Game_DealerExtraCard:
            if (this->isHuman(this->gameStatus.getDealer() % 4)) { 
                highlightCard = true; 
            }
            break;

        case GameState::Game_LeadCard ... GameState::Game_Follow_03:
            if (this->isHuman(this->gameStatus.getCurrentPlayer())) { 
                highlightCard = true; 
            }
            break;

        default: break;

    }



    // Render Hands ---------------------------------------------------------------------------------------

    // Player 0

    uint8_t position_00 = 0;

    if (this->cookie->getNumberOfPlayers() > 1) {

        if (this->gameStatus.getPlayerView() != 0) {

            position_00 = this->cookie->getPlayer2Pos();

        }

    }

    uint8_t position_01 = (position_00 + 1) % 4;
    uint8_t position_02 = (position_00 + 2) % 4;
    uint8_t position_03 = (position_00 + 3) % 4;

    uint8_t x0 = 40 + ((this->hands[position_00].getCardsInHand() - 1) * 16);
    uint8_t y1 = 40 + ((this->hands[position_01].getCardsInHand() - 1) * 16);
    uint8_t x2 = 40 + ((this->hands[position_02].getCardsInHand() - 1) * 16);
    uint8_t y3 = 40 + ((this->hands[position_03].getCardsInHand() - 1) * 16);

    switch (this->gameState) {

        case GameState::Game_NewHand_00 ... GameState::Game_EndOfTrick:

            for (uint8_t i = 0; i < this->hands[position_00].getCardsInHand(); i++) {

                switch (this->gameState) {

                    case GameState::Game_Follow_01 ... GameState::Game_Follow_03:

                        if (this->isHuman(this->gameStatus.getCurrentPlayer()) && this->counter == 0) {

                            CardSuit suitLed = this->gameStatus.getSuitLed();
                            uint8_t canPlay = !this->cookie->getHighlightPlayable() ? true : this->gameStatus.getFirstPlayer() != position_00 && !(this->hands[position_00].getCard(i).getSuit(this->gameStatus.getTrumps()) != suitLed && this->hands[position_00].hasSuit(suitLed, this->gameStatus.getTrumps()));
                            this->renderCard(Orientation::Bottom, this->hands[position_00].getCard(i), (110 - (x0 / 2)) + (i * 16), 151, this->bidCursor == i && highlightCard, this->bidCursor == i && highlightCard, false, this->cookie->getHighlightPlayable(), canPlay);

                            // printf("Render1 card: %i, highlightCard %i, this->cookie->getHighlightPlayable() && this->bidCursor == i && highlightCard %i, %i %i\n", i, highlightCard, this->cookie->getHighlightPlayable() && this->bidCursor == i && highlightCard, this->cookie->getHighlightPlayable(), canPlay);
                        }
                        else {

                            // printf("Render2 card: %i, %i \n", i, this->cookie->getHighlightPlayable());
                            this->renderCard(Orientation::Bottom, this->hands[position_00].getCard(i), (110 - (x0 / 2)) + (i * 16), 151, false, false, false, false, false);
                        }
                        break;
                    
                    default: 
                        this->renderCard(Orientation::Bottom, this->hands[position_00].getCard(i), (110 - (x0 / 2)) + (i * 16), 151, this->bidCursor == i && highlightCard, this->bidCursor == i && highlightCard, false, false);
                        // printf("Render3 card: %i, highlightCard %i, 0 1\n",i, highlightCard);
                        break;

                }


            }

            if (this->gameStatus.getDealer() == position_00) { PD::drawBitmap(110 + (x0 / 2) + 1, 165, Images::Dealer_Bot); }


            // Player 1

            if (this->isPlayingThisHand(position_01)) {

                for (uint8_t i = 0; i < this->hands[position_01].getCardsInHand(); i++) {

                    this->renderCard(Orientation::Left, this->hands[position_01].getCard(i), -33, (88 - (y1 / 2)) + (i * 16), false, false, this->cookie->getShowHands());

                }

                if (this->gameStatus.getDealer() == position_01) { PD::drawBitmap(2, (88 + (y1 / 2)) + 1, Images::Dealer_Left); }

            }


            // Player 2

            if (this->isPlayingThisHand(position_02)) {

                for (uint8_t i = 0; i < this->hands[position_02].getCardsInHand(); i++) {

                    this->renderCard(Orientation::Top, this->hands[position_02].getCard(i), (70 + (x2 / 2)) - (i * 16), -34, false, false, this->cookie->getShowHands());

                }

                if (this->gameStatus.getDealer() == position_02) { PD::drawBitmap(110 - (x2 / 2) - 11, 2, Images::Dealer_Top); }

            }


            // Player 3

            if (this->isPlayingThisHand(position_03)) {

                for (uint8_t i = 0; i < this->hands[position_03].getCardsInHand(); i++) {

                    this->renderCard(Orientation::Right, this->hands[position_03].getCard(i), 194, (48 + (y3 / 2)) - (i * 16), false, false, this->cookie->getShowHands());

                }

                if (this->gameStatus.getDealer() == position_03) { PD::drawBitmap(209, (88 - (y3 / 2)) - 11, Images::Dealer_Right); }

            }


            // Display trick count ..

            switch (this->gameState) {

                case GameState::Game_StartPlay ... GameState::Game_EndOfHand:
                    PD::drawBitmap(110 + (x0 / 2) + 1, 165 - (this->gameStatus.getDealer() == position_00 ? 10 : 0), Images::Tricks_Bot[this->gameStatus.getTricks(position_00)]); 
                    PD::drawBitmap(2 + (this->gameStatus.getDealer() == position_01 ? 10 : 0), (88 + (y1 / 2)) + 1, Images::Tricks_Left[this->gameStatus.getTricks(position_01)]);
                    PD::drawBitmap(110 - (x2 / 2) - 12, 2 + (this->gameStatus.getDealer() == position_02 ? 10 : 0), Images::Tricks_Top[this->gameStatus.getTricks(position_02)]);
                    PD::drawBitmap(209 - (this->gameStatus.getDealer() == position_03 ? 10 : 0), (88 - (y3 / 2)) - 11, Images::Tricks_Right[this->gameStatus.getTricks(position_03)]);
                    break;

                default: break;

            }

            break;

        default: break;

    }


    // Dealer card 

    if (!pause) {

        if (this->dealerCard.getCardIndex() != Cards::NoCard) {

            switch (this->gameState) {

                case GameState::Game_DealerCard ... GameState::Game_Bid_03:
                    this->renderCard(Orientation::Bottom, this->dealerCard, 90, 59, false, false, true, false, false);
                    break;

                case GameState::Game_Open_Bid_00 ... GameState::Game_StartPlay:
                    this->renderCard(Orientation::Bottom, this->dealerCard, 90, 59, false, false, false, false, false);
                    break;

            }
        
        }


        // Render Played Cards -----------------------------------------------------------------------------------

        for (uint8_t i = this->gameStatus.getFirstPlayer(); i < this->gameStatus.getFirstPlayer() + 4; i++) {

            if (i % 4 == position_00) {
                if (this->gameStatus.getCurrentHand(position_00).getNumber() != Cards::NoCard) {
    // printf("1) %i - %i %i %i %i \n", i, position_00, position_01, position_02, position_03);
                    this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(position_00), 95, 80, this->gameStatus.isPlayerWinning(position_00) && this->cookie->getShowWinner(), false, true, false, false);
                }
            }

            if (i % 4 == position_01) {
                if (this->gameStatus.getCurrentHand(position_01).getNumber() != Cards::NoCard) {
    // printf("2) %i - %i %i %i %i \n", i, position_00, position_01, position_02, position_03);
                    this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(position_01), 70, 65, this->gameStatus.isPlayerWinning(position_01) && this->cookie->getShowWinner(), false, true, false, false);//this->cookie->getShowHands()), false, false;
                }
            }

            if (i % 4 == position_02) {
                if (this->gameStatus.getCurrentHand(position_02).getNumber() != Cards::NoCard) {
    // printf("3) %i - %i %i %i %i \n", i, position_00, position_01, position_02, position_03);
                    this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(position_02), 85, 40, this->gameStatus.isPlayerWinning(position_02) && this->cookie->getShowWinner(), false, true, false, false);//this->cookie->getShowHands(), false, false);
                }
            }

            if (i % 4 == position_03) {
                if (this->gameStatus.getCurrentHand(position_03).getNumber() != Cards::NoCard) {
    // printf("4) %i - %i %i %i %i \n", i, position_00, position_01, position_02, position_03);
                    this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(position_03), 110, 55, this->gameStatus.isPlayerWinning(position_03) && this->cookie->getShowWinner(), false, true, false, false);//this->cookie->getShowHands(), false, false);
                }
            }

        }


        // Bid?

        switch (this->gameState) {

            case GameState::Game_Bid_00:
            case GameState::Game_Bid_01:
            case GameState::Game_Bid_02:
            case GameState::Game_Bid_03:
                {
                    uint8_t offset = (static_cast<uint8_t>(this->gameState) - static_cast<uint8_t>(GameState::Game_Bid_00) + 1) % 4;
                    this->renderBids(position_00, position_01, position_02, position_03);
                    if (this->isHuman((this->gameStatus.getDealer() + offset) % 4)) { 

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
                    this->renderBids(position_00, position_01, position_02, position_03);
                    if (this->isHuman((this->gameStatus.getDealer() + offset) % 4)) { 
                        this->renderPlayerSecondBid();
                    }

                }
                break;

            case GameState::Game_DealerExtraCard:
                this->renderFinalBid(position_00, position_01, position_02, position_03);
                this->renderSoreboard(Constants::AllWinners, Constants::AllWinners, true, true);
                this->renderTrumps(this->gameStatus.getTrumps());
                if (this->isHuman(this->gameStatus.getDealer() % 4)) { 
                    this->renderDiscardACard(); 
                }
                break;

            case GameState::Game_LeadCard ... GameState::Game_Follow_03:
                this->renderFinalBid(position_00, position_01, position_02, position_03);
                this->renderSoreboard(Constants::AllWinners, Constants::AllWinners, true, true);
                this->renderTrumps(this->gameStatus.getTrumps());
                if (this->isHuman(this->gameStatus.getCurrentPlayer())) { 
                    this->renderPlayACard(); 
                }
                break;

            case GameState::Game_EndOfTrick:
                {
                    uint8_t winner = this->gameStatus.whoWon();
                    this->renderFinalBid(position_00, position_01, position_02, position_03);
                    this->renderSoreboard(winner, Constants::AllWinners, PC::frameCount % 32 < 16, true);
                    this->renderTrumps(this->gameStatus.getTrumps());
                    this->renderTrickOver(position_00, position_01, position_02, position_03, winner);
                    this->counter = 1;
                }
                break;

            case GameState::Game_EndOfHand:
                {
                    uint8_t pointsWinner = 0;
                    uint8_t trickWinner = this->gameStatus.whoWon();

                    if (this->bidWinner() == 0 || this->bidWinner() == 2) {

                        switch (this->gameStatus.getTricks0and2()) {

                            case 0 ... 2:
                                pointsWinner = 1;
                                break;

                            default:
                                pointsWinner = 0;
                                break;

                        }                

                    }

                    if (this->bidWinner() == 1 || this->bidWinner() == 3) {

                        switch (this->gameStatus.getTricks1and3()) {

                            case 0 ... 2:
                                pointsWinner = 0;
                                break;

                            default:
                                pointsWinner = 1;
                                break;

                        }                

                    }

                    this->renderSoreboard(trickWinner, pointsWinner, PC::frameCount % 32 < 16, PC::frameCount % 32 < 16);
                    this->renderTrumps(this->gameStatus.getTrumps());
                    this->renderHandOver(pointsWinner);
                }
                break;

        }

    }


    PD::setCursor(200, 160);
    PD::print(static_cast<uint16_t>(this->gameState));

}

void Game::renderSoreboard(uint8_t tricksWinner, uint8_t pointsWinner, bool showTrick, bool showHand) {

    // Score board ..

    PD::drawBitmap(166, 0, Images::Scoreboard);
    if (tricksWinner == Constants::AllWinners || ((tricksWinner == 0 || tricksWinner == 2) && showTrick) || tricksWinner == 1 || tricksWinner == 3) PD::drawBitmap(195, 1, Images::Tricks_Bot[this->gameStatus.getTricks0and2()]);
    if (pointsWinner == Constants::AllWinners || ((pointsWinner == 0 || pointsWinner == 2) && showHand)  || pointsWinner == 1 || pointsWinner == 3) PD::drawBitmap(206, 1, Images::Hands_Bot[this->gameStatus.getPoints0and2()]);
    if (tricksWinner == Constants::AllWinners || ((tricksWinner == 1 || tricksWinner == 3) && showTrick) || tricksWinner == 0 || tricksWinner == 2) PD::drawBitmap(195, 11, Images::Tricks_Bot[this->gameStatus.getTricks1and3()]);
    if (pointsWinner == Constants::AllWinners || ((pointsWinner == 1 || pointsWinner == 3) && showHand)  || pointsWinner == 0 || pointsWinner == 2) PD::drawBitmap(206, 11, Images::Hands_Bot[this->gameStatus.getPoints1and3()]);

}

void Game::renderBids(uint8_t position_00, uint8_t position_01, uint8_t position_02, uint8_t position_03) {

    if (this->hands[position_00].showCallStatus()) {
        if (this->hands[position_00].getCallStatus() == CallStatus::Pass)                                              { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_Pass); }
        if (this->hands[position_00].getCallStatus() == CallStatus::FirstRound && !this->gameStatus.getPlayAlone())    { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_TakeIt); }
        if (this->hands[position_00].getCallStatus() == CallStatus::FirstRound &&  this->gameStatus.getPlayAlone())    { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_Alone); }
        if (this->hands[position_00].getCallStatus() == CallStatus::SecondRound && !this->gameStatus.getPlayAlone())   { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_Suits_Team[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
        if (this->hands[position_00].getCallStatus() == CallStatus::SecondRound && this->gameStatus.getPlayAlone())    { PD::drawBitmap(88, 120, Images::Empty_Bottom); PD::drawBitmap(91, 124, Images::Text_Suits_Alone[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
    }

    if (this->hands[position_01].showCallStatus()) {
        if (this->hands[position_01].getCallStatus() == CallStatus::Pass)                                              { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_Pass); }
        if (this->hands[position_01].getCallStatus() == CallStatus::FirstRound && !this->gameStatus.getPlayAlone())    { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_TakeIt); }
        if (this->hands[position_01].getCallStatus() == CallStatus::FirstRound &&  this->gameStatus.getPlayAlone())    { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_Alone); }
        if (this->hands[position_01].getCallStatus() == CallStatus::SecondRound && !this->gameStatus.getPlayAlone())   { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_Suits_Team[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
        if (this->hands[position_01].getCallStatus() == CallStatus::SecondRound && this->gameStatus.getPlayAlone())    { PD::drawBitmap(20, 72, Images::Empty_Left); PD::drawBitmap(30, 76, Images::Text_Suits_Alone[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
    }

    if (this->hands[position_02].showCallStatus()) {
        if (this->hands[position_02].getCallStatus() == CallStatus::Pass)                                              { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_Pass); }
        if (this->hands[position_02].getCallStatus() == CallStatus::FirstRound && !this->gameStatus.getPlayAlone())    { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_TakeIt); }
        if (this->hands[position_02].getCallStatus() == CallStatus::FirstRound &&  this->gameStatus.getPlayAlone())    { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_Alone); }
        if (this->hands[position_02].getCallStatus() == CallStatus::SecondRound && !this->gameStatus.getPlayAlone())   { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_Suits_Team[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
        if (this->hands[position_02].getCallStatus() == CallStatus::SecondRound && this->gameStatus.getPlayAlone())    { PD::drawBitmap(88, 21, Images::Empty_Top); PD::drawBitmap(91, 31, Images::Text_Suits_Alone[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
    }

    if (this->hands[position_03].showCallStatus()) {
        if (this->hands[position_03].getCallStatus() == CallStatus::Pass)                                              { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_Pass); }
        if (this->hands[position_03].getCallStatus() == CallStatus::FirstRound && !this->gameStatus.getPlayAlone())    { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_TakeIt); }
        if (this->hands[position_03].getCallStatus() == CallStatus::FirstRound &&  this->gameStatus.getPlayAlone())    { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_Alone); }
        if (this->hands[position_03].getCallStatus() == CallStatus::SecondRound && !this->gameStatus.getPlayAlone())   { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_Suits_Team[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
        if (this->hands[position_03].getCallStatus() == CallStatus::SecondRound && this->gameStatus.getPlayAlone())    { PD::drawBitmap(140, 72, Images::Empty_Right); PD::drawBitmap(144, 76, Images::Text_Suits_Alone[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
    }

}

void Game::renderFinalBid(uint8_t position_00, uint8_t position_01, uint8_t position_02, uint8_t position_03) {

    if (this->hands[position_00].isBidWinner()) { 
        
        if (this->gameStatus.getPlayAlone()) {
            PD::drawBitmap(90, Constants::Dialogue_00_Y, Images::Banner_Alone_Bot);
            PD::drawBitmap(94, Constants::Dialogue_00_Y + 1, Images::Suits_Bot[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }
        else {
            PD::drawBitmap(90, Constants::Dialogue_00_Y, Images::Banner_Team_Bot);
            PD::drawBitmap(94, Constants::Dialogue_00_Y + 1, Images::Suits_Bot[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }

    }

    if (this->hands[position_01].isBidWinner()) { 
        
        if (this->gameStatus.getPlayAlone()) {
            PD::drawBitmap(31, 68, Images::Banner_Alone_Left);
            PD::drawBitmap(32, 73, Images::Suits_Left[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }
        else {
            PD::drawBitmap(31, 68, Images::Banner_Team_Left);
            PD::drawBitmap(32, 73, Images::Suits_Left[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }

    }

    if (this->hands[position_02].isBidWinner()) { 
        
        if (this->gameStatus.getPlayAlone()) {
            PD::drawBitmap(90, 27, Images::Banner_Alone_Top);
            PD::drawBitmap(120, 28, Images::Suits_Top[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }
        else {
            PD::drawBitmap(90, 27, Images::Banner_Team_Top);
            PD::drawBitmap(120, 28, Images::Suits_Top[static_cast<uint8_t>(this->gameStatus.getTrumps())]);
        }
    
    }

    if (this->hands[position_03].isBidWinner()) {
        
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

    if (this->cookie->getStickIt() && (this->gameState == GameState::Game_Open_Bid_03))    PD::drawBitmap(54,   92, Images::Dialogue_Pass_Disabled);

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

void Game::renderTrickOver(uint8_t position_00, uint8_t position_01, uint8_t position_02, uint8_t position_03, uint8_t winner) {

    if ((this->gameStatus.getTrumps() != this->gameStatus.getSuitLed()) &&
        (this->gameStatus.getTrumps() == this->gameStatus.getCurrentHand(this->gameStatus.whoWon()).getSuit(this->gameStatus.getTrumps()))) {

        if (this->gameStatus.isPlayerWinning((this->gameStatus.whoWon() + 2) % 4, this->gameStatus.whoWon())) {

            text = Images::Text_Sorry;
            if (this->counter == 0) this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::Sorry) + this->gameStatus.whoWon())); 

        }
        else {
    
            text = Images::Text_Trumped;
            if (this->counter == 0) this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::Trumped) + this->gameStatus.whoWon())); 

        }

    }
    else {

        if (this->text == nullptr) {

            switch (random(0, 3)) {

                case 0:
                    text = Images::Text_Mine;
                    if (this->counter == 0) this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::Mine) + this->gameStatus.whoWon())); 
                    break;

                case 1:
                    text = Images::Text_Winner;
                    if (this->counter == 0) this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::Winner) + this->gameStatus.whoWon())); 
                    break;

                case 2:
                    text = Images::Text_WooHoo;
                    if (this->counter == 0) this->playSpeech(static_cast<Speech>(static_cast<uint8_t>(Speech::WooHoo) + this->gameStatus.whoWon())); 
                    break;

            }

        }

    }


    if (this->gameStatus.whoWon() == position_00) {

        PD::drawBitmap(88, 120, Images::Empty_Bottom); 
        PD::drawBitmap(91, 124, this->text); 
    
    }

    if (this->gameStatus.whoWon() == position_01) {

        PD::drawBitmap(20, 85, Images::Empty_Left); 
        PD::drawBitmap(30, 89, this->text); 

    }

    if (this->gameStatus.whoWon() == position_02) {

        PD::drawBitmap(96, 20, Images::Empty_Top); 
        PD::drawBitmap(99, 31, this->text); 
            
    }

    if (this->gameStatus.whoWon() == position_03) {

        PD::drawBitmap(140, 72, Images::Empty_Right); 
        PD::drawBitmap(144, 76, this->text); 

    }

}

void Game::renderHandOver(uint8_t winner) {

    if (this->bidWinner() == 0 || this->bidWinner() == 2) {

        switch (this->gameStatus.getTricks0and2()) {

            case 0 ... 2:
                PD::drawBitmap(Constants::EOGText_X, Constants::EOGText_Y, Images::Euchre);
                PD::drawBitmap(49, Constants::Dialogue_00_Y + 6, Images::TeamBeta);
                PD::drawBitmap(126, Constants::Dialogue_00_Y + 8, Images::EOG_02);

                if (this->eog < 44) {
                    uint8_t index = (this->eog / 4 > 4 ? 4 : this->eog / 4);
                    PD::drawBitmap(Constants::EOGPoints_X + Images::MinusTwo_CentreX - Images::MinusTwo_OffsetsX[index], 
                                   Constants::EOGPoints_Y + Images::MinusTwo_CentreY - Images::MinusTwo_OffsetsY[index], 
                                   Images::MinusTwo[index]);
                }

                if (this->eog == 0) {
                    this->playSpeech(Speech::TeamBetaPlus2);
                }

                break;

            case 3 ... 4:
                PD::drawBitmap(47, Constants::Dialogue_00_Y + 6, Images::TeamAlpha);
                PD::drawBitmap(128, Constants::Dialogue_00_Y + 8, Images::EOG_01);

                if (this->eog < 44) {
                    uint8_t index = (this->eog / 4 > 4 ? 4 : this->eog / 4);
                    PD::drawBitmap(Constants::EOGPoints_X + Images::PlusOne_CentreX - Images::PlusOne_OffsetsX[index], 
                                   Constants::EOGPoints_Y + Images::PlusOne_CentreY - Images::PlusOne_OffsetsY[index], 
                                   Images::PlusOne[index]);
                }

                if (this->eog == 0) {
                    this->playSpeech(Speech::TeamAlphaPlus1);
                }

                break;

            case 5:
                if (!this->gameStatus.getPlayAlone()) {

                    PD::drawBitmap(47, Constants::Dialogue_00_Y + 6, Images::TeamAlpha);
                    PD::drawBitmap(128, Constants::Dialogue_00_Y + 8, Images::EOG_02);

                    if (this->eog < 44) {
                        uint8_t index = (this->eog / 4 > 4 ? 4 : this->eog / 4);
                        PD::drawBitmap(Constants::EOGPoints_X + Images::PlusTwo_CentreX - Images::PlusTwo_OffsetsX[index], 
                                       Constants::EOGPoints_Y + Images::PlusTwo_CentreY - Images::PlusTwo_OffsetsY[index], 
                                       Images::PlusTwo[index]);
                    }

                    if (this->eog == 0) {
                        this->playSpeech(Speech::TeamAlphaPlus2);
                    }

                }
                else {

                    PD::drawBitmap(45, 53, Images::March);
                    PD::drawBitmap(47, Constants::Dialogue_00_Y + 6, Images::TeamAlpha);
                    PD::drawBitmap(128, Constants::Dialogue_00_Y + 8, Images::EOG_04);

                    if (this->eog < 44) {
                        uint8_t index = (this->eog / 4 > 4 ? 4 : this->eog / 4);
                        PD::drawBitmap(Constants::EOGPoints_X + Images::PlusFour_CentreX - Images::PlusFour_OffsetsX[index], 
                                       Constants::EOGPoints_Y + Images::PlusFour_CentreY - Images::PlusFour_OffsetsY[index], 
                                       Images::PlusFour[index]);
                    }

                    if (this->eog == 0) {
                        this->playSpeech(Speech::TeamAlphaPlus4);
                    }

                }
                break;

        }                

    }

    else if (this->bidWinner() == 1 || this->bidWinner() == 3) {

        switch (this->gameStatus.getTricks1and3()) {

            case 0 ... 2:
                PD::drawBitmap(Constants::EOGText_X, Constants::EOGText_Y, Images::Euchre);
                PD::drawBitmap(47, Constants::Dialogue_00_Y + 4, Images::TeamAlpha);
                PD::drawBitmap(128, Constants::Dialogue_00_Y + 6, Images::EOG_02);

                if (this->eog < 44) {
                    uint8_t index = (this->eog / 4 > 4 ? 4 : this->eog / 4);
                    PD::drawBitmap(Constants::EOGPoints_X + Images::MinusTwo_CentreX - Images::MinusTwo_OffsetsX[index], 
                                   Constants::EOGPoints_Y + Images::MinusTwo_CentreY - Images::MinusTwo_OffsetsY[index], 
                                   Images::MinusTwo[index]);
                }

                if (this->eog == 0) {
                    this->playSpeech(Speech::TeamAlphaPlus2);
                }

                break;

            case 3 ... 4:
                PD::drawBitmap(49, Constants::Dialogue_00_Y + 4, Images::TeamBeta);
                PD::drawBitmap(126, Constants::Dialogue_00_Y + 6, Images::EOG_01);

                if (this->eog < 44) {
                    uint8_t index = (this->eog / 4 > 4 ? 4 : this->eog / 4);
                    PD::drawBitmap(Constants::EOGPoints_X + Images::PlusOne_CentreX - Images::PlusOne_OffsetsX[index], 
                                   Constants::EOGPoints_Y + Images::PlusOne_CentreY - Images::PlusOne_OffsetsY[index], 
                                   Images::PlusOne[index]);
                }

                if (this->eog == 0) {
                    this->playSpeech(Speech::TeamBetaPlus1);
                }

                break;

            case 5:
                if (!this->gameStatus.getPlayAlone()) {
                    
                    PD::setCursor(40, 125);
                    PD::drawBitmap(49, Constants::Dialogue_00_Y + 4, Images::TeamBeta);
                    PD::drawBitmap(126, Constants::Dialogue_00_Y + 6, Images::EOG_02);

                    if (this->eog < 44) {
                        uint8_t index = (this->eog / 4 > 4 ? 4 : this->eog / 4);
                        PD::drawBitmap(Constants::EOGPoints_X + Images::PlusTwo_CentreX - Images::PlusTwo_OffsetsX[index], 
                                       Constants::EOGPoints_Y + Images::PlusTwo_CentreY - Images::PlusTwo_OffsetsY[index], 
                                       Images::PlusTwo[index]);
                    }

                    if (this->eog == 2) {
                        this->playSpeech(Speech::TeamBetaPlus1);
                    }

                }
                else {

                    PD::drawBitmap(45, 53, Images::March);
                    PD::drawBitmap(49, Constants::Dialogue_00_Y + 4, Images::TeamBeta);
                    PD::drawBitmap(126, Constants::Dialogue_00_Y + 6, Images::EOG_04);

                    if (this->eog < 44) {
                        uint8_t index = (this->eog / 4 > 4 ? 4 : this->eog / 4);
                        PD::drawBitmap(Constants::EOGPoints_X + Images::PlusFour_CentreX - Images::PlusFour_OffsetsX[index], 
                                       Constants::EOGPoints_Y + Images::PlusFour_CentreY - Images::PlusFour_OffsetsY[index], 
                                       Images::PlusFour[index]);
                    }

                    if (this->eog == 0) {
                        this->playSpeech(Speech::TeamBetaPlus4);
                    }

                }
                break;

        }                

    }

    if (this->eog < 44) this->eog++;

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