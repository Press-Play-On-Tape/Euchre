#pragma once

namespace Images {

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

};

