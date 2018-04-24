#include "../headerfiles/FObjeto.h"


FObjeto::FObjeto(){
	padre = TMotorTAG::getInstance()->getEscena();
	//TNodo* nodo, rotacion, traslacion;

	nodo = new TNodo();
	rotacion = new TNodo();
	traslacion = new TNodo();

	padre->addHijoBack(rotacion);
	rotacion->addHijoBack(traslacion);
	traslacion->addHijoBack(nodo);

	TTransf* rot = new TTransf();
	TTransf* tras = new TTransf();
	TMalla* mesh = new TMalla();


	rotacion->setEntidad(rot);
	traslacion->setEntidad(tras);
	nodo->setEntidad(mesh);



	active = true;
}

FObjeto::~FObjeto(){
	traslacion->remHijoChange(nodo,padre);
	padre->remHijoAll(rotacion);
}

//Rota el objeto teniendo en cuenta la rotacion previa
void FObjeto::Rotar(vec3 rot, float ang){
	dynamic_cast<TTransf*>(rotacion->getEntidad())->rotar(rot.x, rot.y, rot.z, ang);
}

void FObjeto::Escalar(vec3 escalado){
	dynamic_cast<TTransf*>(rotacion->getEntidad())->escalar(escalado.x, escalado.y, escalado.z);
}

//Mueve el objeto teniendo en cuenta la posicion previa
void FObjeto::Mover(vec3 pos){
	dynamic_cast<TTransf*>(traslacion->getEntidad())->trasladar(pos.x,pos.y, pos.z);
}

//Cambia la posicion del objeto en funcion del origen de coordenadas
void FObjeto::setPosicion(vec3 pos){
	dynamic_cast<TTransf*>(traslacion->getEntidad())->setPosition(pos.x, pos.y, pos.z);
}

//Cambia la rotacion sin tener en cuenta la rotacion previa
void FObjeto::setRotacion(vec3 rot, float ang){
	dynamic_cast<TTransf*>(rotacion->getEntidad())->setRotation(rot.x, rot.y, rot.z, ang);
}

//Cambia el booleano visible al proporcionado, modificando si se dibuja o no el objeto
void FObjeto::isActive(bool flag){
	dynamic_cast<TMalla*>(nodo->getEntidad())->isVisible(flag);
	active = flag;
}

//Cambia el padre del objeto a otro objeto, asociandolo tambien a las transformaciones que sufre el nuevo padre
void FObjeto::Unir(FEntidad* nPadre){
	padre->changePadre(nPadre->getTraslacion(), rotacion);
	padre = nPadre->getNodo();
}

bool FObjeto::getActive(){
	return active;
}

TNodo* FObjeto::getNodo(){
	return nodo;
}

TNodo* FObjeto::getTraslacion(){
	return traslacion;
}

TNodo* FObjeto::getRotacion(){
	return rotacion;
}

vec3 FObjeto::getPosicion(){
	glm::vec3 pos = nodo->getPosicion();
	vec3 posicion = vec3(pos.x, pos.y, pos.z);
	return posicion;
}

void FObjeto::setMalla(string path){
	dynamic_cast<TMalla*>(nodo->getEntidad())->cargarMalla(path);
}

void FObjeto::setMaterial(string nombre){
	dynamic_cast<TMalla*>(nodo->getEntidad())->setMaterial(nombre);
	//Anyadir errores si no existe material

}

void FObjeto::setAnimacion(string path){
	dynamic_cast<TAnimacion*>(nodo->getEntidad())->setAnimacion(path);
}

