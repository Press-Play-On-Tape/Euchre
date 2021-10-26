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
        GameState gameState = GameState::Splash;
        GameState nextState = GameState::None;
        GameCookie *cookie;
        Deck deck;
        Hand hands[4];
        GameStatus gameStatus;


        uint8_t counter;
        uint8_t deal;
        uint8_t threshold;
        uint8_t bidCursor;
        uint8_t dialogCursor;
        Card dealerCard;
        

        const uint8_t *text = nullptr;

    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen();
        void title_Init();
        void title();
        void game_Init();
        void game();
        void selection_Init();
        void selection();
        
        void incMode();
        void print();
        bool handlePlayerBid(uint8_t playerIdx);
        void handlePlayerSecondBid(uint8_t playerIdx);  
        uint8_t handleDiscardACard(uint8_t playerIdx);  
        uint8_t handlePlayACard(uint8_t playerIdx, CardSuit suitLed = CardSuit::None);  
        uint8_t bidWinner();

        void renderGame();
        void renderBids();
        void renderPlayerBid();
        void renderPlayerSecondBid();
        void renderDiscardACard();
        void renderPlayACard();
        void renderSoreboard(uint8_t winner, bool showTrick, bool showHand);
        void renderTrumps(CardSuit trumps);
        bool doSecondBid(uint8_t handNumber);
        void renderSuit(CardSuit suit);
        void renderTrickOver(uint8_t winner);
        void renderHandOver(uint8_t winner);
        void renderFinalBid();
        void renderCard(Orientation orientation, Card card, int16_t x, int16_t y, bool highlight, bool raise, bool showCards);
        
};

