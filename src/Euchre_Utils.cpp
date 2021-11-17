#include "Euchre.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::playSpeech(Speech speech) {

    #ifdef SOUNDS
                           //012345678901234567
    char sounds[40][19] = { "music/Euch_000.raw", "music/Euch_001.raw", "music/Euch_002.raw", "music/Euch_003.raw",
                            "music/Euch_010.raw", "music/Euch_011.raw", "music/Euch_012.raw", "music/Euch_013.raw",
                            "music/Euch_020.raw", "music/Euch_021.raw", "music/Euch_022.raw", "music/Euch_023.raw",
                            "music/Euch_030.raw", "music/Euch_031.raw", "music/Euch_032.raw", "music/Euch_033.raw",
                            "music/Euch_040.raw", "music/Euch_041.raw", "music/Euch_042.raw", "music/Euch_043.raw",
                            "music/Euch_050.raw", "music/Euch_051.raw", "music/Euch_052.raw", "music/Euch_053.raw",
                            "music/Euch_060.raw", "music/Euch_061.raw", "music/Euch_062.raw", "music/Euch_063.raw",
                            "music/Euch_070.raw", "music/Euch_071.raw", "music/Euch_072.raw", "music/Euch_073.raw",
                            "music/Euch_800.raw", "music/Euch_801.raw", "music/Euch_802.raw", "music/Euch_803.raw",
                            "music/Euch_804.raw", "music/Euch_805.raw", "music/Euch_080.raw", "music/Euch_081.raw"
    };

    uint8_t index = static_cast<uint8_t>(speech);

    if (this->soundEffectFile.openRO(sounds[index])) {

        auto& music = Audio::play<1>(this->soundEffectFile);
        music.setLoop(false);

    }

    #endif

}

void Game::playTheme(uint8_t themeNumber) {

    #ifdef SOUNDS

    char theme[3][19] = { "music/Euch_900.raw", "music/Euch_901.raw", "music/Euch_902.raw" };

    if (this->mainThemeFile.openRO(theme[themeNumber])) {
        auto& music = Audio::play<0>(this->mainThemeFile);
        music.setLoop(true);
    }

    #endif

}


void Game::muteTheme() {

    #ifdef SOUNDS
    Audio::stop<0>();
    #endif

}
