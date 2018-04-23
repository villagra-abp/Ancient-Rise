#ifndef ARISTA_H
#define ARISTA_H

class NodoGrafo;

enum Comportamiento  // Enumerador para definir el comportamiento que debe seguir el NPC mientras este pasando esta arista
{
	
	SALTO, 			// El NPC tiene que ejecutar un salto
	NORMAL,
	BAJADA,
};

class Arista
{
	public:
		
		Arista(int c, int c2);

		void setNodoI(NodoGrafo *i);
		void setNodoF(NodoGrafo *f);

		double getCoste();
		NodoGrafo* getNodoInicio();
		NodoGrafo* getNodoFin();
		Comportamiento getComportamiento();

		virtual ~Arista();


	private:
		double coste; 		// Determina el coste de la arista
		NodoGrafo *inicio;	// Nodo desde donde empieza la arista
		NodoGrafo *fin;  	// Nodo donde acaba la arista
		Comportamiento m_eTipo;
		
};

#endif // ARISTA_H