#ifndef TRAMPA_H
#define TRAMPA_H

#include "../headerfiles/Objeto.h"



class Trampa : public Objeto
{

	public:

		Trampa(ISceneManager* smgr, Posicion pos);
		scene::ISceneNode* getNode();

	private:
        scene::ISceneNode * trampa;
        core::vector3df trampaPosition;
};

#endif // TRAMPA_H