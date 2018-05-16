#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <cstdint>
#include <string>

#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <math.h>
#include <unistd.h>
#include <ctime>

#include "../headerfiles/Posicion.h"
#include "../headerfiles/Fachada.h"


using namespace std;



class GameObject {
public:
	enum Tipo { PROTA, ENEMY, COMIDA, FUENTE, BEBIDA, ALARMA, TRAMPA, PROYECTIL, NODOGRAFO, PALANCA };

 	//virtual void update() = 0;
   
   	Tipo getTipo() const { return goType; } // Devuelve tipo.

   	virtual Posicion* getPosition() const = 0; //Devuelve la posicion.
   
protected:
	Tipo goType;

	void setTipo(Tipo t){ goType = t; }

};

#endif
