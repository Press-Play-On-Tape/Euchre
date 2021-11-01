#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::selection_Init() {

    this->gameState = GameState::Selection;
    this->dialogCursor = this->cookie->getNumberOfPlayers() - 1;
    this->bidCursor = 0;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::selection() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        switch (this->dialogCursor) {

            case 0:
                this->cookie->setNumberOfPlayers(1);
                this->cookie->saveCookie();
                this->gameState = GameState::Game_Init;
                break;

            case 1:
                this->cookie->setNumberOfPlayers(2);
                this->cookie->saveCookie();
                this->gameState = GameState::Game_Init;
                break;

            case 2:
                this->cookie->setPlayer2Pos(2);
                break;

            case 3:
                this->cookie->setPlayer2Pos(1);
                break;

            case 4:
                this->cookie->setPlayer2Pos(3);
                break;

            case 5:
                this->cookie->setStickIt(!this->cookie->getStickIt());
                break;

            case 6:
                this->cookie->setShowWinner(!this->cookie->getShowWinner());
                break;

            case 7:
                this->cookie->setShowHands(!this->cookie->getShowHands());
                break;

        }

    }         

    if (PC::buttons.pressed(BTN_UP)) {

        switch (this->dialogCursor) {

            case 2:
                this->dialogCursor = 1;
                break;

            case 3 ... 4:
                this->dialogCursor = 2;
                break;

            case 5:
                this->dialogCursor = this->bidCursor;
                break;

            case 6 ... 7:
                this->dialogCursor--;
                break;

            default: break;

        }

    }

    if (PC::buttons.pressed(BTN_DOWN)) {

        switch (this->dialogCursor) {

            case 0:
                this->bidCursor = this->dialogCursor;
                this->dialogCursor = 5;
                break;

            case 1:
                // this->bidCursor = this->dialogCursor;
                this->dialogCursor = 2;
                break;

            case 2 ... 4:
                this->bidCursor = this->dialogCursor;
                this->dialogCursor = 5;
                break;

            case 5 ... 6:
                this->dialogCursor++;
                break;

            default: break;

        }

    }

    if (PC::buttons.pressed(BTN_LEFT)) {

        switch (this->dialogCursor) {

            case 1:
                this->dialogCursor = 0;
                this->bidCursor = 0;
                this->cookie->setNumberOfPlayers(1);
                break;

            case 2:
                this->dialogCursor = 3;
                this->bidCursor = 3;
                break;

            case 4:
                this->dialogCursor = 2;
                this->bidCursor = 2;
                break;

            default: break;

        }

    }
    
    if (PC::buttons.pressed(BTN_RIGHT)) {

        switch (this->dialogCursor) {

            case 0:
                this->dialogCursor = 1;
                this->cookie->setNumberOfPlayers(2);
                break;

            case 3:
                this->dialogCursor = 2;
                this->bidCursor = 2;
                break;

            case 2:
                this->dialogCursor = 4;
                this->bidCursor = 4;
                break;

            default: break;

        }

    }
    

    PD::fillScreen(3);

    if (this->dialogCursor == 0)   PD::drawBitmap(10, 10, Images::OnePlayer_Selected);
    if (this->dialogCursor != 0)   PD::drawBitmap(10, 10, Images::OnePlayer);
    if (this->dialogCursor == 1)   PD::drawBitmap(70, 10, Images::TwoPlayer_Selected);
    if (this->dialogCursor != 1)   PD::drawBitmap(70, 10, Images::TwoPlayer);


    if (this->dialogCursor != 5) {  
        PD::drawBitmap(10, 140, this->cookie->getStickIt() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
        PD::drawBitmap(19, 140, Images::StickIt);
    }
    else {
        PD::drawBitmap(10, 140, this->cookie->getStickIt() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
        PD::drawBitmap(19, 140, Images::StickIt_Selected);
    }

    if (this->dialogCursor != 6) {  
        PD::drawBitmap(10, 153, this->cookie->getShowWinner() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
        PD::drawBitmap(19, 153, Images::ShowWinner);
    }
    else {
        PD::drawBitmap(10, 153, this->cookie->getShowWinner() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
        PD::drawBitmap(19, 153, Images::ShowWinner_Selected);
    }

    if (this->dialogCursor != 7) {  
        PD::drawBitmap(10, 166, this->cookie->getShowHands() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
        PD::drawBitmap(19, 166, Images::ShowAll);
    }
    else {
        PD::drawBitmap(10, 166, this->cookie->getShowHands() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
        PD::drawBitmap(19, 166, Images::ShowAll_Selected);
    }

    if (this->cookie->getNumberOfPlayers() == 2) {

        PD::drawBitmap(61, 65, Images::Seat_Left);
        PD::drawBitmap(91, 40, Images::Seat_Top);
        PD::drawBitmap(136, 65, Images::Seat_Right);
        PD::drawBitmap(91, 100, Images::Seat_Bot);

        if (this->dialogCursor == 3) {
            PD::drawBitmap(1, 75, this->cookie->getPlayer2Pos() == 1 ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
            PD::drawBitmap(10, 75, Images::Position1_Selected);
        }
        else {
            PD::drawBitmap(1, 75, this->cookie->getPlayer2Pos() == 1 ? Images::CheckBox_Checked : Images::CheckBox_Empty);
            PD::drawBitmap(10, 75, Images::Position1);
        }

        if (this->dialogCursor == 2) {
            PD::drawBitmap(75, 25, this->cookie->getPlayer2Pos() == 2 ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
            PD::drawBitmap(84, 25, Images::Position2_Selected);
        }
        else {
            PD::drawBitmap(75, 25, this->cookie->getPlayer2Pos() == 2 ? Images::CheckBox_Checked : Images::CheckBox_Empty);
            PD::drawBitmap(84, 25, Images::Position2);
        }

        if (this->dialogCursor == 4) {
            PD::drawBitmap(160, 75, this->cookie->getPlayer2Pos() == 3 ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
            PD::drawBitmap(169, 75, Images::Position3_Selected);
        }
        else {
            PD::drawBitmap(160, 75, this->cookie->getPlayer2Pos() == 3 ? Images::CheckBox_Checked : Images::CheckBox_Empty);
            PD::drawBitmap(169, 75, Images::Position3);
        }

    }
    else {

        PD::drawBitmap(1, 75, this->cookie->getPlayer2Pos() == 1 ? Images::CheckBox_Checked_Disabled : Images::CheckBox_Empty_Disabled);
        PD::drawBitmap(10, 75, Images::Position1_Disabled);
        PD::drawBitmap(75, 25, this->cookie->getPlayer2Pos() == 2 ? Images::CheckBox_Checked_Disabled : Images::CheckBox_Empty_Disabled);
        PD::drawBitmap(84, 25, Images::Position2_Disabled);
        PD::drawBitmap(160, 75, this->cookie->getPlayer2Pos() == 3 ? Images::CheckBox_Checked_Disabled : Images::CheckBox_Empty_Disabled);
        PD::drawBitmap(169, 75, Images::Position3_Disabled);

        PD::drawBitmap(61, 65, Images::Seat_Left_Disabled);
        PD::drawBitmap(91, 40, Images::Seat_Top_Disabled);
        PD::drawBitmap(136, 65, Images::Seat_Right_Disabled);
        PD::drawBitmap(91, 100, Images::Seat_Bot_Disabled);

    }
    
}
