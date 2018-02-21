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


private:
	void recInverso(TNodo *nodo);

	TNodo* escena;
	vector<TCamara*> regCam;
	vector<TLuz*> regLuz;
	//vector<> regVPort;

} ;

#endif //MALLA_H