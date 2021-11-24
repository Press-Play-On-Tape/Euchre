#pragma once

namespace Images {

    #include "Card_Front_Disabled.h"
    #include "Card_Front.h"
    #include "Card_Front_Rot.h"
    #include "Card_Back.h"
    #include "Card_Back_Rot.h"

    #include "suits/top/Suit_00_Top.h"
    #include "suits/top/Suit_01_Top.h"
    #include "suits/top/Suit_02_Top.h"
    #include "suits/top/Suit_03_Top.h"

    #include "suits/bottom/Suit_00_Bot.h"
    #include "suits/bottom/Suit_01_Bot.h"
    #include "suits/bottom/Suit_02_Bot.h"
    #include "suits/bottom/Suit_03_Bot.h"

    #include "suits/left/Suit_00_Left.h"
    #include "suits/left/Suit_01_Left.h"
    #include "suits/left/Suit_02_Left.h"
    #include "suits/left/Suit_03_Left.h"

    #include "suits/right/Suit_00_Right.h"
    #include "suits/right/Suit_01_Right.h"
    #include "suits/right/Suit_02_Right.h"
    #include "suits/right/Suit_03_Right.h"

    #include "numbers/bottom/Numbers_Blk_09_Bot.h"
    #include "numbers/bottom/Numbers_Blk_10_Bot.h"
    #include "numbers/bottom/Numbers_Blk_0J_Bot.h"
    #include "numbers/bottom/Numbers_Blk_0Q_Bot.h"
    #include "numbers/bottom/Numbers_Blk_0K_Bot.h"
    #include "numbers/bottom/Numbers_Blk_0A_Bot.h"

    #include "numbers/bottom/Numbers_Red_09_Bot.h"
    #include "numbers/bottom/Numbers_Red_10_Bot.h"
    #include "numbers/bottom/Numbers_Red_0J_Bot.h"
    #include "numbers/bottom/Numbers_Red_0Q_Bot.h"
    #include "numbers/bottom/Numbers_Red_0K_Bot.h"
    #include "numbers/bottom/Numbers_Red_0A_Bot.h"

    #include "numbers/top/Numbers_Blk_09_Top.h"
    #include "numbers/top/Numbers_Blk_10_Top.h"
    #include "numbers/top/Numbers_Blk_0J_Top.h"
    #include "numbers/top/Numbers_Blk_0Q_Top.h"
    #include "numbers/top/Numbers_Blk_0K_Top.h"
    #include "numbers/top/Numbers_Blk_0A_Top.h"

    #include "numbers/top/Numbers_Red_09_Top.h"
    #include "numbers/top/Numbers_Red_10_Top.h"
    #include "numbers/top/Numbers_Red_0J_Top.h"
    #include "numbers/top/Numbers_Red_0Q_Top.h"
    #include "numbers/top/Numbers_Red_0K_Top.h"
    #include "numbers/top/Numbers_Red_0A_Top.h"

    #include "numbers/left/Numbers_Blk_09_Left.h"
    #include "numbers/left/Numbers_Blk_10_Left.h"
    #include "numbers/left/Numbers_Blk_0J_Left.h"
    #include "numbers/left/Numbers_Blk_0Q_Left.h"
    #include "numbers/left/Numbers_Blk_0K_Left.h"
    #include "numbers/left/Numbers_Blk_0A_Left.h"

    #include "numbers/left/Numbers_Red_09_Left.h"
    #include "numbers/left/Numbers_Red_10_Left.h"
    #include "numbers/left/Numbers_Red_0J_Left.h"
    #include "numbers/left/Numbers_Red_0Q_Left.h"
    #include "numbers/left/Numbers_Red_0K_Left.h"
    #include "numbers/left/Numbers_Red_0A_Left.h"

    #include "numbers/right/Numbers_Blk_09_Right.h"
    #include "numbers/right/Numbers_Blk_10_Right.h"
    #include "numbers/right/Numbers_Blk_0J_Right.h"
    #include "numbers/right/Numbers_Blk_0Q_Right.h"
    #include "numbers/right/Numbers_Blk_0K_Right.h"
    #include "numbers/right/Numbers_Blk_0A_Right.h"

    #include "numbers/right/Numbers_Red_09_Right.h"
    #include "numbers/right/Numbers_Red_10_Right.h"
    #include "numbers/right/Numbers_Red_0J_Right.h"
    #include "numbers/right/Numbers_Red_0Q_Right.h"
    #include "numbers/right/Numbers_Red_0K_Right.h"
    #include "numbers/right/Numbers_Red_0A_Right.h"


    const uint8_t * const Suits_Bot[] = { 
        Suit_00_Bot,
        Suit_01_Bot,
        Suit_02_Bot,
        Suit_03_Bot,
    };

    const uint8_t * const Suits_Left[] = { 
        Suit_00_Left,
        Suit_01_Left,
        Suit_02_Left,
        Suit_03_Left,
    };

    const uint8_t * const Suits_Top[] = { 
        Suit_00_Top,
        Suit_01_Top,
        Suit_02_Top,
        Suit_03_Top,
    };

    const uint8_t * const Suits_Right[] = { 
        Suit_00_Right,
        Suit_01_Right,
        Suit_02_Right,
        Suit_03_Right,
    };

    const uint8_t * const Suits_All[] = { 
        Suit_00_Bot,
        Suit_01_Bot,
        Suit_02_Bot,
        Suit_03_Bot,
        Suit_00_Left,
        Suit_01_Left,
        Suit_02_Left,
        Suit_03_Left,
        Suit_00_Top,
        Suit_01_Top,
        Suit_02_Top,
        Suit_03_Top,
        Suit_00_Right,
        Suit_01_Right,
        Suit_02_Right,
        Suit_03_Right,
    };

    const uint8_t * const Numbers_Bot_Blk[] = { 
        Numbers_Blk_09_Bot,
        Numbers_Blk_10_Bot,
        Numbers_Blk_0J_Bot,
        Numbers_Blk_0Q_Bot,
        Numbers_Blk_0K_Bot,
        Numbers_Blk_0A_Bot,
    };

    const uint8_t * const Numbers_Bot_Red[] = { 
        Numbers_Red_09_Bot,
        Numbers_Red_10_Bot,
        Numbers_Red_0J_Bot,
        Numbers_Red_0Q_Bot,
        Numbers_Red_0K_Bot,
        Numbers_Red_0A_Bot,
    };

    const uint8_t * const Numbers_Top_Blk[] = { 
        Numbers_Blk_09_Top,
        Numbers_Blk_10_Top,
        Numbers_Blk_0J_Top,
        Numbers_Blk_0Q_Top,
        Numbers_Blk_0K_Top,
        Numbers_Blk_0A_Top,
    };

    const uint8_t * const Numbers_Top_Red[] = { 
        Numbers_Red_09_Top,
        Numbers_Red_10_Top,
        Numbers_Red_0J_Top,
        Numbers_Red_0Q_Top,
        Numbers_Red_0K_Top,
        Numbers_Red_0A_Top,
    };

    const uint8_t * const Numbers_Left_Blk[] = { 
        Numbers_Blk_09_Left,
        Numbers_Blk_10_Left,
        Numbers_Blk_0J_Left,
        Numbers_Blk_0Q_Left,
        Numbers_Blk_0K_Left,
        Numbers_Blk_0A_Left,
    };

    const uint8_t * const Numbers_Left_Red[] = { 
        Numbers_Red_09_Left,
        Numbers_Red_10_Left,
        Numbers_Red_0J_Left,
        Numbers_Red_0Q_Left,
        Numbers_Red_0K_Left,
        Numbers_Red_0A_Left,
    };

    const uint8_t * const Numbers_Right_Blk[] = { 
        Numbers_Blk_09_Right,
        Numbers_Blk_10_Right,
        Numbers_Blk_0J_Right,
        Numbers_Blk_0Q_Right,
        Numbers_Blk_0K_Right,
        Numbers_Blk_0A_Right,
    };

    const uint8_t * const Numbers_Right_Red[] = { 
        Numbers_Red_09_Right,
        Numbers_Red_10_Right,
        Numbers_Red_0J_Right,
        Numbers_Red_0Q_Right,
        Numbers_Red_0K_Right,
        Numbers_Red_0A_Right,
    };

};