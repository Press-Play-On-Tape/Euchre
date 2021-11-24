#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 0;

};


struct TitleScreenVariables {

    TitleScreenMode mode = TitleScreenMode::StartGame;

    uint8_t top = 0;
    uint8_t bottom = 0;
    uint8_t counter = 0;

};
