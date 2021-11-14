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
        this->firstValidCard(this->gameStatus.getCurrentPlayer());

    }         


    if (this->gameStatus.getPlayerView() != 0) {

        PD::setColor(3);
        PD::fillRect(0, 0, 110, 176);
        PD::setColor(1);
        PD::fillRect(110, 0, 110, 176);
        PD::drawBitmap(81, 40, Images::Swap_01);

    }
    else {

        PD::setColor(1);
        PD::fillRect(0, 0, 110, 176);
        PD::setColor(3);
        PD::fillRect(110, 0, 110, 176);
        PD::drawBitmap(81, 40, Images::Swap_00);

    }


    // Render caption ..

    {
      
        uint8_t width[] = { 104, 84, 104, 58, 74 };
        uint8_t overallWidth = 54 + 8 + width[static_cast<uint8_t>(this->swapCaption)];
        uint8_t playerPos =  110 - (overallWidth / 2);

        switch (this->gameStatus.getPlayerView()) {

            case 0:

                PD::drawBitmap(playerPos, 105, Images::Player1);
                PD::drawBitmap(playerPos + 62 , 105, Images::Swap_Text[static_cast<uint8_t>(this->swapCaption)]);
                break;

            default:

                PD::drawBitmap(playerPos, 105, Images::Player2);
                PD::drawBitmap(playerPos + 62 , 105, Images::Swap_Text[static_cast<uint8_t>(this->swapCaption)]);
                break;

        }

    }


    // Render last hand?

    bool renderPrevHand = false;
    bool renderThisHand = false;

    uint8_t xPrev = 0;
    uint8_t xThis = 0;

    for (uint8_t i = 0; i < 4; i++) {

        if (this->gameStatus.getLastHand(i).getCardIndex() != Cards::NoCard) {

            renderPrevHand = true;
            xPrev++;

        }

        if (this->gameStatus.getCurrentHand(i).getCardIndex() != Cards::NoCard) {

            renderThisHand = true;
            xThis++;

        }

    }

    xPrev = 35 - ((xPrev - 1) * 8);
    xThis = 145 - ((xThis - 1) * 8);

    if (renderPrevHand) {

        PD::drawBitmap(24, 140, Images::PreviousHand);
        uint8_t spacing = 0;

        for (uint8_t i = 0; i < 4; i++) {

            if (this->gameStatus.getLastHand(i).getCardIndex() != Cards::NoCard) {

                this->renderCard(Orientation::Bottom, this->gameStatus.getLastHand(i), xPrev + (spacing * 16), 151, false, true, false);
                spacing++;
                
            }

        }

    }

    if (renderThisHand) {

        PD::drawBitmap(136, 140, Images::CurrentHand);

        uint8_t spacing = 0;

        for (uint8_t i = 0; i < 4; i++) {

            if (this->gameStatus.getCurrentHand(i).getCardIndex() != Cards::NoCard) {

                this->renderCard(Orientation::Bottom, this->gameStatus.getCurrentHand(i), xThis + (spacing * 16), 151, false, true, false);
                spacing++;
                
            }

        }

    }

}
