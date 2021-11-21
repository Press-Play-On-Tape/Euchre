#include "Euchre.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;

}

void Game::loop() {

    PC::buttons.pollButtons();

    switch (this->gameState) {

        case GameState::Splash:
            PD::clear();
            this->splashScreen();
            break;

        case GameState::Title_Init:
            this->title_Init();
            [[fallthrough]]

        case GameState::Title:
            PD::clear();
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
            PD::clear();
            this->swap();
            break;

        case GameState::Pause_Init:
            this->pause_Init();
            [[fallthrough]]

        case GameState::Pause:
            PD::clear();
            this->pause();
            break;

        case GameState::Game_Init:
            this->game_Init();
            [[fallthrough]]

        case GameState::Game_NewHand_Init ... GameState::GameOver:
            PD::clear();
            this->game();
            break;

        case GameState::Instructions_Init:
            this->instructions_Init();
            [[fallthrough]]

        case GameState::Instructions_00 ... GameState::Instructions_04:
            this->instructions();
            break;

    }

}
