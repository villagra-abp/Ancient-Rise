#include "../headerfiles/Blackboard.h"



Blackboard::Blackboard():enemBActual(nullptr), prota(nullptr)
{

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

vector<Objeto*> Blackboard::getComida()
{
	return comidas;
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

void Blackboard::setComida(vector<Objeto*> c)
{
	comidas = c;
}

void Blackboard::setAlarma(vector<Alarma*> a)
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

void Blackboard::setProtagonista(Protagonista* p)
{
	prota = p;
}

void Blackboard::setNodosGrafo(vector<NodoGrafo*> n)
{
	nodos = n;

	/*for(int i=0; i<nodos.size();i++)
    {
        cout<<"Nodo "<<nodos[i]->getNombre();
        cout<<" en X: "<<nodos[i]->getPosition()->getPosX();
        cout<<" y en Y: "<<nodos[i]->getPosition()->getPosY()<<endl;
    }
    cout<<"SIGUIENTE"<<endl;
    */
}


Blackboard::~Blackboard()
{	
	for(int i = 0 ; i < alarmas.size(); i++){
		delete alarmas[i];
	}
	alarmas.clear();

	for(int i = 0 ; i < comidas.size(); i++){
		delete comidas[i];
	}
	comidas.clear();

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
