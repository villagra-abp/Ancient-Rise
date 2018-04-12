#ifndef MOTORTAG_H
#define MOTORTAG_H

#include "../../headerfiles/TNodo.h"
#include "../../headerfiles/TTransf.h"
#include "../../headerfiles/TLuz.h"
#include "../../headerfiles/TMalla.h"
#include "../../headerfiles/TCamara.h"
#include "../../headerfiles/TGestorRecursos.h"

//#include "FObjeto.h"
//#include "FCamara.h"
#include "vec3.h"
#include "vec4.h"

class TMotorTAG{
public:
	//enum tEnt { transf, malla, luz, camara };

	static TMotorTAG* getInstance();
	virtual ~TMotorTAG();

	/*
	TNodo *crearNodo(TNodo *padre, TEntidad *ent);
	TTransf *crearTransf();
	TTransf *crearTransfRot(float x,float y,float z,float w);
	TTransf *crearTransfTras(float x,float y,float z);
	TTransf *crearTransfEsc(float x, float y, float z);
	TCamara *crearCamara();
	TLuz *crearLuz();
	TMalla *crearMalla(char *fichero);
	void draw();
	*/
	glm::mat4 generateMatrix(TNodo *nodo);
	

	void draw();

	//void registrarCamara(TNodo* cam);
	void activarCamara(TNodo* cam);
	void registrarLuz(TNodo* luz);
	bool eliminarLuz(TNodo* luz);

	//bool setCamara(TEntidad* cam);

	//bool setLuz(TLuz* lz, bool b);

	vector<TNodo*> getLuces();
	glm::mat4 getCamaraMat();
	glm::mat4 getCamaraProj();
	TNodo* getEscena();

private:

	TMotorTAG();
	void recInverso(TNodo *nodo);

	TNodo* escena;
	//vector<TNodo*> regCam;
	//vector<bool> estadoCam;  	//True Camara activada. SOLO UNA
	TNodo* camara;
	vector<TNodo*> regLuz;	
//	vector<bool> estadoLuz;		//True Luz activada.
	//vector<> regVPort;

	glm::mat4 mVista;			//ViewMatrix
	glm::mat4 mProyeccion;		//ProyectionMatrix
	vector<glm::vec4> pLuz;		//Vector Posicion Luz

} ;

#endif //MALLA_H