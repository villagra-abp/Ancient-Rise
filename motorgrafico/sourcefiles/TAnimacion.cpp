#include "../headerfiles/TAnimacion.h"

TAnimacion::TAnimacion(){
	visible = true;
	time = 0;
	now = steady_clock::now();
	gestor = TGestorRecursos::getInstance();
}

void TAnimacion::cargarAnimacion(string path){
	animacion = gestor->getRecursoAnimacion(path);
	duracion = animacion->getDuracion();
	dMalla = animacion->getDMalla();
	time = 0;  
}

void TAnimacion::beginDraw(TDatosEntidad *datos){
	if(visible){
		int frame = getFrame();
//		cout<<frame<<endl;

		animacion->draw(mmodelo, datos, frame); // (...) //Dibujado del recurso de malla OpenGL
	}

}

void TAnimacion::endDraw(){


}



int TAnimacion::getFrame(){
	int malla;
	double auxTime;

	time += getTime();

	while(time > duracion)					//Si se ha superado la duracion de la animacion se inicia desde 0
		time -= duracion;
	
	malla = 0;
	auxTime = time;									//Comprobamos en qué punto de la animación se encuentra


	while(auxTime>dMalla){
		malla++;
		auxTime -= dMalla;
	}

	return malla;			//Devolvemos el frame que toca

}


double TAnimacion::getTime(){			//Devuelve los segundos desde la ultima vez que se llamo a este metodo
	double elapsed;
	now = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(now - antes);
	elapsed = time_span.count();
	antes = now;

	return elapsed;

}

void TAnimacion::setTime(double tiempo){
	time = tiempo;
}

void TAnimacion::setTimeZero(){
	time = 0;
}

