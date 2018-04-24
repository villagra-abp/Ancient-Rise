#include "../headerfiles/TAnimacion.h"

TAnimacion::TAnimacion(){
	visible = true;
	time = 0;
	time(&now);
	gestor = TGestorRecursos::getInstace();
}

void TAnimacion::cargarAnimacion(string path){
	animacion = gestor->getRecursoAnimacion(path);
	duracion = animacion->getDuracion();
}

void TAnimacion::beginDraw(TDatosEntidad *datos){
	if(visible){
		int frame = getFrame();

		animacion->draw(mmodelo, datos, frame); // (...) //Dibujado del recurso de malla OpenGL
	}

}

void TAnimacion::endDraw(){


}



int TAnimacion::getFrame(){
	int malla, auxTime;

	time += getTime();
	while(time > duracion)					//Si se ha superado la duracion de la animacion se inicia desde 0
		time -= duracion;
	
	malla = -1;
	auxTime =time;									//Comprobamos en qué punto de la animación se encuentra
	do{
		malla++;
		auxTime -= dMalla;
	} while( auxTime > dMalla)

	return malla;			//Devolvemos el frame que toca

}


float TAnimacion::getTime(){			//Devuelve los segundos desde la ultima vez que se llamo a este metodo
	double elapsed;
	now = time();
	elapsed = difftime(now, antes);
	antes = now;

	return (float) elapsed;

}
