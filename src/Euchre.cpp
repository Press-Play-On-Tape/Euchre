#include "Euchre.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;

}

void Game::loop() {

    PC::buttons.pollButtons();
    PD::clear();

    switch (this->gameState) {

        case GameState::Splash:
            this->splashScreen();
            break;

        case GameState::Title_Init:
            this->title_Init();
            [[fallthrough]]

        case GameState::Title:
            this->title();
            break;

        case GameState::Selection_Init:
            this->selection_Init();
            [[fallthrough]]

        case GameState::Selection:
            this->selection();
            break;

        case GameState::Swap_Init:
            this->swap_Init();
            [[fallthrough]]

        case GameState::Swap:
            this->swap();
            break;

        case GameState::Pause_Init:
            this->pause_Init();
            [[fallthrough]]

        case GameState::Pause:
            this->pause();
            break;

        case GameState::Game_Init:
            this->game_Init();
            [[fallthrough]]

        case GameState::Game_NewHand_Init ... GameState::Game_Xxx:
            this->game();
            break;

    }

}
