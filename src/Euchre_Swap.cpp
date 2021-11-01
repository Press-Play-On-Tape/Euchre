#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::swap_Init() {

    this->gameState = GameState::Swap;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::swap() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = this->savedState;

    }         


    if (this->gameStatus.getPlayerView() != 0) {

        PD::setColor(3);
        PD::fillRect(0, 0, 110, 176);
        PD::setColor(1);
        PD::fillRect(110, 0, 110, 176);
        PD::drawBitmap(79, 60, Images::Swap_01);

    }
    else {

        PD::setColor(1);
        PD::fillRect(0, 0, 110, 176);
        PD::setColor(3);
        PD::fillRect(110, 0, 110, 176);
        PD::drawBitmap(79, 60, Images::Swap_00);

    }

}
