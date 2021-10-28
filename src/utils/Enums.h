#pragma once

#define DEBUG
#define SOUNDS
#define COOKIE_INITIALISED 66

namespace Cards {

    constexpr uint8_t Two = 0;
    constexpr uint8_t Three = 1;
    constexpr uint8_t Four = 2;
    constexpr uint8_t Five = 3;
    constexpr uint8_t Six = 4;
    constexpr uint8_t Seven = 5;
    constexpr uint8_t Eight = 6;
    constexpr uint8_t Nine = 7;
    constexpr uint8_t Ten = 8;
    constexpr uint8_t Jack = 9;
    constexpr uint8_t Queen = 10;
    constexpr uint8_t King = 11;
    constexpr uint8_t Ace = 12;

    constexpr uint8_t NoCard = 255;
    constexpr uint8_t RightBower = 150;
    constexpr uint8_t LeftBower = 149;
    constexpr uint8_t TrumpsStart = 78;
    constexpr uint8_t TrumpsEnd = 78 + 13;

}

namespace Constants {

    constexpr uint8_t MaxNumberOfCards[] = { 0, 8, 7, 6, 5 };
    constexpr uint8_t AllWinners = 5;
    constexpr uint8_t BidDialogueDelay = 30;
    constexpr uint8_t Dialogue_00_Y = 134;
    constexpr uint8_t NoPlayer = 4;

    constexpr uint8_t EOGText_X = 32;
    constexpr uint8_t EOGText_Y = 40;   
    constexpr uint8_t EOGPoints_X = 120;
    constexpr uint8_t EOGPoints_Y = 60;   

}

enum class GameState : uint8_t {
    Splash_Init,            // 0
    Splash,                 // 1    
    Title_Init,             // 2
    Title,                  // 3
    Game_Init,              // 4
    Game_NewHand_Init,      // 5
    Game_NewHand_00,        // 6
    Game_NewHand_01,        // 7
    Game_NewHand_02,        // 8
    Game_NewHand_03,        // 9
    Game_NewHand_04,        // 10
    Game_NewHand_05,        // 11
    Game_NewHand_06,        // 12
    Game_NewHand_07,        // 13
    Game_NewHand_08,        // 14
    Game_NewHand_09,        // 15
    Game_NewHand_10,        // 16
    Game_NewHand_11,        // 17
    Game_NewHand_12,        // 18
    Game_NewHand_13,        // 19
    Game_NewHand_14,        // 20
    Game_NewHand_15,        // 21
    Game_NewHand_16,        // 22
    Game_NewHand_17,        // 23
    Game_NewHand_18,        // 24
    Game_NewHand_19,        // 25
    Game_DealerCard,        // 26
    Game_Bid_00,            // 27
    Game_Bid_01,            // 28
    Game_Bid_02,            // 29
    Game_Bid_03,            // 30
    Game_Open_Bid_00,       // 31
    Game_Open_Bid_01,       // 32
    Game_Open_Bid_02,       // 33
    Game_Open_Bid_03,       // 34
    Game_DealerExtraCard,   // 35
    Game_StartPlay,         // 36
    Game_LeadCard,          // 37
    Game_Follow_01,         // 38
    Game_Follow_02,         // 39
    Game_Follow_03,         // 40
    Game_EndOfTrick,        // 41
    Game_EndOfHand,         // 42
    Game_Xxx,               // 43
    Selection_Init,         // 44
    Selection,              // 45
    None,                   // 46
};


inline GameState &operator++(GameState &c ) {
    c = static_cast<GameState>(static_cast<uint8_t>(c) + 1);
    return c;
}

inline GameState operator++(GameState &c, int ) {
    GameState result = c;
    ++c;
    return result;
}

inline GameState &operator--(GameState &c ) {
    c = static_cast<GameState>(static_cast<uint8_t>(c) - 1);
    return c;
}

inline GameState operator--(GameState &c, int ) {
    GameState result = c;
    --c;
    return result;
}


enum class CardSuit : uint8_t {
    Spades,
    Clubs,
    Diamonds,
    Hearts,
    None,
};

enum class CallStatus : uint8_t {
    None,
    Pass,
    FirstRound,
    SecondRound,
};

enum class HasSuit : uint8_t {
    Unknown,
    True,
    False,
};

enum class Orientation : uint8_t {
    Bottom,
    Left,
    Top,
    Right
};