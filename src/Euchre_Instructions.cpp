#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::instructions_Init() {

    this->gameState = GameState::Instructions_00;

    if (this->instructionFile.openRO(Constants::instructions[0])) {
        this->instructionFile.read(PD::getBuffer(), 2);
        this->instructionFile.read(PD::getBuffer(), (220 * 176 / 2));
    }

}   

void Game::instructions() {


    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Title;

    }         

    if (PC::buttons.pressed(BTN_LEFT)) { 
        
        if (this->gameState == GameState::Instructions_00) {

            this->gameState = GameState::Title;

        }
        else {
            
            this->gameState--;

            if (this->instructionFile.openRO(Constants::instructions[static_cast<uint8_t>(this->gameState) - static_cast<uint8_t>(GameState::Instructions_00)])) {
                this->instructionFile.read(PD::getBuffer(), 2);
                this->instructionFile.read(PD::getBuffer(), (220 * 176 / 2));
            }

        }

    }         

    if (PC::buttons.pressed(BTN_RIGHT)) { 
        
        if (this->gameState == GameState::Instructions_04) {

            this->gameState = GameState::Title;

        }
        else {

            this->gameState++;

            if (this->instructionFile.openRO(Constants::instructions[static_cast<uint8_t>(this->gameState) - static_cast<uint8_t>(GameState::Instructions_00)])) {
                this->instructionFile.read(PD::getBuffer(), 2);
                this->instructionFile.read(PD::getBuffer(), (220 * 176 / 2));
            }

        }

    }         

}
