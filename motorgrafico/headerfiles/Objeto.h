#include <irrlicht/irrlicht.h>
#include <iostream>
#include "Motorgrafico.h"

using namespace irr;
using namespace std;
using namespace io;

class Objeto {
public:

	virtual ~Objeto();
	Objeto(path s);

	void setLuz(bool flag);
	void setMaterial(path s);
	void setAnimation(string s);


private:	

	Motorgrafico* grafico;
	scene::ISceneManager* escena;

	scene::IAnimatedMesh* mesh;
	scene::IAnimatedMeshSceneNode* node;

	//Eventlistener receiver;
};