#include "../headerfiles/Blackboard.h"



Blackboard::Blackboard():enemBActual(nullptr)
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

vector<EnemigoBasico*> Blackboard::getEnemB()
{
	return enemigosB;
}

EnemigoBasico* Blackboard::getEnemBActual()
{
	return enemBActual;
}




void Blackboard::setTime(const f32 T)
{
	time = T;
}

void Blackboard::setProta(float pX)
{
	protaX = pX;
}

void Blackboard::setFuente(vector<Objeto*> f)
{
	fuentes = f;
}

void Blackboard::setComida(vector<Objeto*> c)
{
	comidas = c;
}

void Blackboard::setAlarma(vector<Objeto*> a)
{
	alarmas = a;
}

void Blackboard::setEnemB(EnemigoBasico *e)
{
	enemigosB.push_back(e);
}

void Blackboard::setEnemBActual(EnemigoBasico *e)
{
	enemBActual = e;
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