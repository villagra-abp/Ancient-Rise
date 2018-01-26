#ifndef TRAMPA_H
#define TRAMPA_H

#include "../headerfiles/Objeto.h"
//#include "../headerfiles/GameObject.h"


class Trampa : public Objeto//, public GameObject
{

	public:

		Trampa(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos);
		scene::ISceneNode* getNode();


	private:
        scene::ISceneNode * trampa;
        core::vector3df trampaPosition;
        IVideoDriver* 		driver;
};

#endif // TRAMPA_H