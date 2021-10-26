#pragma once

namespace Images {

    #include "Scoreboard.h"

    #include "bottom/Dealer_Bot.h"
    #include "left/Dealer_Left.h"
    #include "top/Dealer_Top.h"
    #include "right/Dealer_Right.h"

    #include "bottom/Tricks_00_Bot.h"
    #include "bottom/Tricks_01_Bot.h"
    #include "bottom/Tricks_02_Bot.h"
    #include "bottom/Tricks_03_Bot.h"
    #include "bottom/Tricks_04_Bot.h"
    #include "bottom/Tricks_05_Bot.h"

    #include "top/Tricks_00_Top.h"
    #include "top/Tricks_01_Top.h"
    #include "top/Tricks_02_Top.h"
    #include "top/Tricks_03_Top.h"
    #include "top/Tricks_04_Top.h"
    #include "top/Tricks_05_Top.h"

    #include "left/Tricks_00_Left.h"
    #include "left/Tricks_01_Left.h"
    #include "left/Tricks_02_Left.h"
    #include "left/Tricks_03_Left.h"
    #include "left/Tricks_04_Left.h"
    #include "left/Tricks_05_Left.h"

    #include "right/Tricks_00_Right.h"
    #include "right/Tricks_01_Right.h"
    #include "right/Tricks_02_Right.h"
    #include "right/Tricks_03_Right.h"
    #include "right/Tricks_04_Right.h"
    #include "right/Tricks_05_Right.h"

    #include "bottom/Hands_00_Bot.h"
    #include "bottom/Hands_01_Bot.h"
    #include "bottom/Hands_02_Bot.h"
    #include "bottom/Hands_03_Bot.h"
    #include "bottom/Hands_04_Bot.h"
    #include "bottom/Hands_05_Bot.h"
    #include "bottom/Hands_06_Bot.h"
    #include "bottom/Hands_07_Bot.h"
    #include "bottom/Hands_08_Bot.h"
    #include "bottom/Hands_09_Bot.h"
    #include "bottom/Hands_10_Bot.h"
    #include "bottom/Hands_11_Bot.h"
    #include "bottom/Hands_12_Bot.h"
    #include "bottom/Hands_13_Bot.h"
    #include "bottom/Hands_14_Bot.h"

    const uint8_t * const Tricks_Bot[] = { 
        Tricks_00_Bot,
        Tricks_01_Bot,
        Tricks_02_Bot,
        Tricks_03_Bot,
        Tricks_04_Bot,
        Tricks_05_Bot,
    };

    const uint8_t * const Tricks_Top[] = { 
        Tricks_00_Top,
        Tricks_01_Top,
        Tricks_02_Top,
        Tricks_03_Top,
        Tricks_04_Top,
        Tricks_05_Top,
    };

    const uint8_t * const Tricks_Left[] = { 
        Tricks_00_Left,
        Tricks_01_Left,
        Tricks_02_Left,
        Tricks_03_Left,
        Tricks_04_Left,
        Tricks_05_Left,
    };

    const uint8_t * const Tricks_Right[] = { 
        Tricks_00_Right,
        Tricks_01_Right,
        Tricks_02_Right,
        Tricks_03_Right,
        Tricks_04_Right,
        Tricks_05_Right,
    };

    const uint8_t * const Hands_Bot[] = { 
        Hands_00_Bot,
        Hands_01_Bot,
        Hands_02_Bot,
        Hands_03_Bot,
        Hands_04_Bot,
        Hands_05_Bot,
        Hands_06_Bot,
        Hands_07_Bot,
        Hands_08_Bot,
        Hands_09_Bot,
        Hands_10_Bot,
        Hands_11_Bot,
        Hands_12_Bot,
        Hands_13_Bot,
        Hands_14_Bot,
    };

};

