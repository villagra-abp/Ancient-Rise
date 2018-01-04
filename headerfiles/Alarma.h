#ifndef ALARMA_H
#define ALARMA_H


#include "../headerfiles/Objeto.h"


class Alarma : public Objeto
{

	public:
		Alarma(ISceneManager* smgr, Posicion pos);
		virtual ~Alarma();




};

#endif