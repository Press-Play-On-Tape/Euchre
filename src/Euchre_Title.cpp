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
//    this->playTheme(Themes::Main);
//    this->gamePlay.setCounter(0);

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Selection_Init;

    }         

    // if (PC::buttons.pressed(BTN_UP)) {

    //     this->cookie->sfx--;
    //     this->cookie->saveCookie();

    //     if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

    //         this->muteTheme();
            
    //     }
    //     else {

    //         this->playTheme(Themes::Main);

    //     }

    // }

    // if (PC::buttons.pressed(BTN_DOWN)) {

    //     this->cookie->sfx++;
    //     this->cookie->saveCookie();

    //     if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

    //         this->muteTheme();
            
    //     }
    //     else {

    //         this->playTheme(Themes::Main);
            
    //     }
        
    // }

    // Render page ..

    // PD::drawBitmap(0, 0, Images::Background);
    // PD::drawBitmap(110, 0, Images::Background, NOROT, FLIPH);
    // PD::drawBitmap(27, 82, Images::Title_02);


    // uint16_t frameCount = PC::frameCount % 96;

    // switch (frameCount) {

    //     case 0 ... 9:
    //         PD::drawBitmap(41, 1, Images::Title_01_Tops[frameCount / 2]);
    //         PD::drawBitmap(24, 113, Images::Title_01_Bots[frameCount / 2]);
    //         break;

    //     default:
    //         PD::drawBitmap(41, 1, Images::Title_01_Top);
    //         PD::drawBitmap(24, 113, Images::Title_01_Bot);
    //         break;

    // }


    // switch (this->cookie->sfx) {

    //     case SoundEffects::Music:
    //         PD::drawBitmap(186, 164, Images::Sound_Music);
    //         break;

    //     case SoundEffects::SFX:
    //         PD::drawBitmap(186, 164, Images::Sound_SFX);
    //         break;

    //     case SoundEffects::Both:
    //         PD::drawBitmap(186, 164, Images::Sound_Both);
    //         break;

    //     default:
    //         PD::drawBitmap(186, 164, Images::Sound_None);
    //         break;

    // }



    PD::drawBitmap(0, 0, Images::Title);

}
