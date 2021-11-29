#pragma once

namespace Images {

    #include "BlueTape_Shadow.h"
    #include "GreenTape_Shadow.h"
    #include "RedTape_Shadow.h"

    #include "ArrowLeft.h"
    #include "ArrowRight.h"

    const uint8_t * const Tapes_Shadow[3] = { 
        GreenTape_Shadow,
        RedTape_Shadow,
        BlueTape_Shadow,
    };

};