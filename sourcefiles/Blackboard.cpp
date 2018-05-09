#include "../headerfiles/Blackboard.h"
#include "../headerfiles/Alarma.h"


Blackboard::Blackboard():enemBActual(nullptr), prota(nullptr)
{

}

void Blackboard::borrarEnemB()
{
	for(int i = 0 ; i < enemigosB.size(); i++){
		cout<<"entro"<<endl;
		delete enemigosB[i];
	}
	enemigosB.clear();
}


glm::f32 Blackboard::getTime()
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

vector<Alarma*> Blackboard::getAlarma()
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

Protagonista* Blackboard::getProtagonista()
{
	return prota;
}

vector<NodoGrafo*> Blackboard::getNodosGrafo()
{
	return nodos;
}


void Blackboard::setTime(const glm::f32 T)
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

void Blackboard::setAlarma(vector<Alarma*> a)
{
	alarmas = a;
}

void Blackboard::setEnemB(vector<EnemigoBasico*> e)
{
	enemigosB=e;
}

void Blackboard::setEnemBActual(EnemigoBasico *e)
{
	enemBActual = e;
}

void Blackboard::setProtagonista(Protagonista* p)
{
	prota = p;
}

void Blackboard::setNodosGrafo(vector<NodoGrafo*> n)
{
	nodos = n;
}


Blackboard::~Blackboard()
{	
	for(int i = 0 ; i < alarmas.size(); i++){
		delete alarmas[i];
	}
	alarmas.clear();

	for(int i = 0 ; i < fuentes.size(); i++){
		delete fuentes[i];
	}
	fuentes.clear();

	for(int i = 0 ; i < enemigosB.size(); i++){
		delete enemigosB[i];
	}
	enemigosB.clear();

	for(int i = 0 ; i < nodos.size(); i++){
		delete nodos[i];
	}
	nodos.clear();
	
}
