#include "Motorgrafico.h"
#include "Vector3D.h"

using namespace irr;
using namespace std;
using namespace io;

class ObjetoF {
public:

	virtual ~ObjetoF();
	ObjetoF(path s);
	ObjetoF(int t);



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
