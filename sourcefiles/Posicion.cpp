#include "../headerfiles/Posicion.h"

Posicion::Posicion(float x, float y, float z)
{
    posX=x;
    posY=y;
    posZ=z;
}


float Posicion::getPosX()
{
    return posX;
}

float Posicion::getPosY()
{
    return posY;
}

float Posicion::getPosZ()
{
    return posZ;
}
Posicion::~Posicion()
{
    //dtor
}
