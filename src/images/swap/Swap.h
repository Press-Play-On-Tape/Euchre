#pragma once

namespace Images {

    #include "Swap_00.h"
    #include "Swap_01.h"

    #include "CurrentHand.h"
    #include "PreviousHand.h"

    #include "DealAgain.h"
    #include "DiscardCard.h"
    #include "FollowTheLead.h"
    #include "LeadACard.h"
    #include "Player1.h"
    #include "Player2.h"
    #include "YourBid.h"

    const uint8_t * const Swap_Text[] = { 
        DiscardCard,
        LeadACard,
        FollowTheLead,
        YourBid,
        DealAgain
    };

};

