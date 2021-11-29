#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderCard(Orientation orientation, Card card, int16_t x, int16_t y, bool raise, bool showCards, CardMode cardMode) {

    uint8_t highlight_offset = (raise ? 6 : 0);

    switch (orientation) {

        case Orientation::Bottom:
        case Orientation::Top:

            if (showCards) {

                PD::drawBitmap(x, y - highlight_offset, Images::CardFronts[static_cast<uint8_t>(cardMode)]);

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
            else {

                PD::drawBitmap(x, y, Images::Card_Back);

            }

            break;
        
        case Orientation::Left:
        case Orientation::Right:

            if (showCards) {
                    
                PD::drawBitmap(x, y, Images::Card_Front_Rot);
                PD::drawBitmap(x + 35, y + 6, Images::Suits_Left[static_cast<uint8_t>(card.getSuit(CardSuit::None))]);
                PD::drawBitmap(x + 16, y + 28, Images::Suits_Right[static_cast<uint8_t>(card.getSuit(CardSuit::None))], ROT180, NOFLIP);

                switch (card.getSuit(CardSuit::None)) {

                    case CardSuit::Spades:
                    case CardSuit::Clubs:
                        PD::drawBitmap(x + 46, y + 4, Images::Numbers_Left_Blk[card.getNumber() - 7]);
                        PD::drawBitmap(x + 6, y + 26, Images::Numbers_Right_Blk[card.getNumber() - 7], ROT180, NOFLIP);
                        break;

                    case CardSuit::Diamonds:
                    case CardSuit::Hearts:
                        PD::drawBitmap(x + 46, y + 4, Images::Numbers_Left_Red[card.getNumber() - 7]);
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

    uint8_t xOffsetEOG = 0;

    PD::fillScreen(this->gameStatus.getPlayerView() == 0 ? 3 : 1);

    
    // EOG?

    if (this->gameState == GameState::GameOver) {

        if (this->bidWinner() == 0 || this->bidWinner() == 2) {

            switch (this->gameStatus.getTricks0and2()) {

                case 0 ... 2:
                case 5:

                    switch (this->eog) {

                        case 0 ... 59:
                            break;

                        case 60 ... 90:
                            xOffsetEOG = (this->eog - 60) * 3 / 2;
                            break;

                        default:
                            xOffsetEOG = 45;
                            break;
                        
                    }

                    break;

                case 3 ... 4:

                    switch (this->eog) {

                        case 0 ... 30:
                            xOffsetEOG = this->eog * 3 / 2;
                            break;

                        default:
                            xOffsetEOG = 45;
                            break;
                        
                    }

                    break;

            }      

        }
        else {

            switch (this->gameStatus.getTricks1and3()) {

                case 0 ... 2:
                case 5:

                    switch (this->eog) {

                        case 0 ... 59:
                            break;

                        case 60 ... 90:
                            xOffsetEOG = (this->eog - 60) * 3 / 2;
                            break;

                        default:
                            xOffsetEOG = 45;
                            break;
                        
                    }

                    break;

                case 3 ... 4:

                    switch (this->eog) {

                        case 0 ... 30:
                            xOffsetEOG = this->eog * 3 / 2;
                            break;

                        default:
                            xOffsetEOG = 45;
                            break;
                        
                    }

                    break;

            }  

        }

    }



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

    uint8_t positions[4] = { 0, 0, 0, 0 };

    if (this->cookie->getNumberOfPlayers() > 1) {

        if (this->gameStatus.getPlayerView() != 0) {

            positions[0] = this->cookie->getPlayer2Pos();

        }

    }

    positions[1] = (positions[0] + 1) % 4;
    positions[2] = (positions[0] + 2) % 4;
    positions[3] = (positions[0] + 3) % 4;

    uint8_t x0 = 40 + ((this->hands[positions[0]].getCardsInHand() - 1) * 16);
    uint8_t y1 = 40 + ((this->hands[positions[1]].getCardsInHand() - 1) * 16);
    uint8_t x2 = 40 + ((this->hands[positions[2]].getCardsInHand() - 1) * 16);
    uint8_t y3 = 40 + ((this->hands[positions[3]].getCardsInHand() - 1) * 16);

    switch (this->gameState) {

        case GameState::Game_NewHand_00 ... GameState::Game_EndOfTrick:

            for (uint8_t i = 0; i < this->hands[positions[0]].getCardsInHand(); i++) {

                switch (this->gameState) {

                    case GameState::Game_Follow_01 ... GameState::Game_Follow_03:

                        if (this->isHuman(this->gameStatus.getCurrentPlayer()) && this->counter == 0) {

                            CardSuit suitLed = this->gameStatus.getSuitLed();
                            uint8_t canPlay = !this->cookie->getHighlightPlayable() ? true : this->gameStatus.getFirstPlayer() != positions[0] && !(this->hands[positions[0]].getCard(i).getSuit(this->gameStatus.getTrumps()) != suitLed && this->hands[positions[0]].hasSuit(suitLed, this->gameStatus.getTrumps()));
                            this->renderCard(Orientation::Bottom, this->hands[positions[0]].getCard(i), (110 - (x0 / 2)) + (i * 16), 151, this->bidCursor == i && highlightCard, true, !(this->cookie->getHighlightPlayable() && canPlay) ? CardMode::Disabled : CardMode::Normal);
// printf("1\n");
                        }
                        else {
// printf("2\n");

                            this->renderCard(Orientation::Bottom, this->hands[positions[0]].getCard(i), (110 - (x0 / 2)) + (i * 16), 151, false, true, CardMode::Normal);
                        }
                        break;
                    
                    default: 
// printf("3\n");

                        this->renderCard(Orientation::Bottom, this->hands[positions[0]].getCard(i), (110 - (x0 / 2)) + (i * 16), 151, this->bidCursor == i && highlightCard, true, CardMode::Normal);
                        break;

                }


            }

            if (this->gameStatus.getDealer() == positions[0]) { PD::drawBitmap(110 + (x0 / 2) + 1, 165, Images::Dealer_Bot); }


            // Player 1

            if (this->isPlayingThisHand(positions[1])) {

                for (uint8_t i = 0; i < this->hands[positions[1]].getCardsInHand(); i++) {

                    this->renderCard(Orientation::Left, this->hands[positions[1]].getCard(i), -33, (88 - (y1 / 2)) + (i * 16), false, this->cookie->getShowHands(), CardMode::Normal);

                }

                if (this->gameStatus.getDealer() == positions[1]) { PD::drawBitmap(2, (88 + (y1 / 2)) + 1, Images::Dealer_Left); }

            }


            // Player 2

            if (this->isPlayingThisHand(positions[2])) {

                for (uint8_t i = 0; i < this->hands[positions[2]].getCardsInHand(); i++) {

                    this->renderCard(Orientation::Top, this->hands[positions[2]].getCard(i), (70 + (x2 / 2)) - (i * 16), -34, false, this->cookie->getShowHands(), CardMode::Normal);

                }

                if (this->gameStatus.getDealer() == positions[2]) { PD::drawBitmap(110 - (x2 / 2) - 11, 2, Images::Dealer_Top); }

            }


            // Player 3

            if (this->isPlayingThisHand(positions[3])) {

                for (uint8_t i = 0; i < this->hands[positions[3]].getCardsInHand(); i++) {

                    this->renderCard(Orientation::Right, this->hands[positions[3]].getCard(i), 194, (48 + (y3 / 2)) - (i * 16), false, this->cookie->getShowHands(), CardMode::Normal);

                }

                if (this->gameStatus.getDealer() == positions[3]) { PD::drawBitmap(209, (88 - (y3 / 2)) - 11, Images::Dealer_Right); }

            }


            // Display trick count ..

            switch (this->gameState) {

                case GameState::Game_StartPlay ... GameState::Game_EndOfHand:
                    PD::drawBitmap(110 + (x0 / 2) + 1, 165 - (this->gameStatus.getDealer() == positions[0] ? 10 : 0), Images::Tricks_Bot[this->gameStatus.getTricks(positions[0])]); 
                    PD::drawBitmap(2 + (this->gameStatus.getDealer() == positions[1] ? 10 : 0), (88 + (y1 / 2)) + 1, Images::Tricks_Left[this->gameStatus.getTricks(positions[1])]);
                    PD::drawBitmap(110 - (x2 / 2) - 12, 2 + (this->gameStatus.getDealer() == positions[2] ? 10 : 0), Images::Tricks_Top[this->gameStatus.getTricks(positions[2])]);
                    PD::drawBitmap(209 - (this->gameStatus.getDealer() == positions[3] ? 11 : 0), (88 - (y3 / 2)) - 11, Images::Tricks_Right[this->gameStatus.getTricks(positions[3])]);
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
                    this->renderCard(Orientation::Bottom, this->dealerCard, 90, 59, false, true, CardMode::Normal);
                    break;

                case GameState::Game_Open_Bid_00 ... GameState::Game_Open_Bid_03:
                    this->renderCard(Orientation::Left, this->dealerCard, 81, 44, false, false, CardMode::Normal);
                    break;

            }
        
        }


        // Render Played Cards -----------------------------------------------------------------------------------

        {
            const uint8_t playedX[] = { 95, 70, 85, 110 };
            const uint8_t playedY[] = { 80, 65, 40, 55 };

            for (uint8_t i = this->gameStatus.getFirstPlayer(); i < this->gameStatus.getFirstPlayer() + 4; i++) {

                for (uint8_t j = 0; j < 4; j++) {

                    if (this->gameState != GameState::GameOver && i % 4 == positions[j]) {
                        this->renderPlayedCard(playedX[j] + xOffsetEOG, playedY[j], positions[j]);
                    }

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
                    this->renderBids(positions);
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
                    uint8_t offset = (static_cast<uint8_t>(this->gameState) - static_cast<uint8_t>(GameState::Game_Open_Bid_00) + 1) % 4;
                    this->renderBids(positions);
                    if (this->isHuman((this->gameStatus.getDealer() + offset) % 4)) { 
                        this->renderPlayerSecondBid();
                    }

                }
                break;

            case GameState::Game_DealerExtraCard:
                this->renderSoreboard(Constants::AllWinners, Constants::AllWinners, true, true);
                this->renderTrumps(this->gameStatus.getTrumps());
                if (this->isHuman(this->gameStatus.getDealer() % 4)) { 
                    this->renderDiscardACard(); 
                }
                else {
                    this->renderFinalBid(positions);
                }
                break;

            case GameState::Game_LeadCard ... GameState::Game_Follow_03:
                this->renderSoreboard(Constants::AllWinners, Constants::AllWinners, true, true);
                this->renderTrumps(this->gameStatus.getTrumps());
                if (this->isHuman(this->gameStatus.getCurrentPlayer())) { 
                    this->renderPlayACard(); 
                }
                else {
                    this->renderFinalBid(positions);
                }
                break;

            case GameState::Game_EndOfTrick:
                {
                    uint8_t winner = this->gameStatus.whoWon();
                    this->renderFinalBid(positions);
                    this->renderSoreboard(winner, Constants::AllWinners, PC::frameCount % 32 < 16, true);
                    this->renderTrumps(this->gameStatus.getTrumps());
                    this->renderTrickOver(positions, winner);
                    this->counter = 1;
                }
                break;

            case GameState::Game_EndOfHand:
            case GameState::GameOver:
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

                    if (this->gameState == GameState::Game_EndOfHand) {
                        this->renderHandOver(pointsWinner);
                    }
                    else {
                        this->renderGameOver(pointsWinner);
                    }

                }
                break;

        }

    }


    #ifdef DEBUG_STATE
        PD::setCursor(200, 160);
        PD::print(static_cast<uint16_t>(this->gameState));
    #endif

}

void Game::renderPlayedCard(uint8_t x, uint8_t y, uint8_t position) {

    if (this->gameStatus.getCurrentHand(position).getNumber() != Cards::NoCard) {
        this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(position), x, y, false, true, !(this->gameStatus.isPlayerWinning(position) && this->cookie->getShowWinner()) ? CardMode::Normal : CardMode::Highlighted);
    }

}

void Game::renderSoreboard(uint8_t tricksWinner, uint8_t pointsWinner, bool showTrick, bool showHand) {

    // Score board ..

    PD::drawBitmap(166, 0, Images::Scoreboard);
    if (tricksWinner == Constants::AllWinners || ((tricksWinner == 0 || tricksWinner == 2) && showTrick) || tricksWinner == 1 || tricksWinner == 3) PD::drawBitmap(195, 1, Images::Tricks_Bot[this->gameStatus.getTricks0and2()]);
    if (pointsWinner == Constants::AllWinners || ((pointsWinner == 0 || pointsWinner == 2) && showHand)  || pointsWinner == 1 || pointsWinner == 3) PD::drawBitmap(206, 1, Images::Hands_Bot[this->gameStatus.getPoints0and2()]);
    if (tricksWinner == Constants::AllWinners || ((tricksWinner == 1 || tricksWinner == 3) && showTrick) || tricksWinner == 0 || tricksWinner == 2) PD::drawBitmap(195, 11, Images::Tricks_Bot[this->gameStatus.getTricks1and3()]);
    if (pointsWinner == Constants::AllWinners || ((pointsWinner == 1 || pointsWinner == 3) && showHand)  || pointsWinner == 0 || pointsWinner == 2) PD::drawBitmap(206, 11, Images::Hands_Bot[this->gameStatus.getPoints1and3()]);

}

void Game::renderBids(uint8_t positions[4]) {

    const uint8_t renderBidsX[] = { 88, 20, 88, 140 };
    const uint8_t renderBidsY[] = { 120, 72, 21, 72 };

    const uint8_t renderBids_TextX[] = { 91, 30, 91, 144 };
    const uint8_t renderBids_TextY[] = { 124, 76, 31, 76 };
    
    for (uint8_t i = 0; i < 4; i++) {

        if (this->hands[positions[i]].showCallStatus()) {
            if (this->hands[positions[i]].getCallStatus() == CallStatus::Pass)                                              { PD::drawBitmap(renderBidsX[i], renderBidsY[i], Images::Empty_Dialogue[i]); PD::drawBitmap(renderBids_TextX[i], renderBids_TextY[i], Images::Text_Pass); }
            if (this->hands[positions[i]].getCallStatus() == CallStatus::FirstRound && !this->gameStatus.getPlayAlone())    { PD::drawBitmap(renderBidsX[i], renderBidsY[i], Images::Empty_Dialogue[i]); PD::drawBitmap(renderBids_TextX[i], renderBids_TextY[i], Images::Text_TakeIt); }
            if (this->hands[positions[i]].getCallStatus() == CallStatus::FirstRound &&  this->gameStatus.getPlayAlone())    { PD::drawBitmap(renderBidsX[i], renderBidsY[i], Images::Empty_Dialogue[i]); PD::drawBitmap(renderBids_TextX[i], renderBids_TextY[i], Images::Text_Alone); }
            if (this->hands[positions[i]].getCallStatus() == CallStatus::SecondRound && !this->gameStatus.getPlayAlone())   { PD::drawBitmap(renderBidsX[i], renderBidsY[i], Images::Empty_Dialogue[i]); PD::drawBitmap(renderBids_TextX[i], renderBids_TextY[i], Images::Text_Suits_Team[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
            if (this->hands[positions[i]].getCallStatus() == CallStatus::SecondRound && this->gameStatus.getPlayAlone())    { PD::drawBitmap(renderBidsX[i], renderBidsY[i], Images::Empty_Dialogue[i]); PD::drawBitmap(renderBids_TextX[i], renderBids_TextY[i], Images::Text_Suits_Alone[static_cast<uint8_t>(this->gameStatus.getTrumps())]); }
        }

    }

}

void Game::renderFinalBid(uint8_t positions[4]) {
    

    uint8_t render_BannerX[4] = { 90, 31, 90, 180 };
    uint8_t render_BannerY[4] = { 139, 68, 27, 68 };
    uint8_t render_SuitX[4] = { 94, 32, 120, 180 };
    uint8_t render_SuitY[4] = { 140, 73, 28, 98 };
    
    for (uint8_t i = 0; i < 4; i++) {

        if (this->hands[positions[i]].isBidWinner()) { 
            
            if (this->gameStatus.getPlayAlone()) {
                PD::drawBitmap(render_BannerX[i], render_BannerY[i], Images::Banner_Alone[i]);
                PD::drawBitmap(render_SuitX[i], render_SuitY[i], Images::Suits_All[(i * 4) + static_cast<uint8_t>(this->gameStatus.getTrumps())]);
            }
            else {
                PD::drawBitmap(render_BannerX[i], render_BannerY[i], Images::Banner_Team[i]);
                PD::drawBitmap(render_SuitX[i], render_SuitY[i], Images::Suits_All[(i * 4) + static_cast<uint8_t>(this->gameStatus.getTrumps())]);
            }

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

    PD::drawBitmap(61, 96, Images::Dialogue_Large_Background);

    if (this->cookie->getStickIt() && (this->gameState == GameState::Game_Open_Bid_03))    PD::drawBitmap(54,   95, Images::Dialogue_Pass_Disabled);

    if (this->dialogCursor == 0)    PD::drawBitmap(54,   95, Images::Dialogue_Pass);
    if (this->dialogCursor == 1)    PD::drawBitmap(94,   95, Images::Dialogue_Go_Spades);
    if (this->dialogCursor == 2)    PD::drawBitmap(130,  95, Images::Dialogue_Alone_Spades);
    if (this->dialogCursor == 3)    PD::drawBitmap(94,  106, Images::Dialogue_Go_Clubs);
    if (this->dialogCursor == 4)    PD::drawBitmap(130, 106, Images::Dialogue_Alone_Clubs);
    if (this->dialogCursor == 5)    PD::drawBitmap(94,  117, Images::Dialogue_Go_Diamonds);
    if (this->dialogCursor == 6)    PD::drawBitmap(130, 117, Images::Dialogue_Alone_Diamonds);
    if (this->dialogCursor == 7)    PD::drawBitmap(94,  128, Images::Dialogue_Go_Hearts);
    if (this->dialogCursor == 8)    PD::drawBitmap(130, 128, Images::Dialogue_Alone_Hearts);

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

void Game::renderTrickOver(uint8_t positions[4], uint8_t winner) {

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

    {
        const uint8_t dialogue_X[4] = { 88, 20, 96, 140 }; 
        const uint8_t dialogue_Y[4] = { 120, 85, 20, 72 }; 

        const uint8_t text_X[4] = { 91, 30, 99, 144 }; 
        const uint8_t text_Y[4] = { 124, 89,31, 76 }; 

        for (uint8_t i = 0; i < 4; i++) {

            if (this->gameStatus.whoWon() == positions[i]) {

                PD::drawBitmap(dialogue_X[i], dialogue_Y[i], Images::Empty_Dialogue[i]); 
                PD::drawBitmap(text_X[i], text_Y[i], this->text); 
            
            }

        }

    }

}

void Game::renderHandOver(uint8_t winner) {

    if (this->bidWinner() == 0 || this->bidWinner() == 2) {

        switch (this->gameStatus.getTricks0and2()) {

            case 0 ... 2:

                PD::drawBitmap(49, Constants::Dialogue_EOH_Y, Images::TeamBeta);
                PD::drawBitmap(126, Constants::Dialogue_EOH_Y + 2, Images::Points_02);
                PD::drawBitmap(Constants::EOHText_X, Constants::EOHText_Y, Images::Title);

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

                PD::drawBitmap(47, Constants::Dialogue_EOH_Y, Images::TeamAlpha);
                PD::drawBitmap(128, Constants::Dialogue_EOH_Y + 2, Images::Points_01);

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

                PD::drawBitmap(47, Constants::Dialogue_EOH_Y, Images::TeamAlpha);
                PD::drawBitmap(128, Constants::Dialogue_EOH_Y + 2, Images::Points_02);

                if (!this->gameStatus.getPlayAlone()) {

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

                    PD::drawBitmap(47, Constants::Dialogue_EOH_Y, Images::TeamAlpha);
                    PD::drawBitmap(128, Constants::Dialogue_EOH_Y + 2, Images::Points_04);
                    PD::drawBitmap(Constants::EOHText_X, Constants::EOHText_Y, Images::March);

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

                PD::drawBitmap(47, Constants::Dialogue_EOH_Y, Images::TeamAlpha);
                PD::drawBitmap(128, Constants::Dialogue_EOH_Y + 2, Images::Points_02);
                PD::drawBitmap(Constants::EOHText_X, Constants::EOHText_Y, Images::Title);

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

                PD::drawBitmap(49, Constants::Dialogue_EOH_Y, Images::TeamBeta);
                PD::drawBitmap(126, Constants::Dialogue_EOH_Y + 2, Images::Points_01);

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

                    PD::drawBitmap(49, Constants::Dialogue_EOH_Y, Images::TeamBeta);
                    PD::drawBitmap(126, Constants::Dialogue_EOH_Y + 2, Images::Points_02);

                    if (this->eog < 44) {
                        uint8_t index = (this->eog / 4 > 4 ? 4 : this->eog / 4);
                        PD::drawBitmap(Constants::EOGPoints_X + Images::PlusTwo_CentreX - Images::PlusTwo_OffsetsX[index], 
                                       Constants::EOGPoints_Y + Images::PlusTwo_CentreY - Images::PlusTwo_OffsetsY[index], 
                                       Images::PlusTwo[index]);
                    }

                    if (this->eog == 0) {
                        this->playSpeech(Speech::TeamBetaPlus2);
                    }

                }
                else {

                    PD::drawBitmap(49, Constants::Dialogue_EOH_Y, Images::TeamBeta);
                    PD::drawBitmap(126, Constants::Dialogue_EOH_Y + 2, Images::Points_04);
                    PD::drawBitmap(Constants::EOHText_X, Constants::EOHText_Y, Images::March);

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

    if (this->eog < 500) this->eog++;

}


void Game::renderGameOver(uint8_t winner) {

    if (this->bidWinner() == 0 || this->bidWinner() == 2) {

        switch (this->gameStatus.getTricks0and2()) {

            case 0 ... 2:

                this->renderGameOver_Beta();

                if (this->eog == 0) {
                    this->playSpeech(Speech::TeamBetaWins);
                }

                break;

            case 3 ... 4:

                this->renderGameOver_Alpha();

                if (this->eog == 0) {
                    this->playSpeech(Speech::TeamAlphaWins);
                }

                break;

            case 5:

                if (!this->gameStatus.getPlayAlone()) {

                    this->renderGameOver_Alpha();

                    if (this->eog == 0) {
                        this->playSpeech(Speech::TeamAlphaWins);
                    }

                }
                else {

                    this->renderGameOver_Alpha();

                    if (this->eog == 0) {
                        this->playSpeech(Speech::TeamAlphaWins);
                    }

                }
                break;

        }                

    }

    else if (this->bidWinner() == 1 || this->bidWinner() == 3) {

        switch (this->gameStatus.getTricks1and3()) {

            case 0 ... 2:

                this->renderGameOver_Alpha();

                if (this->eog == 0) {
                    this->playSpeech(Speech::TeamAlphaWins);
                }

                break;

            case 3 ... 4:

                this->renderGameOver_Beta();

                if (this->eog == 0) {
                    this->playSpeech(Speech::TeamBetaWins);
                }

                break;

            case 5:

                if (!this->gameStatus.getPlayAlone()) {

                    this->renderGameOver_Beta();

                    if (this->eog == 0) {
                        this->playSpeech(Speech::TeamBetaWins);
                    }

                }
                else {

                    this->renderGameOver_Beta();

                    if (this->eog == 0) {
                        this->playSpeech(Speech::TeamBetaWins);
                    }

                }
                break;

        }                

    }

    if (this->eog < 500) this->eog++;

}

void Game::renderGameOver_Alpha() {

    #ifdef FADE_IN

        uint8_t frame = 0;

        switch (this->eog) {

            case 0:
                frame = 0;
                // this->eog++;
                break;

            case 1 ... 15:
                frame = this->eog;
                // this->eog++;
                break;

            default: 
                frame = 16;
                break;

        }

        if (frame > 0) {

    #endif

            PD::drawBitmap(Constants::EOGText_X1, Constants::EOGText_Y1, Images::EOG_Team);
            PD::drawBitmap(Constants::EOGText_X3, Constants::EOGText_Y3,  Images::EOG_Wins);
            PD::drawBitmap(Constants::EOGText_X21, Constants::EOGText_Y2, Images::EOG_Alpha);

    #ifdef FADE_IN

            if (frame <= 15) {

                for (uint8_t y = Constants::EOGText_Y1; y < Constants::EOGText_Y2 + 50; y = y + 4) {

                    for (uint8_t x = Constants::EOGText_X22; x < Constants::EOGText_X3 + 144; x = x + 4) {

                        PD::drawBitmap(x, y, Images::Dither_Green[15 - frame]);

                    }

                }

            }

        }

    #endif

}

void Game::renderGameOver_Beta() {

    #ifdef FADE_IN

        uint8_t frame = 0;

        switch (this->eog) {

            case 0:
                frame = 0;
                // this->eog++;
                break;

            case 1 ... 15:
                frame = this->eog;
                // this->eog++;
                break;

            default: 
                frame = 16;
                break;

        }

        if (frame > 0) {

    #endif

            PD::drawBitmap(Constants::EOGText_X1, Constants::EOGText_Y1, Images::EOG_Team);
            PD::drawBitmap(Constants::EOGText_X3, Constants::EOGText_Y3,  Images::EOG_Wins);
            PD::drawBitmap(Constants::EOGText_X22, Constants::EOGText_Y2, Images::EOG_Beta);

    #ifdef FADE_IN

            if (frame <= 15) {

                for (uint8_t y = Constants::EOGText_Y1; y < Constants::EOGText_Y2 + 50; y = y + 4) {

                    for (uint8_t x = Constants::EOGText_X22; x < Constants::EOGText_X3 + 144; x = x + 4) {

                        PD::drawBitmap(x, y, Images::Dither_Green[15 - frame]);

                    }

                }

            }

        }

    #endif

}
