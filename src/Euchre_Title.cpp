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
                            
    switch (this->cookie->getSFX()) {

        case SoundEffects::Music:
        case SoundEffects::Both:
            this->playTheme(this->cookie->getTrack());
            break;

        default:
            break;

    }

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
uint8_t sounds = 0;

void Game::title() {

    #ifdef DEBUG_SOUNDS

        if (PC::buttons.pressed(BTN_B)) { 

            this->playSpeech(static_cast<Speech>(sounds));

        }         

        if (PC::buttons.pressed(BTN_LEFT)) { 

            if (sounds > 0) sounds--;

        }         

        if (PC::buttons.pressed(BTN_RIGHT)) { 

            if (sounds < 31) sounds++;

        }         

    #endif
    

    // Handle player actions ..

    switch (this->titleScreenVariables.mode) {

        case TitleScreenMode::Sounds:

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

            if (PC::buttons.pressed(BTN_RIGHT)) {

                this->titleScreenVariables.mode = TitleScreenMode::StartGame;

            }

            break;

        case TitleScreenMode::StartGame:

            if (PC::buttons.pressed(BTN_A)) { 

                this->gameState = GameState::Selection_Init;

            }      
            
            if (PC::buttons.pressed(BTN_LEFT)) {

                this->titleScreenVariables.mode = TitleScreenMode::Sounds;

            }
            
            if (PC::buttons.pressed(BTN_RIGHT)) {

                this->titleScreenVariables.mode = TitleScreenMode::Instructions;

            }

            break;

        case TitleScreenMode::Instructions:

            if (PC::buttons.pressed(BTN_A)) { 

                this->gameState = GameState::Instructions_Init;

            }  
            
            if (PC::buttons.pressed(BTN_LEFT)) {

                this->titleScreenVariables.mode = TitleScreenMode::StartGame;

            }

            break;

    }



    // Render page ..

    PD::fillScreen(1);
    PD::drawBitmap(31, 60, Images::Euchre);


    uint16_t frameCount = PC::frameCount % 96;

    if (this->titleScreenVariables.mode == TitleScreenMode::Sounds) {
            
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
    else {
         
        switch (this->cookie->getSFX()) {

            case SoundEffects::Music:
                PD::drawBitmap(4, 164, Images::Sound_Music_Grey);
                break;

            case SoundEffects::SFX:
                PD::drawBitmap(4, 164, Images::Sound_SFX_Grey);
                break;

            case SoundEffects::Both:
                PD::drawBitmap(4, 164, Images::Sound_Both_Grey);
                break;

            default:
                PD::drawBitmap(4, 164, Images::Sound_None_Grey);
                break;

        }

    }


    switch (this->titleScreenVariables.mode) {
        
        case TitleScreenMode::Sounds:
            PD::drawBitmap(65, 164, Images::PlayGame_Grey);
            PD::drawBitmap(145, 164, Images::Instructions_Grey);
            break;
        
        case TitleScreenMode::StartGame:
            PD::drawBitmap(65, 164, Images::PlayGame_White);
            PD::drawBitmap(145, 164, Images::Instructions_Grey);
            break;

        case TitleScreenMode::Instructions:
            PD::drawBitmap(65, 164, Images::PlayGame_Grey);
            PD::drawBitmap(145, 164, Images::Instructions_White);
            break;

    }

    #ifdef DEBUG_SOUNDS
        PD::setCursor(0,0);
        PD::setColor(6);
        PD::fontSize = 2;
        PD::print((uint16_t)sounds);
    #endif

}
