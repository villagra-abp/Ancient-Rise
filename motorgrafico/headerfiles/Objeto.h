#include <irrlicht/irrlicht.h>
#include <iostream>
#include "Motorgrafico.h"
#include "Vector3D.h"

using namespace irr;
using namespace std;
using namespace io;

class Objeto {
public:

	virtual ~Objeto();
	Objeto(path s);
	Objeto(int t);



	Vector3D getPosicion();
	Vector3D getRotacion();

	void addCubo();
	void addEsfera();

	void setAnimation(string s);
	void setLuz(bool flag);
	void setMaterial(path s);
	void setPosicion(Vector3D pos);
	void setRotacion(Vector3D rot);
	



private:	

	Motorgrafico* grafico;
	scene::ISceneManager* escena;

	scene::ISceneNode* node;
	scene::ISceneNodeAnimator* animator;
	scene::IAnimatedMesh* mesh;
	scene::IAnimatedMeshSceneNode* animatedNode;

	//Eventlistener receiver;
};