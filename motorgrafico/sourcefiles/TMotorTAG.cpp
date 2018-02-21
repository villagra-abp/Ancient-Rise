#include "../headerfiles/TMotorTAG.h"

TMotorTAG::TMotorTAG() : escena(nullptr)
{

}
TMotorTAG::~TMotorTAG(){
	delete escena;
	escena = nullptr;
}

TNodo* TMotorTAG::crearNodo(TNodo *padre, TEntidad *ent){
	TNodo* nodo = new TNodo();
	
	if(ent!=nullptr){
		nodo->setEntidad(ent);
		if(ent->getTipo()==3){
			regCam.push_back(nodo);
			estadoCam.push_back(false);
			setCamara((TCamara*)ent, true);
		}
		else if(ent->getTipo()==2){
			regLuz.push_back(nodo);
			estadoLuz.push_back(true);
		}
	}

	if(padre!=nullptr)
		padre->addHijoBack(nodo);
	else
		escena = nodo;

	return nodo;
}
TTransf* TMotorTAG::crearTransf(){
	TTransf* transf = new TTransf();

	return transf;
}
TCamara* TMotorTAG::crearCamara(){
	TCamara* camara = new TCamara();

	return camara;
}
TLuz* TMotorTAG::crearLuz(){
	TLuz* luz = new TLuz();

	return luz;
}
TMalla* TMotorTAG::crearMalla(char *fichero){
	TMalla* malla =  new TMalla();

	return malla;
}
void TMotorTAG::draw(){
	//Obtener puntero camara activa del Registro de camaras
	for(int i = 0; i = regCam.size(); i++){
		if(estadoCam[i]){
			mVista = glm::inverse(generateMatrix(regCam[i]));
			i = regCam.size();
		}
	}

	//Obtener puntero luces activas del Registro de luces
	for(int i = 0; i = regLuz.size(); i++){
		if(estadoLuz[i]){
			pLuz.push_back(glm::vec4(0,0,0,1) * generateMatrix(regLuz[i]));
		}
	}

	//Iniciar secuencia draw del arbol
	escena->draw();
}
glm::mat4 TMotorTAG::generateMatrix(TNodo *nodo){
	//Obtendra la Matriz Modelo de un Nodo dado mediante
	//mediante un recorrido inverso de padre a padre.
	glm::mat4 mResultado = glm::mat4(1.0);
	vector<glm::mat4> mObtenidas;
	TNodo* nodoActual = nodo->getPadre();
	TTransf* entActual = nullptr;

	while(nodoActual != nullptr){
		entActual = (TTransf*)nodoActual->getEntidad();
		mObtenidas.push_back(entActual->getMatriz());
		nodoActual->getPadre();
	}

	if(mObtenidas.size()>0){
		for(int i = mObtenidas.size(); i > 0; i--){
			mResultado *= mObtenidas[i];
		}
	}

	return mResultado;
}
bool TMotorTAG::setCamara(TCamara* cam, bool b){
	bool z = false;

	bool hayCam = false;
	int pos = -1;

	if(b){
		for(int i = 0; i = regCam.size(); i++){
			if(estadoCam[i]){
				pos = i;
				estadoCam[i]=false;
			}
			if(regCam[i]->getEntidad()==cam){
				estadoCam[i]=true;
				hayCam = true;
			}
		}
		if(!hayCam)
			estadoCam[pos] = true;

		z=true;
	}	
	return z;
}
bool TMotorTAG::setLuz(TLuz* lz, bool b){
	bool z = false;

	for(int i = 0; i = regLuz.size(); i++){
		if(regLuz[i]->getEntidad()==lz){
			estadoLuz[i] = b;
			z=true;
		}
	}
	return z;
}