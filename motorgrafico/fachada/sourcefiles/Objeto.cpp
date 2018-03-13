#include "../headerfiles/Objeto.h"


Objeto::Objeto(){
	padre = TMotorTAG::getInstance()->getEscena();
	TNodo* malla, rotacion, traslacion;

	malla = new TNodo();
	rotacion = new TNodo();
	traslacion = new TNodo();

	padre->addHijoBack(rotacion);
	rotacion->addHijoBack(traslacion);
	traslacion->addHijoBack(malla);

	TTransf* rot = new TTransf();
	TTransf* tras = new TTransf();
	TMalla* mesh = new TMalla();


	rotacion->setEntidad(rot);
	traslacion->setEntidad(tras);
	malla->setEntidad(mesh);



	visible = true;
}

Objeto::~Objeto(){

}

//Rota el objeto teniendo en cuenta la rotacion previa
void Objeto::Rotar(vec3 rotacion, float angulo){
	rotacion->getEntidad()->rotar(rotacion.x, rotacion.y, rotacion.z, angulo);
}

void Objeto::Escalar(vec3 escalado){

}

//Mueve el objeto teniendo en cuenta la posicion previa
void Objeto::Mover(vec3 posicion){
	traslacion->getEntidad()->trasladar(posicion.x,posicion.y, posicion.z);
}

//Cambia la posicion del objeto en funcion del origen de coordenadas
void Objeto::setPosicion(vec3 posicion){
	traslacion->getEntidad()->setPosition(posicion.x, posicion.y. posicion.z);
}

//Cambia la rotacion sin tener en cuenta la rotacion previa
void Objeto::setRotacion(vec3 rotacion, float angulo){
	rotacion->getEntidad()->setRotation(rotacion.x, rotacion.y, rotacion.z, angulo);
}

//Cambia el booleano visible al proporcionado, modificando si se dibuja o no el objeto
void Objeto::isVisible(bool flag){
	malla->getEntidad()->isVisible(flag);
}

//Cambia el padre del objeto a otro objeto, asociandolo tambien a las transformaciones que sufre el nuevo padre
void Objeto::Unir(Objeto* nPadre){
	padre->changePadre(nPadre, rotacion);
}


TNodo* Objeto::getNodo(){
	return malla;
}

void Objeto::setMalla(string path){
	malla->cargarMalla(path);
}


