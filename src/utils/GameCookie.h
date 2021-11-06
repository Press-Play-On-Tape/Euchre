#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"


class GameCookie : public Pokitto::Cookie {

	public:

        uint8_t initialised;

	private:

        bool stickIt = false;
        bool showHands = true;
        bool showWinner = true;
        bool highlightPlayable = true;

        uint8_t numberOfPlayers;
        uint8_t player2Pos = 1;
        uint8_t track = 0;

        SoundEffects sfx = SoundEffects::Both;                

	public:

        bool getShowHands()                                         { return this->showHands; }    
        bool getStickIt()                                           { return this->stickIt; }    
        bool getShowWinner()                                        { return this->showWinner; }    
        bool getHighlightPlayable()                                 { return this->highlightPlayable; }    
        uint8_t getPlayer2Pos()                                     { return this->player2Pos; }    
        uint8_t getNumberOfPlayers()                                { return this->numberOfPlayers; }    
        uint8_t getTrack()                                          { return this->track; }    
        SoundEffects getSFX()                                       { return this->sfx; }

        void setShowHands(bool val)                                 { this->showHands = val; }
        void setStickIt(bool val)                                   { this->stickIt = val; }
        void setShowWinner(bool val)                                { this->showWinner = val; }
        void setHighlightPlayable(bool val)                         { this->highlightPlayable = val; }
        void setNumberOfPlayers(uint8_t val)                        { this->numberOfPlayers = val; }
        void setPlayer2Pos(uint8_t val)                             { this->player2Pos = val; }
        void setTrack(uint8_t val)                                  { this->track = val; }
        void setSFX(SoundEffects val)                               { this->sfx = val; }

	public:

		void initialise() {

            this->initialised = COOKIE_INITIALISED;
            this->stickIt = false;
            this->showHands = true;
            this->showWinner = true;
            this->highlightPlayable = true;
            this->player2Pos = 1;
            this->track = 1;
            this->numberOfPlayers = 1;
			this->sfx = SoundEffects::Both;

            this->saveCookie();

		}

        void incSFX() {

            this->sfx++;

        }

        void decSFX() {

            this->sfx--;

        }

};