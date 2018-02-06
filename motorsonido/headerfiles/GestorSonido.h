#ifndef GESTORSONIDO_H
#define GESTORSONIDO_H

//#include <fmod_studio.hpp>
//#include <fmod.hpp>
//#include <fmod_errors.h>
#include <cstddef>
#include <cstdio>
#include <iostream>

#include "GestorErrores.h"
#include "GrupoCanales.h"
#include "Sonido.h"
#include "Canal.h"
#include "Reverb.h"

using namespace std;

class GestorSonido{
	public:

		virtual ~GestorSonido();

		static GestorSonido* getInstance();


		GrupoCanales* createGrupoCanales();
		GrupoCanales* createGrupoCanales(const char* name);
		Sonido* create2DSound(const char* name);
		Sonido* create3DSound(const char* name);
		Reverb* create3DReverb();
		DSP*	createDSP(const char* tipo);
		Sonido* createMusic(const char* name);
		bool playSound(Sonido* sonido);
		void update();

		GrupoCanales* getMasterGroup();
		GrupoCanales* getGrupoMusica();
		GrupoCanales* getGrupoAmbiente();
		GrupoCanales* getGrupoVoces();

		void setListener(float x, float y, float z);


		const char* SOUND_BOSS3_NANI = "resources/sonido/boss3/boss3_NANI.wav";
		const char* SOUND_BOSS3_OMAE = "resources/sonido/boss3/boss3_omaewa.wav";
		const char* SOUND_BOSS3_RISA = "resources/sonido/boss3/boss3_risa.wav";
		const char* SOUND_BOSS3_GRITO1 = "resources/sonido/boss3/boss3_grito1.wav";
		const char* SOUND_MUSIC_BOSQUE = "resources/sonido/bs/musica_bosque.mp3";

		//Tipos de rever
		const char* REVERB_CUEVA = "cueva";
		const char* REVERB_CIUDAD = "ciudad";
		const char* REVERB_BOSQUE = "bosque";
		const char* REVERB_HABITACION = "habitacion";

		const float DISTANCEFACTOR = 1.0f;          // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.


	private:
		GestorSonido();

		FMOD::Studio::System* system;
		FMOD::System* syslow;

		FMOD_RESULT result;

		int num = 0;

		const int CANALES = 32;
		FMOD::Channel** channels;

		FMOD::Sound *sound;
		FMOD::Reverb3D* reverb;

		GrupoCanales* master;
		GrupoCanales* voces;
		GrupoCanales* ambiente;
		GrupoCanales* musica;

};

#endif //GestorSOnido_H