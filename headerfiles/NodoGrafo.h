#ifndef NODOGRAFO_H
#define NODOGRAFO_H


#include "../headerfiles/Arista.h"
#include "../headerfiles/GameObject.h"

class NodoGrafo : public GameObject
{
	public:
		
		NodoGrafo(int n, glm::f32 x, glm::f32 y);
		void insertAristaS(Arista *s, NodoGrafo *final);
		void insertAristaE(Arista *e);

		/* Getters y Setters */
		vector<Arista*> getAristasS();
		vector<Arista*> getAristasE();
		int getNombre();
		double getCostSoFar();
		Arista* getAristaPath();
		virtual Posicion* getPosition() const override { return nodoPosition; }

		void setCostSoFar(double c);
		void setAristaPath(Arista* a);

		virtual ~NodoGrafo();


	private:
	
		int id; 					// Identificador del nodo
		double cost_so_far; 			// Coste total del camino hasta este nodo
		vector<Arista*> aristasEnt;		// Vector con todas las aristas entrantes del nodo
		vector<Arista*> aristasSal; 	// Vector con todas las aristas salientes del nodo
		Arista* path;						
		Posicion* nodoPosition;			// Posicion (x,y) del nodo 
		void * objeto;


		
};

#endif // NODOGRAFO_H
