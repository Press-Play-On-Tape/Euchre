#pragma once

namespace Images {

    #include "Empty_Bottom.h"
    #include "Empty_Left.h"
    #include "Empty_Top.h"
    #include "Empty_Right.h"

    #include "DiscardACard.h"
    #include "PlayACard.h"

    #include "text/Text_Alone.h"
    #include "text/Text_Mine.h"
    #include "text/Text_Pass.h"
    #include "text/Text_Sorry.h"
    #include "text/Text_TakeIt.h"
    #include "text/Text_Trumped.h"
    #include "text/Text_Winner.h"
    #include "text/Text_WooHoo.h"

    #include "text/Text_Spades_Team.h"
    #include "text/Text_Spades_Alone.h"
    #include "text/Text_Clubs_Team.h"
    #include "text/Text_Clubs_Alone.h"
    #include "text/Text_Diamonds_Team.h"
    #include "text/Text_Diamonds_Alone.h"
    #include "text/Text_Hearts_Team.h"
    #include "text/Text_Hearts_Alone.h"

    #include "Dialogue_Alone.h"
    #include "Dialogue_Alone_Spades.h"
    #include "Dialogue_Alone_Clubs.h"
    #include "Dialogue_Alone_Diamonds.h"
    #include "Dialogue_Alone_Hearts.h"
 
    #include "Dialogue_Go.h"
    #include "Dialogue_Go_Spades.h"
    #include "Dialogue_Go_Clubs.h"
    #include "Dialogue_Go_Diamonds.h"
    #include "Dialogue_Go_Hearts.h"

    #include "Dialogue_Pass.h"
    #include "Dialogue_Pass_Disabled.h"
    #include "Dialogue_Small_Background.h"
    #include "Dialogue_Large_Background.h"

    #include "selection/CheckBox_Checked.h"
    #include "selection/CheckBox_Checked_Selected.h"
    #include "selection/CheckBox_Checked_Disabled.h"
    #include "selection/CheckBox_Empty.h"
    #include "selection/CheckBox_Empty_Selected.h"
    #include "selection/CheckBox_Empty_Disabled.h"
    #include "selection/OnePlayer.h"
    #include "selection/OnePlayer_Selected.h"
    #include "selection/TwoPlayer.h"
    #include "selection/TwoPlayer_Selected.h"
    #include "selection/StickIt.h"
    #include "selection/StickIt_Selected.h"
    #include "selection/ShowAll.h"
    #include "selection/ShowAll_Selected.h"
    #include "selection/ShowWinner.h"
    #include "selection/ShowWinner_Selected.h"

    #include "selection/Seat_Bot.h"
    #include "selection/Seat_Bot_Disabled.h"
    #include "selection/Seat_Left.h"
    #include "selection/Seat_Left_Disabled.h"
    #include "selection/Seat_Top.h"
    #include "selection/Seat_Top_Disabled.h"
    #include "selection/Seat_Right.h"
    #include "selection/Seat_Right_Disabled.h"

    #include "selection/Position1.h"
    #include "selection/Position1_Selected.h"
    #include "selection/Position1_Disabled.h"
    #include "selection/Position2.h"
    #include "selection/Position2_Selected.h"
    #include "selection/Position2_Disabled.h"
    #include "selection/Position3.h"
    #include "selection/Position3_Selected.h"
    #include "selection/Position3_Disabled.h"

    #include "endOfGame/EOG_01.h"
    #include "endOfGame/EOG_02.h"
    #include "endOfGame/EOG_04.h"
    #include "endOfGame/Euchre.h"
    #include "endOfGame/March.h"
    #include "endOfGame/TeamAlpha.h"
    #include "endOfGame/TeamBeta.h"

    #include "endOfGame/MinusTwo_00.h"
    #include "endOfGame/MinusTwo_01.h"
    #include "endOfGame/MinusTwo_02.h"
    #include "endOfGame/MinusTwo_03.h"
    #include "endOfGame/MinusTwo_04.h"

    #include "endOfGame/PlusOne_00.h"
    #include "endOfGame/PlusOne_01.h"
    #include "endOfGame/PlusOne_02.h"
    #include "endOfGame/PlusOne_03.h"
    #include "endOfGame/PlusOne_04.h"

    #include "endOfGame/PlusTwo_00.h"
    #include "endOfGame/PlusTwo_01.h"
    #include "endOfGame/PlusTwo_02.h"
    #include "endOfGame/PlusTwo_03.h"
    #include "endOfGame/PlusTwo_04.h"

    #include "endOfGame/PlusFour_00.h"
    #include "endOfGame/PlusFour_01.h"
    #include "endOfGame/PlusFour_02.h"
    #include "endOfGame/PlusFour_03.h"
    #include "endOfGame/PlusFour_04.h"

    const uint8_t * const Text_Suits_Team[] = { 
        Text_Spades_Team,
        Text_Clubs_Team,
        Text_Diamonds_Team,
        Text_Hearts_Team,
    };

    const uint8_t * const Text_Suits_Alone[] = { 
        Text_Spades_Alone,
        Text_Clubs_Alone,
        Text_Diamonds_Alone,
        Text_Hearts_Alone,
    };

    const uint8_t * const Text_Alones[] = { 
        Dialogue_Alone_Spades,
        Dialogue_Alone_Clubs,
        Dialogue_Alone_Diamonds,
        Dialogue_Alone_Hearts,
    };

    const uint8_t * const Text_Go[] = { 
        Dialogue_Go_Spades,
        Dialogue_Go_Clubs,
        Dialogue_Go_Diamonds,
        Dialogue_Go_Hearts,
    };

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

