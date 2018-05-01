#include "../headerfiles/Arista.h"

Arista::Arista(int c, int c2):inicio(nullptr),fin(nullptr)
{
	coste = c;  		// Coste de la arista(coste del camino)

	switch(c2)
	{
		case 1: 
		{
			m_eTipo = NORMAL;
			break;
		}

		case 2:
		{
			m_eTipo = SALTO;
			break;
		}

		case 3:
		{
			m_eTipo = BAJADA;
			break;
		}

		case 4:
		{
			m_eTipo = SALTO_GRANDE;
			break;
		}
	}
	
}

void Arista::setNodoI(NodoGrafo *i)
{
	inicio = i;
}

void Arista::setNodoF(NodoGrafo *f)
{
	fin = f;
}

double Arista::getCoste()
{
	return coste;
}

NodoGrafo* Arista::getNodoInicio()
{
	return inicio;
}

NodoGrafo* Arista::getNodoFin()
{
	return fin;
}

Comportamiento Arista::getComportamiento()
{
	return m_eTipo;
}

Arista::~Arista()
{
	
}