#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		//SoundEffects sfx = SoundEffects::Both;

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			//this->sfx = SoundEffects::Both;
			this->saveCookie();

		}

};