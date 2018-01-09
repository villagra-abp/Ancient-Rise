#include "../headerfiles/Blackboard.h"



Blackboard::Blackboard():comida(nullptr), fuente(nullptr), alarma(nullptr)
{

}


f32 Blackboard::getTime()
{
	return time;
}

float Blackboard::getProta()
{
	return protaX;
}


Objeto* Blackboard::getFuente()
{
	return fuente;
}

Objeto* Blackboard::getComida()
{
	return comida;
}

Objeto* Blackboard::getAlarma()
{
	return alarma;
}




void Blackboard::setTime(const f32 T)
{
	time = T;
}

void Blackboard::setProta(float pX)
{
	protaX = pX;
}

void Blackboard::setFuente(Objeto* f)
{
	fuente= f;
}

void Blackboard::setComida(Objeto *c)
{
	comida = c;
}

void Blackboard::setAlarma(Objeto *a)
{
	alarma = a;
}


Blackboard::~Blackboard()
{
    //dtor
	comida = nullptr;
	fuente = nullptr;
	alarma = nullptr;


    delete comida;
    delete fuente;
    delete alarma;
}