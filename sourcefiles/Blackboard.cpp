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


vector<Objeto*> Blackboard::getFuente()
{
	return fuentes;
}

vector<Objeto*> Blackboard::getComida()
{
	return comidas;
}

vector<Objeto*> Blackboard::getAlarma()
{
	return alarmas;
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
	fuentes.push_back(f);
}

void Blackboard::setComida(Objeto *c)
{
	comidas.push_back(c);
}

void Blackboard::setAlarma(Objeto *a)
{
	alarmas.push_back(a);
}


Blackboard::~Blackboard()
{	
	for(int i = 0 ; i < alarmas.size(); i++){
		alarmas[i] = nullptr;
		delete alarmas[i];
	}

	alarmas.clear();

	for(int i = 0 ; i < comidas.size(); i++){
		comidas[i] = nullptr;
		delete comidas[i];
	}

	comidas.clear();

	for(int i = 0 ; i < fuentes.size(); i++){
		fuentes[i] = nullptr;
		delete fuentes[i];
	}

	fuentes.clear();
}