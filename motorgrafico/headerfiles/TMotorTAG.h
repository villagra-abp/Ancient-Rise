#ifndef MOTORTAG_H
#define MOTORTAG_H

#include "TNodo.h"
#include "TTransf.h"
#include "TLuz.h"
#include "TMalla.h"
#include "TCamara.h"


class TMotorTAG{
public:
	//enum tEnt { transf, malla, luz, camara };

	TMotorTAG();
	virtual ~TMotorTAG();

	TNodo *crearNodo(TNodo *padre, TEntidad *ent);
	TTransf *crearTransf();
	TTransf *crearTransfRot(float x,float y,float z,float w);
	TTransf *crearTransfTras(float x,float y,float z);
	TTransf *crearTransfEsc(float x, float y, float z);
	TCamara *crearCamara();
	TLuz *crearLuz();
	TMalla *crearMalla(char *fichero);
	void draw();
	glm::mat4 generateMatrix(TNodo *nodo);
	bool setCamara(TCamara* cam, bool b);
	bool setLuz(TLuz* lz, bool b);


private:
	void recInverso(TNodo *nodo);

	TNodo* escena;
	vector<TNodo*> regCam;
	vector<bool> estadoCam;  	//True Camara activada. SOLO UNA
	vector<TNodo*> regLuz;	
	vector<bool> estadoLuz;		//True Luz activada.
	//vector<> regVPort;

	glm::mat4 mVista;			//ViewMatrix
	glm::mat4 mProyeccion;		//ProyectionMatrix
	vector<glm::vec4> pLuz;		//Vector Posicion Luz

} ;

#endif //MALLA_H