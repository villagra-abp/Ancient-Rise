#include "../headerfiles/FObjeto.h"

//Original

FObjeto::FObjeto(){
	padre = TMotorTAG::getInstance()->getEscena();
	//TNodo* nodo, rotacion, traslacion;

//	nodo = new TNodo();
//	rotacion = new TNodo();
//	traslacion = new TNodo();
//
//	padre->addHijoBack(rotacion);
//	rotacion->addHijoBack(traslacion);
//	traslacion->addHijoBack(nodo);
//
//	TTransf* rot = new TTransf();
//	TTransf* tras = new TTransf();
//	TMalla* mesh = new TMalla();
//
//
//	rotacion->setEntidad(rot);
//	traslacion->setEntidad(tras);
//	nodo->setEntidad(mesh);

	nodo = new TNodo();
	escalado = new TNodo();
	rotacion = new TNodo();
	traslacion = new TNodo();

//	padre->addHijoBack(escalado);
//	escalado->addHijoBack(rotacion);
//	rotacion->addHijoBack(traslacion);
	padre->addHijoBack(rotacion);
	rotacion->addHijoBack(escalado);
	escalado->addHijoBack(traslacion);
	traslacion->addHijoBack(nodo);

	TTransf* esc = new TTransf();
	TTransf* rot = new TTransf();
	TTransf* tras = new TTransf();
	TMalla* mesh = new TMalla();

	escalado->setEntidad(esc);
	rotacion->setEntidad(rot);
	traslacion->setEntidad(tras);
	nodo->setEntidad(mesh);



	active = true;
	esAnimacion = false;
}

FObjeto::~FObjeto(){
	traslacion->remHijoChange(nodo,padre);
	padre->remHijoAll(rotacion);
}

//Rota el objeto teniendo en cuenta la rotacion previa
void FObjeto::Rotar(vec3 rot, float ang){
	dynamic_cast<TTransf*>(rotacion->getEntidad())->rotar(rot.x, rot.y, rot.z, ang);
}

void FObjeto::Escalar(vec3 esc){
	dynamic_cast<TTransf*>(escalado->getEntidad())->escalar(esc.x, esc.y, esc.z);
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

void FObjeto::reiniciarAnimacion(){
	if(esAnimacion){
//		TAnimacion* anim = dynamic_cast<TAnimacion*>(nodo->getEntidad());
//		cout<<anim->returnTime()<<" ";
		dynamic_cast<TAnimacion*>(nodo->getEntidad())->setTimeZero();
//		cout<<anim->returnTime()<<endl;
	}
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
	TMalla* mesh = new TMalla();
	nodo->setEntidad(mesh);
	dynamic_cast<TMalla*>(nodo->getEntidad())->cargarMalla(path);
	esAnimacion = false;

}

void FObjeto::setMaterial(string nombre){

	dynamic_cast<TMalla*>(nodo->getEntidad())->setMaterial(nombre);
	//Anyadir errores si no existe material

}

void FObjeto::setAnimacion(string path){
	TAnimacion* mesh = new TAnimacion();
	nodo->setEntidad(mesh);
	dynamic_cast<TAnimacion*>(nodo->getEntidad())->cargarAnimacion(path);


	esAnimacion = true;
}

