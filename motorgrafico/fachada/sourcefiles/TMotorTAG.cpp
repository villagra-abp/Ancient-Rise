#include "../headerfiles/TMotorTAG.h"

static TMotorTAG* fachadaMotor = nullptr;

TMotorTAG* TMotorTAG::getInstance(){
	if(fachadaMotor == nullptr){
		fachadaMotor = new TMotorTAG();
	} return fachadaMotor;
}

TMotorTAG::TMotorTAG() : camara(nullptr)
{
	escena = new TNodo();
}
TMotorTAG::~TMotorTAG(){
	delete escena;
	escena = nullptr;
}


void TMotorTAG::draw(){
	escena->draw(getCamaraMat(), getCamaraProj());
}


void TMotorTAG::activarCamara(TNodo* cam){
	if(camara != nullptr)
		dynamic_cast<TCamara*>(camara->getEntidad())->setActive(false);
	dynamic_cast<TCamara*>(cam->getEntidad())->setActive(false);
	camara = cam;
}

void TMotorTAG::registrarLuz(TLuz* luz){
	
}
/*
TNodo* TMotorTAG::crearNodo(TNodo *padre, TEntidad *ent){
	TNodo* nodo = new TNodo();
	
	if(ent!=nullptr){
		nodo->setEntidad(ent);
		if(ent->getTipo()=="camara"){
			regCam.push_back(nodo);
			estadoCam.push_back(false);
			setCamara(ent, true);
		}
		else if(ent->getTipo()=="luz"){
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
TTransf* TMotorTAG::crearTransfRot(float x,float y,float z,float w){
	TTransf* transf = new TTransf();
	transf->rotar(x, y, z, w);

	return transf;
}
TTransf* TMotorTAG::crearTransfTras(float x,float y,float z){
	TTransf* transf = new TTransf();
	transf->trasladar(x, y, z);

	return transf;
}
TTransf* TMotorTAG::crearTransfEsc(float x, float y, float z){
	TTransf* transf = new TTransf();
	transf->escalar(x, y, z);

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
	TCamara* entCam = nullptr;

	for(int i = 0; i < regCam.size(); i++){
		if(estadoCam[i]){
			mVista = glm::inverse(generateMatrix(regCam[i]));
			entCam = (TCamara*)regCam[i]->getEntidad();
			mProyeccion = entCam->getProyectionMatrix();
			i = regCam.size();
		}
	}

	//Obtener puntero luces activas del Registro de luces
	for(int i = 0; i < regLuz.size(); i++){
		if(estadoLuz[i]){
			pLuz.push_back(generateMatrix(regLuz[i]) * glm::vec4(0,0,0,1));
		}
	}

	//Iniciar secuencia draw del arbol
	escena->draw();
*/
	/*
	std::cout << "ViewMatrix: " << std::endl;
	std::cout << glm::to_string(mVista) << std::endl;
	std::cout << "Proyection: " << std::endl;
	std::cout << glm::to_string(mProyeccion) << std::endl;
	std::cout << "Light Position: " << std::endl;
	std::cout << glm::to_string(pLuz[0]) << std::endl;
	*/

//}


glm::mat4 TMotorTAG::generateMatrix(TNodo *nodo){
	//Obtendra la Matriz Modelo de un Nodo dado mediante
	//mediante un recorrido inverso de padre a padre.
	glm::mat4 mResultado = glm::mat4(1.0);
	vector<glm::mat4> mObtenidas;
	TNodo* nodoActual = nodo->getPadre();
	TTransf* entActual = nullptr;

	while(nodoActual->getPadre() != nullptr){
		entActual = dynamic_cast<TTransf*>(nodoActual->getEntidad());
		mObtenidas.push_back(entActual->getMatriz());
		nodoActual = nodoActual->getPadre();
	}

	if(mObtenidas.size()>0){
		for(int i = mObtenidas.size(); i > 0; i--){
			mResultado *= mObtenidas[i-1];
		}
	}

	return mResultado;
}

/*
bool TMotorTAG::setCamara(TEntidad* cam){
	bool z = false;

	bool hayCam = false;
	int pos = -1;

	
		for(int i = 0; i < regCam.size(); i++){
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
	
	return z;
}
*/
bool TMotorTAG::setLuz(TLuz* lz, bool b){
	bool z = false;

	for(int i = 0; i < regLuz.size(); i++){
		if(regLuz[i]->getEntidad()==lz){
			estadoLuz[i] = b;
			z=true;
		}
	}
	return z;
}


TNodo* TMotorTAG::getEscena(){
	return escena;
}

glm::mat4 TMotorTAG::getCamaraMat(){
	glm::mat4 mat = glm::mat4(1);

	if(camara != nullptr){
		mat = generateMatrix(camara);
	}

	return mat;
}

glm::mat4 TMotorTAG::getCamaraProj(){
	glm::mat4 mat = glm::mat4(1);

	if(camara != nullptr){
		mat = dynamic_cast<TCamara*>(camara->getEntidad())->getProyectionMatrix();
	}

	return mat;
}