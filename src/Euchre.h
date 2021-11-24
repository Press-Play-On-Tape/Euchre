#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include <LibSchedule>
#include "entities/Entities.h"
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/GameCookie.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        SplashScreenVariables splashScreenVariables;
        TitleScreenVariables titleScreenVariables;
        
        GameState gameState = GameState::Splash_Init;
        GameState nextState = GameState::None;
        GameState savedState = GameState::None;
        GameCookie *cookie;
        Deck deck;
        Hand hands[4];
        GameStatus gameStatus;
        SwapCaption swapCaption;

        uint8_t counter;
        uint8_t deal;
        uint8_t upperThreshold;
        uint8_t threshold;
        uint8_t bidCursor;
        uint8_t dialogCursor;
        uint8_t tapeCursor;
        uint16_t eog;
        Card dealerCard;

        const uint8_t *text = nullptr;

        File mainThemeFile;
        File soundEffectFile;
        File instructionFile;  

    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen_Init();
        void splashScreen();
        void title_Init();
        void title();
        void game_Init();
        void game();
        void selection_Init();
        void selection();
        void swap_Init();
        void swap();
        void pause_Init();
        void pause();
        void instructions_Init();
        void instructions();
        
        void incMode(bool ignoreCounter = false, bool increasePlayer = true);
        void print();
        bool handlePlayerBid(uint8_t playerIdx);
        void handlePlayerSecondBid(uint8_t playerIdx);  
        uint8_t handleDiscardACard(uint8_t playerIdx);  
        uint8_t handlePlayACard(uint8_t playerIdx, CardSuit suitLed = CardSuit::None);  
        uint8_t bidWinner();
        bool isPlayingThisHand(uint8_t playerIdx);
        bool isHuman(uint8_t playerIdx);

        void renderGame(bool pause);
        void renderPlayedCard(uint8_t x, uint8_t y, uint8_t position);
        void renderBids(uint8_t positions[4]);
        void renderPlayerBid();
        void renderPlayerSecondBid();
        void renderDiscardACard();
        void renderPlayACard();
        void renderSoreboard(uint8_t tricksWinner, uint8_t pointsWinner, bool showTrick, bool showHand);
        void renderTrumps(CardSuit trumps);
        void renderGameOver_Alpha();
        void renderGameOver_Beta();

        bool doSecondBid(uint8_t handNumber);
        void renderTrickOver(uint8_t positions[4], uint8_t winner);
        void renderHandOrGameOver(uint8_t winner);
        void renderFinalBid(uint8_t positions[4]);
        void renderCard(Orientation orientation, Card card, int16_t x, int16_t y, bool raise, bool showCards, CardMode cardMode);
        void playSpeech(Speech speech);
        void playTheme(uint8_t themeNumber);
        void muteTheme();
        void getSwapCaption(GameState gameState);
        void firstValidCard(uint8_t playerIdx);
};

