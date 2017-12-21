#include "Objeto.h"

Objeto::Objeto(int idCont, Color color, float x, float y, float radius){        //CONSTRUCTOR DE OBJETO
    
    id = idCont; 
    alreadyIN = false;
    
    obj = new CircleShape;
    obj->setRadius(radius);
    obj->setPosition(x, y);
    obj->setFillColor(color);
    obj->setOrigin(obj->getRadius(), obj->getRadius());
}

// SETERS.

bool Objeto::setState(bool state){
    alreadyIN = state;
}

// GETERS.

sf::CircleShape* Objeto::getCirculo(){
    return obj;
}

bool Objeto::getState(){
    return alreadyIN;
}

int Objeto::getId(){
    return id;
}
    
Objeto::~Objeto(){      //DESTRUCTOR DE PERSONAJE
    obj = nullptr;
}