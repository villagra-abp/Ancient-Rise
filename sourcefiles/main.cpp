

#include "../motorgrafico/headerfiles/Motorgrafico.h"
#include "../motorgrafico/headerfiles/Objeto.h"
#include "../motorgrafico/headerfiles/Mapa.h"
#include "../motorgrafico/headerfiles/Camara.h"
#include "../motorgrafico/headerfiles/Vector3D.h"
//#include "../motorgrafico/sourcefiles/Motorgrafico.cpp"

#include <iostream>
#include <Box2D/Box2D.h>


using namespace std;
using namespace io;


/*
This is the main method. We can now use main() on every platform.
*/
int main()
{

	const path mapa = "resources/media/map-20kdm2.pk3";


	Motorgrafico* grafico = Motorgrafico::getInstance();


	string s = "Mapas";
	grafico->setNombreVentana(s);


	grafico->cursorVisible(false);

	Mapa* mapita = new Mapa(mapa);
	mapita->setPosicion(-1300,-144,-1249);

	Camara* camara = new Camara(1);

	Objeto* cubo = new Objeto(0);
	Objeto* esfera = new Objeto(1);

	Vector3D v(0,0,30);

	cubo->setPosicion(v);
	v.Z = 60;
	esfera->setPosicion(v);

	cubo->setMaterial("resources/media/wall.bmp");
	esfera->setMaterial("resources/media/wall.bmp");

	cubo->setLuz(false);
	esfera->setLuz(false);

	int lastFPS = -1;
	u32 then = grafico->getTime();

	const f32 MOVEMENT_SPEED= 100.f;

	while(grafico->getVentanaEstado()){
		if (grafico->getVentanaActiva()){
			const u32 now = grafico->getTime();
			const f32 frameDeltaTime = (f32)(now-then) / 1000.f; //Time in seconds
			then = now; 
			
			Vector3D nodePosicion = camara->getPosicion();
			Vector3D nodeRotation = camara->getRotation();

			Eventlistener receiver = grafico->getListener();
			if(receiver.IsKeyDown('w')){
				nodePosicion.Z += MOVEMENT_SPEED * frameDeltaTime;
			}
			else if(receiver.IsKeyDown('s')){
				nodePosicion.Z -= MOVEMENT_SPEED * frameDeltaTime;
			}

			if(receiver.IsKeyDown('a')){
				nodeRotation.Y -= MOVEMENT_SPEED*frameDeltaTime;
			}
			else if(receiver.IsKeyDown('d'))
				nodeRotation.Y += MOVEMENT_SPEED*frameDeltaTime;
			if(receiver.IsKeyDown(3)){
				grafico->cerrar();
			}
			camara->setPosicion(nodePosicion);
			camara->setRotation(nodeRotation);
			
			grafico->draw(255,200,200,200);

			int fps = grafico->getFPS();

			if(lastFPS != fps){
				string str = "Irrlicht Engine - Quake 3 Map example FPS:";
				str += to_string(fps);
	
				grafico->setNombreVentana(str);
				lastFPS = fps;
			}
		} else{
			grafico->suspension();
		}
		
	}
   
	
	delete grafico;
	delete mapita;
	delete camara;

	return 0;
}

