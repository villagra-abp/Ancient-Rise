#ifndef MAPA_H
#define MAPA_H

#include "../headerfiles/Motorgrafico.h"

class Mapa{
public:
	virtual ~Mapa();
	Mapa(io::path s);


	void setPosicion(int x, int y, int z);


private:	

	Motorgrafico* grafico;
	scene::ISceneManager* escena;

	scene::IAnimatedMesh* mesh;
	scene::ISceneNode* node;
} ;


#endif //MAPA_H