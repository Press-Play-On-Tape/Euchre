#pragma once

namespace Images {

    #include "Points_01.h"
    #include "Points_02.h"
    #include "Points_04.h"
    #include "Euchre.h"
    #include "March.h"
    #include "TeamAlpha.h"
    #include "TeamBeta.h"

    #include "Minus_00.h"
    #include "Minus_01.h"
    #include "Minus_02.h"
    #include "Minus_03.h"
    #include "Minus_04.h"

    #include "Plus_00.h"
    #include "Plus_01.h"
    #include "Plus_02.h"
    #include "Plus_03.h"
    #include "Plus_04.h"

    #include "One_00.h"
    #include "One_01.h"
    #include "One_02.h"
    #include "One_03.h"
    #include "One_04.h"

    #include "Two_00.h"
    #include "Two_01.h"
    #include "Two_02.h"
    #include "Two_03.h"
    #include "Two_04.h"

    #include "Four_00.h"
    #include "Four_01.h"
    #include "Four_02.h"
    #include "Four_03.h"
    #include "Four_04.h"

    const int8_t Sign_One_OffsetsX[] = { -1, -1, -3, -2, -2 };
    const int8_t Sign_One_OffsetsY[] = { 15, 19, 21, 24, 28 };

    const int8_t Sign_Two_OffsetsX[] = { 0, 0, 0, 0, 0 };
    const int8_t Sign_Two_OffsetsY[] = { 20, 24, 28, 30, 38 };

    const int8_t Sign_Four_OffsetsX[] = { -1, -1, -2, -3, -2 };
    const int8_t Sign_Four_OffsetsY[] = { 15, 19, 23, 25, 28 };

    const uint8_t * const Minus[] = { 
        Minus_00,
        Minus_01,
        Minus_02,
        Minus_03,
        Minus_04,
    };

    const uint8_t * const Plus[] = { 
        Plus_00,
        Plus_01,
        Plus_02,
        Plus_03,
        Plus_04,
    };

    const uint8_t One_CentreX = 21;
    const uint8_t One_CentreY = 15;

    const uint8_t One_OffsetsX[] = { 0, 4, 7, 11, 14 };
    const uint8_t One_OffsetsX2[] = { 10, 14, 16, 18, 18 };
    const uint8_t One_OffsetsY[] = { 0, 4, 6, 9, 12 };

    const uint8_t * const One[] = { 
        One_00,
        One_01,
        One_02,
        One_03,
        One_04,
    };

    const uint8_t Two_CentreX = 21;
    const uint8_t Two_CentreY = 15;

    const uint8_t Two_OffsetsX[] = { 0, 4, 7, 10, 13 };
    const uint8_t Two_OffsetsX2[] = { 10, 14, 14, 16, 18 };
    const uint8_t Two_OffsetsY[] = { 0, 4, 7, 10, 12 };

    const uint8_t * const Two[] = { 
        Two_00,
        Two_01,
        Two_02,
        Two_03,
        Two_04,
    };

    const uint8_t Four_CentreX = 18;
    const uint8_t Four_CentreY = 17;

    const uint8_t Four_OffsetsX[] = { 0, 4, 7, 10, 13 };
    const uint8_t Four_OffsetsX2[] = { 12, 16, 18, 20, 20 };
    const uint8_t Four_OffsetsY[] = { 0, 4, 8, 11, 14 };

    const uint8_t * const Four[] = { 
        Four_00,
        Four_01,
        Four_02,
        Four_03,
        Four_04,
    };

};

