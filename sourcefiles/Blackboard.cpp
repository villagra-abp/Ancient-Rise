#include "../headerfiles/Blackboard.h"



Blackboard::Blackboard():enemBasico(nullptr)
{

}
/*
template <class T>
T Blackboard::get()
{

	return v;
}
*/

Enemigo * Blackboard::getEnem()
{
	return enemBasico;
}

f32 Blackboard::getVel()
{
	return velocidadEnemigo;
}

f32 Blackboard::getTime()
{
	return time;
}

float Blackboard::getProta()
{
	return protaX;
}

vector<Posicion*> Blackboard::getPos()
{
	return posPatrulla;
}




void Blackboard::setEnemigo(Enemigo* e)
{
	enemBasico = e;
}

void Blackboard::setVel(f32 vel)
{
	velocidadEnemigo = vel;
}

void Blackboard::setTime(const f32 T)
{
	time = T;
}

void Blackboard::setPos(vector<Posicion*> pos)
{
	posPatrulla = pos;
}

void Blackboard::setProta(float pX)
{
	protaX = pX;
}

Blackboard::~Blackboard()
{
    //dtor
}