#ifndef ALARMASONANDO_H
#define ALARMASONANDO_H

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <cstddef>
#include <cstdio>
#include <iostream>


class Sonido{
	public:
		virtual ~Sonido();

		static Sonido* getInstance();

		void update();
		void playSound(const char* name);

		const char* SOUND_BOSS3_NANI = "resources/sonido/boss3/boss3_NANI.wav";
		const char* SOUND_BOSS3_OMAE = "resources/sonido/boss3/boss3_omaewa.wav";
		const char* SOUND_BOSS3_RISA = "resources/sonido/boss3/boss3_risa.wav";
		const char* SOUND_BOSS3_GRITO1 = "resources/sonido/boss3/boss3_grito1.wav";


	private:
		Sonido();

		FMOD::Studio::System* fmod;
		FMOD::System* fmodlow;

		FMOD_RESULT result;

		const int CANALES = 16;
		FMOD::Channel** channels;

		FMOD::Sound *sound;

};

#endif //ALARMASONANDO_H