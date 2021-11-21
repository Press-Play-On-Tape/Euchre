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

    if (this->instructionFile.openRO(Constants::instructions[0])) {
        this->instructionFile.read(PD::getBuffer(), 2);
        this->instructionFile.read(PD::getBuffer(), (220 * 176 / 2));
    }

    PD::setColor(0);
    PD::fillRect(32, 0, 186, 176);

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
                this->cookie->setHighlightPlayable(!this->cookie->getHighlightPlayable());
                break;

            case 8:
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

            case 6 ... 8:
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
                this->dialogCursor = 2;
                break;

            case 2 ... 4:
                this->bidCursor = this->dialogCursor;
                this->dialogCursor = 5;
                break;

            case 5 ... 7:
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
        

    // if (this->dialogCursor == 0)   PD::drawBitmap(37, 10, Images::OnePlayer_Selected);
    // if (this->dialogCursor != 0)   PD::drawBitmap(37, 10, Images::OnePlayer);
    // if (this->dialogCursor == 1)   PD::drawBitmap(97, 10, Images::TwoPlayer_Selected);
    // if (this->dialogCursor != 1)   PD::drawBitmap(97, 10, Images::TwoPlayer);


    // if (this->dialogCursor != 5) {  
    //     PD::drawBitmap(37, 127, this->cookie->getStickIt() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
    //     PD::drawBitmap(46, 127, Images::StickIt);
    // }
    // else {
    //     PD::drawBitmap(37, 127, this->cookie->getStickIt() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
    //     PD::drawBitmap(46, 127, Images::StickIt_Selected);
    // }

    // if (this->dialogCursor != 6) {  
    //     PD::drawBitmap(37, 140, this->cookie->getShowWinner() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
    //     PD::drawBitmap(46, 140, Images::ShowWinner);
    // }
    // else {
    //     PD::drawBitmap(37, 140, this->cookie->getShowWinner() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
    //     PD::drawBitmap(46, 140, Images::ShowWinner_Selected);
    // }

    // if (this->dialogCursor != 7) {  
    //     PD::drawBitmap(37, 153, this->cookie->getHighlightPlayable() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
    //     PD::drawBitmap(46, 153, Images::HighlightPlayable);
    // }
    // else {
    //     PD::drawBitmap(37, 153, this->cookie->getHighlightPlayable() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
    //     PD::drawBitmap(46, 153, Images::HighlightPlayable_Selected);
    // }

    // if (this->dialogCursor != 8) {  
    //     PD::drawBitmap(37, 166, this->cookie->getShowHands() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
    //     PD::drawBitmap(46, 166, Images::ShowAll);
    // }
    // else {
    //     PD::drawBitmap(37, 166, this->cookie->getShowHands() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
    //     PD::drawBitmap(46, 166, Images::ShowAll_Selected);
    // }

    // if (this->cookie->getNumberOfPlayers() == 2) {

    //     PD::drawBitmap(77, 65, Images::Seat_Left);
    //     PD::drawBitmap(103, 40, Images::Seat_Top);
    //     PD::drawBitmap(143, 65, Images::Seat_Right);
    //     PD::drawBitmap(103, 100, Images::Seat_Bot);

    //     if (this->dialogCursor == 3) {
    //         PD::drawBitmap(37, 75, this->cookie->getPlayer2Pos() == 1 ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
    //         PD::drawBitmap(46, 75, Images::Position1_Selected);
    //     }
    //     else {
    //         PD::drawBitmap(37, 75, this->cookie->getPlayer2Pos() == 1 ? Images::CheckBox_Checked : Images::CheckBox_Empty);
    //         PD::drawBitmap(46, 75, Images::Position1);
    //     }

    //     if (this->dialogCursor == 2) {
    //         PD::drawBitmap(102, 25, this->cookie->getPlayer2Pos() == 2 ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
    //         PD::drawBitmap(111, 25, Images::Position2_Selected);
    //     }
    //     else {
    //         PD::drawBitmap(101, 25, this->cookie->getPlayer2Pos() == 2 ? Images::CheckBox_Checked : Images::CheckBox_Empty);
    //         PD::drawBitmap(111, 25, Images::Position2);
    //     }

    //     if (this->dialogCursor == 4) {
    //         PD::drawBitmap(168, 75, this->cookie->getPlayer2Pos() == 3 ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
    //         PD::drawBitmap(177, 75, Images::Position3_Selected);
    //     }
    //     else {
    //         PD::drawBitmap(168, 75, this->cookie->getPlayer2Pos() == 3 ? Images::CheckBox_Checked : Images::CheckBox_Empty);
    //         PD::drawBitmap(177, 75, Images::Position3);
    //     }

    // }
    // else {

    //     PD::drawBitmap(37, 75, this->cookie->getPlayer2Pos() == 1 ? Images::CheckBox_Checked_Disabled : Images::CheckBox_Empty_Disabled);
    //     PD::drawBitmap(46, 75, Images::Position1_Disabled);
    //     PD::drawBitmap(102, 25, this->cookie->getPlayer2Pos() == 2 ? Images::CheckBox_Checked_Disabled : Images::CheckBox_Empty_Disabled);
    //     PD::drawBitmap(111, 25, Images::Position2_Disabled);
    //     PD::drawBitmap(168, 75, this->cookie->getPlayer2Pos() == 3 ? Images::CheckBox_Checked_Disabled : Images::CheckBox_Empty_Disabled);
    //     PD::drawBitmap(177, 75, Images::Position3_Disabled);

    //     PD::drawBitmap(77, 65, Images::Seat_Left_Disabled);
    //     PD::drawBitmap(103, 40, Images::Seat_Top_Disabled);
    //     PD::drawBitmap(143, 65, Images::Seat_Right_Disabled);
    //     PD::drawBitmap(103, 100, Images::Seat_Bot_Disabled);

    // }

    

    if (this->dialogCursor == 0)   PD::drawBitmap(41, 10, Images::OnePlayer_Selected);
    if (this->dialogCursor != 0)   PD::drawBitmap(41, 10, Images::OnePlayer);
    if (this->dialogCursor == 1)   PD::drawBitmap(101, 10, Images::TwoPlayer_Selected);
    if (this->dialogCursor != 1)   PD::drawBitmap(101, 10, Images::TwoPlayer);


    if (this->dialogCursor != 5) {  
        PD::drawBitmap(41, 127, this->cookie->getStickIt() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
        PD::drawBitmap(50, 127, Images::StickIt);
    }
    else {
        PD::drawBitmap(41, 127, this->cookie->getStickIt() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
        PD::drawBitmap(50, 127, Images::StickIt_Selected);
    }

    if (this->dialogCursor != 6) {  
        PD::drawBitmap(41, 140, this->cookie->getShowWinner() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
        PD::drawBitmap(50, 140, Images::ShowWinner);
    }
    else {
        PD::drawBitmap(41, 140, this->cookie->getShowWinner() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
        PD::drawBitmap(50, 140, Images::ShowWinner_Selected);
    }

    if (this->dialogCursor != 7) {  
        PD::drawBitmap(41, 153, this->cookie->getHighlightPlayable() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
        PD::drawBitmap(50, 153, Images::HighlightPlayable);
    }
    else {
        PD::drawBitmap(41, 153, this->cookie->getHighlightPlayable() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
        PD::drawBitmap(50, 153, Images::HighlightPlayable_Selected);
    }

    if (this->dialogCursor != 8) {  
        PD::drawBitmap(41, 166, this->cookie->getShowHands() ? Images::CheckBox_Checked : Images::CheckBox_Empty);
        PD::drawBitmap(50, 166, Images::ShowAll);
    }
    else {
        PD::drawBitmap(41, 166, this->cookie->getShowHands() ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
        PD::drawBitmap(50, 166, Images::ShowAll_Selected);
    }

    if (this->cookie->getNumberOfPlayers() == 2) {

        PD::drawBitmap(81, 65, Images::Seat_Left);
        PD::drawBitmap(107, 40, Images::Seat_Top);
        PD::drawBitmap(147, 65, Images::Seat_Right);
        PD::drawBitmap(107, 100, Images::Seat_Bot);

        if (this->dialogCursor == 3) {
            PD::drawBitmap(41, 75, this->cookie->getPlayer2Pos() == 1 ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
            PD::drawBitmap(50, 75, Images::Position1_Selected);
        }
        else {
            PD::drawBitmap(41, 75, this->cookie->getPlayer2Pos() == 1 ? Images::CheckBox_Checked : Images::CheckBox_Empty);
            PD::drawBitmap(50, 75, Images::Position1);
        }

        if (this->dialogCursor == 2) {
            PD::drawBitmap(106, 25, this->cookie->getPlayer2Pos() == 2 ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
            PD::drawBitmap(115, 25, Images::Position2_Selected);
        }
        else {
            PD::drawBitmap(106, 25, this->cookie->getPlayer2Pos() == 2 ? Images::CheckBox_Checked : Images::CheckBox_Empty);
            PD::drawBitmap(115, 25, Images::Position2);
        }

        if (this->dialogCursor == 4) {
            PD::drawBitmap(172, 75, this->cookie->getPlayer2Pos() == 3 ? Images::CheckBox_Checked_Selected : Images::CheckBox_Empty_Selected);
            PD::drawBitmap(181, 75, Images::Position3_Selected);
        }
        else {
            PD::drawBitmap(172, 75, this->cookie->getPlayer2Pos() == 3 ? Images::CheckBox_Checked : Images::CheckBox_Empty);
            PD::drawBitmap(181, 75, Images::Position3);
        }

    }
    else {

        PD::drawBitmap(41, 75, this->cookie->getPlayer2Pos() == 1 ? Images::CheckBox_Checked_Disabled : Images::CheckBox_Empty_Disabled);
        PD::drawBitmap(50, 75, Images::Position1_Disabled);
        PD::drawBitmap(106, 25, this->cookie->getPlayer2Pos() == 2 ? Images::CheckBox_Checked_Disabled : Images::CheckBox_Empty_Disabled);
        PD::drawBitmap(115, 25, Images::Position2_Disabled);
        PD::drawBitmap(172, 75, this->cookie->getPlayer2Pos() == 3 ? Images::CheckBox_Checked_Disabled : Images::CheckBox_Empty_Disabled);
        PD::drawBitmap(181, 75, Images::Position3_Disabled);

        PD::drawBitmap(81, 65, Images::Seat_Left_Disabled);
        PD::drawBitmap(107, 40, Images::Seat_Top_Disabled);
        PD::drawBitmap(147, 65, Images::Seat_Right_Disabled);
        PD::drawBitmap(107, 100, Images::Seat_Bot_Disabled);

    }    

}
