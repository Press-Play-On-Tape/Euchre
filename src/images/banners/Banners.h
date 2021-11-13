#pragma once

namespace Images {

    #include "Banner_Team_Bot.h"
    #include "Banner_Alone_Bot.h"
    #include "Banner_Team_Top.h"
    #include "Banner_Alone_Top.h"
    #include "Banner_Team_Left.h"
    #include "Banner_Alone_Left.h"
    #include "Banner_Team_Right.h"
    #include "Banner_Alone_Right.h"
    #include "Trumps.h"

    const uint8_t * const Banner_Team[] = { 
        Banner_Team_Bot,
        Banner_Team_Left,
        Banner_Team_Top,
        Banner_Team_Right,
    };

    const uint8_t * const Banner_Alone[] = { 
        Banner_Alone_Bot,
        Banner_Alone_Left,
        Banner_Alone_Top,
        Banner_Alone_Right,
    };

};