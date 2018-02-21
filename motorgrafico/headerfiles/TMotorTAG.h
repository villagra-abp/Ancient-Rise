#ifndef MOTORTAG_H
#define MOTORTAG_H

#include "TEntidad.h"
#include "TNodo.h"

class TMotorTAG{
public:
	TMotorTAG();
	virtual ~TMotorTAG();

	TNodo *crearNodo(TNodo *padre, TEntidad *ent);
	TTransf *crearTransf();
	TCamara *crearCamara();
	TLuz *crearLuz();
	TMalla *crearMalla(char *fichero);
	void draw();
	glm::mat4 generateMatrix(TNodo *nodo);


private:
	void recInverso(TNodo *nodo);

	TNodo* escena;
	vector<TCamara*> regCam;
	vector<TLuz*> regLuz;
	//vector<> regVPort;

	glm::mat4 mCamara;
	vector<glm::mat4> mLuz;

	glm::mat4 mVista;
	vector<glm::vec4> pLuz;

} ;

#endif //MALLA_H