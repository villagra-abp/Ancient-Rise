#include "../headerfiles/Grafo.h"
#include <algorithm>

Grafo::Grafo():current(nullptr), nodoFinal(nullptr), startRecord(nullptr), endNodeRecord(nullptr)
{
	nodoFinalCoste = 0;
	encontrado = false;

	itA = abierta.begin();
	itC = cerrada.begin();

}

vector<Arista*> Grafo::pathfindDijkstra(NodoGrafo *inicio, NodoGrafo *fin)
{	
	//cout<<"ENTRANDO"<<endl;
	// Resetamos los valores para evitar problemas
	reset();

	startRecord = inicio; 																// Almacenamos el nodo donde empezamos el camino
	nodosReset.push_back(inicio);

	//cout<<"Coste Nodo Inicio "<<inicio->getCostSoFar()<<endl;
	//cout<<"Coste Nodo FInal "<<fin->getCostSoFar()<<endl;
	itA = abierta.begin(); 																// Inicializamos el iterador de la lista Abierta
	abierta.push_back(startRecord); 													// Metemos el nodo inicial en la lista 
	itC = cerrada.begin();

	while(abierta.size()>0 && encontrado!=true) 										// Mientras que queden nodos por procesar en la lista abierta
	{
		//cout<<"dentro : "<<abierta.size()<<endl;
		//cout<<"entro Bucle"<<endl;
		smallestElement(); 																// Encontramos el nodo con el menor coste de la lista abierta
		//cout<<"Nombre1: "<<current->getNombre()<<endl;
		if(current->getNombre()==fin->getNombre()) 										// Si el nodo con el coste mas bajo ya es el nodo final del camino, terminamos
		{
			encontrado = true;
			//cout<<"ENCONTRADO!"<<endl;
		}
		else
		{
			aristas = current->getAristasS(); 											// Obtenemos todas las aristas salientes del nodo actual
			
			for(int cont=0;cont<aristas.size();cont++) 									// Recorremos todas las aristas salientes buscando sus nodos FInales para establecer su coste
			{	
				nodoFinal = aristas[cont]->getNodoFin();    							// Obtenemos el nodoFinal de la arista en la que nos encontramos
				nodosReset.push_back(nodoFinal);
				//cout<<nodoFinal->getNombre()<<endl;
				nodoFinalCoste = current->getCostSoFar() + aristas[cont]->getCoste();	// Calculamos el cost_so_far del nodoFinal de la arista, suamndo el coste dle nodo incial de la arista
																						//(nodo actual en el que estamos) con el coste de la arista (AUn no lo hemos almacenado)

				// Buscamos que el nodoFInal de la arista no este dentro de la lista cerrada
				itC = find(cerrada.begin(), cerrada.end(), nodoFinal);
				if(itC != cerrada.end()) 
				{
					/* Dijkstra nunca va a encontrar un ruta mejor en un nodo que se encuentre ya en la lista cerrada.
					Por lo que no hacemos nada */
				}
				else  // No esta dentro de cerrada, buscamos si esta dentro de abierta
				{	
					itA = find(abierta.begin(), abierta.end(), nodoFinal);
					if(itA != abierta.end())
					{	
						endNodeRecord = *itA;

						if(endNodeRecord->getCostSoFar()>nodoFinalCoste) 			// Con la nueva ruta tenemos un coste menor que el que ya habia en el nodo
						{
							endNodeRecord->setCostSoFar(nodoFinalCoste);
							endNodeRecord->setAristaPath(aristas[cont]);
						}
						
					}
					else  // Tenemos un nodo no visitado por lo que hacemos una grabacion de el
					{
						endNodeRecord = new NodoGrafo(100, 0, 0);
						endNodeRecord = nodoFinal;  			// Guardamos el nodoFinal de la arista

						// Actualizamos la informacion del nodo (su cost_so_far y la arista)
						endNodeRecord->setCostSoFar(nodoFinalCoste);
						endNodeRecord->setAristaPath(aristas[cont]);				

						itA = find(abierta.begin(), abierta.end(), endNodeRecord);
						if(itA==abierta.end()) 					// EL nodo no se encuentra ya en la lista abierta
						{
							abierta.push_back(endNodeRecord);
						}

					}
				}
			}

			// Hemos terminado de mirar todas las aristas del nodo actual por lo que lo eliminamos de la lista abierta y lo metemos en la cerrada
			//abierta.remove(current);
			itA = find(abierta.begin(), abierta.end(), current);
			if(itA!=abierta.end())
			{
				itA = abierta.erase(itA);
				//cout<<"BORRADO"<<endl;
				//cout<<"BOrradoTam :"<<abierta.size()<<endl;
			}
			
			//current->setCostSoFar(0);
			cerrada.push_back(current);

		}

	}

	for(int i=0; i<nodosReset.size(); i++)
	{
		nodosReset[i]->setCostSoFar(0);
	}

	// Hemos llegado hasta aqui si hemos encontrado el ndoo Final del camino o si ya no hay mas nodos que buscar
	if(current->getNombre()!=fin->getNombre())
	{	
		cout<<"No hemos encontrado el nodo final"<<endl;
	}
	else
	{
		
		while(current->getNombre()!=inicio->getNombre())  	// Mientras que no encontremos el nodo incial
		{
			path.push_back(current->getAristaPath());
			current = current->getAristaPath()->getNodoInicio();
		}
		
		reverse(path.begin(),path.end()); 				// Le damos la vuelta al vector



		return path;
	}

}

/* Funcion para encontrar el nodo con el cost-so-far mas bajo de la lista abierta */
void Grafo::smallestElement()
{
	double costeMasBajo = 10000;

	for(itA = abierta.begin(); itA!=abierta.end();++itA)
	{
		//cout<<"CostaMasBajo :"<<costeMasBajo<<endl;
		double coste = (*itA)->getCostSoFar(); 		// Accedemos al nodo mediante el puntero del iterador
		//cout<<"Coste :"<<coste<<endl;

		if(coste<costeMasBajo)
		{
			costeMasBajo = coste;  					// Actualizamos el valor del coste mas bajo
			current = *itA; 						// Almacenamos el nodo que tiene ese valor mas bajo
		}
	}
	

	itA = abierta.begin(); 							// Volvemos a apuntar el iterador al principio
}

/* Funcion para inicializar los valores, vaciar las listas etc. Y evitar problemas a la hora de buscar varias veces un camino en una misma ejecucion */
void Grafo::reset()
{
	abierta.clear();
	cerrada.clear();
	nodoFinalCoste = 0;
	encontrado = false;
	endNodeRecord = nullptr;
}

Grafo::~Grafo()
{
	startRecord = nullptr;
	endNodeRecord = nullptr;
	current = nullptr;
	nodoFinal = nullptr;
}