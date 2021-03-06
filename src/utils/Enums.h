#pragma once

#define _DEBUG
#define _DEBUG_BID
#define _DEBUG_LEAD
#define _DEBUG_FOLLOW
#define _DEBUG_PLAY
#define _DEBUG_STATE
#define _DEBUG_SOUNDS
#define SOUNDS
#define COOKIE_INITIALISED 58

#define FADE_IN
#define FADE_IN_SLOW
#define _FADE_IN_FAST

enum Debug {
    None = 0,
    Bid = 1,
    Lead = 2,
    Follow = 4,
    Play = 8,
    State = 16,
    Sounds = 32
};           


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
    constexpr uint8_t Dialogue_EOH_Y = 156;
    constexpr uint8_t NoPlayer = 4;

    constexpr uint8_t WinningPoints = 10;
    constexpr uint8_t EOG_Delay = 90;

    constexpr uint8_t EOHText_X = 7;
    constexpr uint8_t EOHText_Y = 52;   

    constexpr uint8_t EOGText_X1 = 39;
    constexpr uint8_t EOGText_X21 = 23;
    constexpr uint8_t EOGText_X22 = 38;
    constexpr uint8_t EOGText_X3 = 38;
    constexpr uint8_t EOGText_Y1 = 24;   
    constexpr uint8_t EOGText_Y2 = 64;   
    constexpr uint8_t EOGText_Y3 = 104;   

    constexpr uint8_t EOGPoints_X = 141;
    constexpr uint8_t EOGPoints_Y = 95;   

    constexpr char instructions[5][19] = { 
        "music/Euch_910.raw", "music/Euch_911.raw", "music/Euch_912.raw", "music/Euch_913.raw",
        "music/Euch_914.raw", 
    };

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
    GameOver_Init,          // 43
    GameOver,               // 44
    Selection_Init,         // 45
    Selection,              // 46
    Swap_Init,              // 47
    Swap,                   // 48
    Pause_Init,             // 49
    Pause,                  // 50
    None,                   // 51
    Instructions_Init,      // 52
    Instructions_00,        // 53
    Instructions_01,        // 54
    Instructions_02,        // 55
    Instructions_03,        // 56
    Instructions_04,        // 57
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

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

inline SoundEffects &operator++(SoundEffects &c ) {
    c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline SoundEffects operator++(SoundEffects &c, int ) {
    SoundEffects result = c;
    ++c;
    return result;
}

inline SoundEffects &operator--(SoundEffects &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<SoundEffects>( 3 );
    }
    return c;
}

inline SoundEffects operator--(SoundEffects &c, int ) {
    SoundEffects result = c;
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

enum class Speech : uint8_t {
    Pass = 0,           
    Pass_01,
    Pass_02,
    Pass_03,
    TakeIt = 4,
    TakeIt_01,
    TakeIt_02,
    TakeIt_03,
    TakeItAlone = 8,
    TakeItAlone_01,
    TakeItAlone_02,
    TakeItAlone_03,
    Winner = 12,
    Winner_01,
    Winner_02,
    Winner_03,
    Mine = 16,
    Mine_01,
    Mine_02,
    Mine_03,
    Sorry = 20,
    Sorry_01,
    Sorry_02,
    Sorry_03,
    Trumped = 24,
    Trumped_01,
    Trumped_02,
    Trumped_03,
    WooHoo = 28,
    WooHoo_01,
    WooHoo_02,
    WooHoo_03,
    TeamAlphaPlus1 = 32,
    TeamAlphaPlus2,
    TeamAlphaPlus4,
    TeamBetaPlus1 = 35,
    TeamBetaPlus2,
    TeamBetaPlus4,
    TeamAlphaWins = 38,
    TeamBetaWins,
};

enum class SwapCaption : uint8_t {
    DiscardCard,
    LeadACard,
    FollowALead,
    YourBid,
    Redeal,
    None,
};           

enum class TitleScreenMode : uint8_t {
    Sounds,
    StartGame,
    Instructions,
};           

enum class CardMode : uint8_t {
    Normal,
    Disabled,
    Highlighted,
};           
