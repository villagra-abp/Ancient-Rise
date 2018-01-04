#include "../headerfiles/Blackboard.h"



Blackboard::Blackboard()
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
	return o;
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
	o = f;
}


Blackboard::~Blackboard()
{
    //dtor
}