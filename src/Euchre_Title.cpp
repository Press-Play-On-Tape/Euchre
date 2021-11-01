#include "Euchre.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title_Init() {

    this->gameState = GameState::Title;
    this->playTheme(this->cookie->getTrack());

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Selection_Init;

    }         

    if (PC::buttons.pressed(BTN_UP)) {

        this->cookie->decSFX();
        this->cookie->saveCookie();

        if (this->cookie->getSFX() != SoundEffects::Both && this->cookie->getSFX() != SoundEffects::Music) {

            this->muteTheme();
            
        }
        else {

            this->playTheme(this->cookie->getTrack());

        }

    }

    if (PC::buttons.pressed(BTN_DOWN)) {

        this->cookie->incSFX();
        this->cookie->saveCookie();

        if (this->cookie->getSFX() != SoundEffects::Both && this->cookie->getSFX() != SoundEffects::Music) {

            this->muteTheme();
            
        }
        else {

            this->playTheme(this->cookie->getTrack());
            
        }
        
    }

    // Render page ..

    PD::drawBitmap(0, 0, Images::Title);



    uint16_t frameCount = PC::frameCount % 96;

    switch (this->cookie->getSFX()) {

        case SoundEffects::Music:
            PD::drawBitmap(4, 164, Images::Sound_Music_White);
            break;

        case SoundEffects::SFX:
            PD::drawBitmap(4, 164, Images::Sound_SFX_White);
            break;

        case SoundEffects::Both:
            PD::drawBitmap(4, 164, Images::Sound_Both_White);
            break;

        default:
            PD::drawBitmap(4, 164, Images::Sound_None_White);
            break;

    }



}
