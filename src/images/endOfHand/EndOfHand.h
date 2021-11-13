#pragma once

namespace Images {

    #include "Points_01.h"
    #include "Points_02.h"
    #include "Points_04.h"
    #include "Euchre.h"
    #include "March.h"
    #include "TeamAlpha.h"
    #include "TeamBeta.h"

    #include "MinusTwo_00.h"
    #include "MinusTwo_01.h"
    #include "MinusTwo_02.h"
    #include "MinusTwo_03.h"
    #include "MinusTwo_04.h"

    #include "PlusOne_00.h"
    #include "PlusOne_01.h"
    #include "PlusOne_02.h"
    #include "PlusOne_03.h"
    #include "PlusOne_04.h"

    #include "PlusTwo_00.h"
    #include "PlusTwo_01.h"
    #include "PlusTwo_02.h"
    #include "PlusTwo_03.h"
    #include "PlusTwo_04.h"

    #include "PlusFour_00.h"
    #include "PlusFour_01.h"
    #include "PlusFour_02.h"
    #include "PlusFour_03.h"
    #include "PlusFour_04.h"

    const uint8_t MinusTwo_CentreX = 21;
    const uint8_t MinusTwo_CentreY = 15;

    const uint8_t MinusTwo_OffsetsX[] = { 0, 3, 6, 10, 15 };
    const uint8_t MinusTwo_OffsetsY[] = { 0, 2, 4, 7, 10 };
    
    const uint8_t * const MinusTwo[] = { 
        MinusTwo_00,
        MinusTwo_01,
        MinusTwo_02,
        MinusTwo_03,
        MinusTwo_04,
    };

    const uint8_t PlusOne_CentreX = 21;
    const uint8_t PlusOne_CentreY = 15;

    const uint8_t PlusOne_OffsetsX[] = { 0, 3, 6, 9, 13 };
    const uint8_t PlusOne_OffsetsY[] = { 0, 2, 4, 6, 9 };

    const uint8_t * const PlusOne[] = { 
        PlusOne_00,
        PlusOne_01,
        PlusOne_02,
        PlusOne_03,
        PlusOne_04,
    };

    const uint8_t PlusTwo_CentreX = 21;
    const uint8_t PlusTwo_CentreY = 15;

    const uint8_t PlusTwo_OffsetsX[] = { 0, 3, 6, 10, 15 };
    const uint8_t PlusTwo_OffsetsY[] = { 2, 4, 6, 9, 10 };

    const uint8_t * const PlusTwo[] = { 
        PlusTwo_00,
        PlusTwo_01,
        PlusTwo_02,
        PlusTwo_03,
        PlusTwo_04,
    };

    const uint8_t PlusFour_CentreX = 18;
    const uint8_t PlusFour_CentreY = 17;

    const uint8_t PlusFour_OffsetsX[] = { 0, 2, 5, 8, 11 };
    const uint8_t PlusFour_OffsetsY[] = { 0, 2, 5, 8, 11 };

    const uint8_t * const PlusFour[] = { 
        PlusFour_00,
        PlusFour_01,
        PlusFour_02,
        PlusFour_03,
        PlusFour_04,
    };

};

