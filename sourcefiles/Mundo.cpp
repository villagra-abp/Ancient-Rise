#include "../headerfiles/Mundo.h"



Mundo::Mundo(sf::RenderWindow* mainDevice)	//CONSTRUCTOR
{

	 
	device = mainDevice;




	
/* CREAMOS PLATAFORMAS */



/** ESTABLECEMOS LA CAMARA
 Aqui indicamos la posicion de la camara en el espacio 3d. En este caso,
 esta mirando desde la posicion (0, 30, -40) a la (0, 5, 0) donde es
 aproximadamente donde esta el objeto.
**/

/* CREAMOS EL TERRENO Y COLISIONES DE CAMARA */

	
/** TIME AND FRAMES
 Para poder hacer un movimiento independiente del framerate, tenemos que saber
 cuanto ha pasado desde el ultimo frame
**/


}	

void Mundo::posBuilder(){	//CONSTRUCTOR DE POSICIONES DE ENEMIGOS

	
}

void Mundo::terrainBuilder(){	//CONSTRUCTOR DEL TERRENOS Y COLISIONES DE CAMARA

	
}

void Mundo::update(){
	

}

void Mundo::protaUpdate(const u32 now, const f32 frameDeltaTime, f32 tiempo){
	
}

void Mundo::camUpdate(const f32 frameDeltaTime){
	
}

void Mundo::fpsControl(){
	
	
}

void Mundo::timeWait(){
	
}

void Mundo::draw(){
	/*
	Anything can be drawn between a beginScene() and an endScene()
	call. The beginScene() call clears the screen with a color and
	the depth buffer, if desired. Then we let the Scene Manager and
	the GUI Environment draw their content. With the endScene()
	call everything is presented on the screen.
	*/

}
void Mundo::checkInput(){

	       
}

void Mundo::addGameObject (GameObject* o){
}

/*GameObject* Mundo::getGameObject(uint8_t pos) const{
	
}*/
Mundo::~Mundo()	//DESTRUCTOR
{
	
}
