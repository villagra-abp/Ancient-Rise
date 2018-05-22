#ifndef GESTORSONIDO_H
#define GESTORSONIDO_H

//#include <fmod_studio.hpp>
//#include <fmod.hpp>
//#include <fmod_errors.h>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include<vector>

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
		bool playRandomSound(vector<Sonido*> lista);
		void update();



		GrupoCanales* getMasterGroup();
		GrupoCanales* getGrupoMusica();
		GrupoCanales* getGrupoAmbiente();
		GrupoCanales* getGrupoVoces();

		void setListener(float x, float y, float z);

//		const char* SOUND_ = "resources/sonido/.wav"; 
		//Sonidos prota
		const char* SOUND_PROTA_ATAQUE1 = "resources/sonido/prota/PGrito_Ataque1.wav"; 
		const char* SOUND_PROTA_ATAQUE2 = "resources/sonido/prota/PGrito_Ataque2.wav"; 
		const char* SOUND_PROTA_ATAQUE3 = "resources/sonido/prota/PGrito_Ataque3.wav"; 
		const char* SOUND_PROTA_DOLOR1 = "resources/sonido/prota/PGrito_Dolor1.wav"; 
		const char* SOUND_PROTA_DOLOR2 = "resources/sonido/prota/PGrito_Dolor2.wav"; 
		const char* SOUND_PROTA_DOLOR3 = "resources/sonido/prota/PGrito_Dolor3.wav"; 
		const char* SOUND_PROTA_MUERTE1 = "resources/sonido/prota/PGrito_Muerte1.wav"; 
		const char* SOUND_PROTA_MUERTE2 = "resources/sonido/prota/PGrito_Muerte2.wav"; 
		const char* SOUND_PROTA_PASOS = "resources/sonido/prota/pasosPiedra.wav";
		const char* SOUND_PROTA_COMER = "resources/sonido/prota/comer.wav"; 
		const char* SOUND_PROTA_BEBER = "resources/sonido/prota/beber.wav";

		//Sonidos enemigo
		const char* SOUND_ENEM_ATAQUE1 = "resources/sonido/enemigo/Grito_Ataque1.wav"; 
		const char* SOUND_ENEM_ATAQUE2 = "resources/sonido/enemigo/Grito_Ataque2.wav"; 
		const char* SOUND_ENEM_ATAQUE3 = "resources/sonido/enemigo/Grito_Ataque3.wav"; 
		const char* SOUND_ENEM_DOLOR1 = "resources/sonido/enemigo/Grito_Dolor1.wav"; 
		const char* SOUND_ENEM_DOLOR2 = "resources/sonido/enemigo/Grito_Dolor2.wav"; 
		const char* SOUND_ENEM_DOLOR3 = "resources/sonido/enemigo/Grito_Dolor3.wav"; 
		const char* SOUND_ENEM_MUERTE1 = "resources/sonido/enemigo/Muerte1.wav"; 
		const char* SOUND_ENEM_MUERTE2 = "resources/sonido/enemigo/Muerte2.wav"; 

		//Sonidos musica
		const char* SOUND_MUSIC_MENU = "resources/sonido/musica/Musica-Menu.wav";
		const char* SOUND_MUSIC_NIVEL1 = "resources/sonido/musica/Musica-Fuga.wav";
		const char* SOUND_MUSIC_NIVEL2 = "resources/sonido/musica/Musica-CiudadNoche.wav";
		const char* SOUND_MUSIC_NIVEL3 = "resources/sonido/musica/Musica-CiudadDia.wav";
		const char* SOUND_MUSIC_MUERTE = "resources/sonido/musica/Musica-Cueva.wav";

		//Sonidos ambiente
		const char* SOUND_AMBIENT_CORTECARNE = "resources/sonido/ambiente/corteCarne.wav";

		const char* SOUND_BOSS3_NANI = "resources/sonido/pasos1.wav";
		const char* SOUND_BOSS3_OMAE = "resources/sonido/salto1.wav";
//		const char* SOUND_BOSS3_RISA = "resources/sonido/boss3/boss3_risa.wav";
//		const char* SOUND_BOSS3_GRITO1 = "resources/sonido/boss3/boss3_grito1.wav";
		const char* SOUND_MUSIC_BOSQUE = "resources/sonido/bs/musica_bosque.mp3";
		const char* SOUND_TRAP_ALARM = "resources/sonido/CampanaFINEDIT.wav";

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