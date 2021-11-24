#pragma once

namespace Images {

    #include "Title.h"
    #include "Suits.h"
    #include "Card_Blue.h"

    #include "PlayGame_White.h"
    #include "PlayGame_Grey.h"
    #include "Instructions_White.h"
    #include "Instructions_Grey.h"

    #include "Sound_Both_Grey.h"
    #include "Sound_Both_White.h"
    #include "Sound_Music_Grey.h"
    #include "Sound_Music_White.h"
    #include "Sound_SFX_Grey.h"
    #include "Sound_SFX_White.h"
    #include "Sound_None_Grey.h"
    #include "Sound_None_White.h"

    #include "rotate/Suits_00_00.h"
    #include "rotate/Suits_00_01.h"
    #include "rotate/Suits_00_02.h"
    #include "rotate/Suits_00_03.h"
    #include "rotate/Suits_00_04.h"

    #include "rotate/Suits_01_00.h"
    #include "rotate/Suits_01_01.h"
    #include "rotate/Suits_01_02.h"
    #include "rotate/Suits_01_03.h"
    #include "rotate/Suits_01_04.h"

    #include "rotate/Suits_02_00.h"
    #include "rotate/Suits_02_01.h"
    #include "rotate/Suits_02_02.h"
    #include "rotate/Suits_02_03.h"
    #include "rotate/Suits_02_04.h"

    #include "rotate/Suits_03_00.h"
    #include "rotate/Suits_03_01.h"
    #include "rotate/Suits_03_02.h"
    #include "rotate/Suits_03_03.h"
    #include "rotate/Suits_03_04.h"

    const uint8_t * const Suits_Rotate[9 * 4] = { 
        Suits_00_00,
        Suits_00_01,
        Suits_00_02,
        Suits_00_03,
        Suits_00_04,
        Suits_00_03,
        Suits_00_02,
        Suits_00_01,
        Suits_00_00,
        Suits_01_00,
        Suits_01_01,
        Suits_01_02,
        Suits_01_03,
        Suits_01_04,
        Suits_01_03,
        Suits_01_02,
        Suits_01_01,
        Suits_01_00,
        Suits_02_00,
        Suits_02_01,
        Suits_02_02,
        Suits_02_03,
        Suits_02_04,
        Suits_02_03,
        Suits_02_02,
        Suits_02_01,
        Suits_02_00,
        Suits_03_00,
        Suits_03_01,
        Suits_03_02,
        Suits_03_03,
        Suits_03_04,
        Suits_03_03,
        Suits_03_02,
        Suits_03_01,
        Suits_03_00,
    };

};