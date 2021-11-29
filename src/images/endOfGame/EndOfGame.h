#pragma once

namespace Images {

    #include "EOG_Alpha.h"
    #include "EOG_Beta.h"
    #include "EOG_Team.h"
    #include "EOG_Wins.h"

    #include "Dither_Green_00.h"
    #include "Dither_Green_01.h"
    #include "Dither_Green_02.h"
    #include "Dither_Green_03.h"
    #include "Dither_Green_04.h"
    #include "Dither_Green_05.h"
    #include "Dither_Green_06.h"
    #include "Dither_Green_07.h"
    #include "Dither_Green_08.h"
    #include "Dither_Green_09.h"
    #include "Dither_Green_10.h"
    #include "Dither_Green_11.h"
    #include "Dither_Green_12.h"
    #include "Dither_Green_13.h"
    #include "Dither_Green_14.h"

    const uint8_t * const Dither_Green[] = { 
        Dither_Green_00,
        Dither_Green_01,
        Dither_Green_02,
        Dither_Green_03,
        Dither_Green_04,
        Dither_Green_05,
        Dither_Green_06,
        Dither_Green_07,
        Dither_Green_08,
        Dither_Green_09,
        Dither_Green_10,
        Dither_Green_11,
        Dither_Green_12,
        Dither_Green_13,
        Dither_Green_14,
    };

    const uint8_t * const Dither_Green2[] = { 
        Dither_Green_01,
        Dither_Green_03,
        Dither_Green_05,
        Dither_Green_07,
        Dither_Green_09,
        Dither_Green_11,
        Dither_Green_13,
    };
};

