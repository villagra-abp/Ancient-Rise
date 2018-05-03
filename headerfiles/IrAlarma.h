#ifndef IRALARMA_H
#define IRALARMA_H

#include "../headerfiles/Task.h"

// Tarea (Accion) para saber ir hacia la alarma que esta sonando
class IrAlarma : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		void buscarNodoInicial(Enemigo *e, float posX);
		void recorrerNodos(Enemigo *e, uint8_t v, float posX);
		void movimientoDireccion(Enemigo *e, bool d);
		void comprobarAlarmaSonando(float posEnemX);
		NodoGrafo* calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX);
		void reset();
		void checkComportamiento(Enemigo *e);
		void checkVelocidad(Enemigo *e);
		virtual ~IrAlarma();


	private:
		
		Blackboard *board;
	    vector<Alarma*> a;
	    float enemigoX, enemigoY;

		//Datos de alarma
	    Posicion* alarmaPosition;
		float alarmaX, alarmaY;
		int distanciaAlarma, distAlarmAux;
		int pos;

		/* PATHFINDING */
	    vector<NodoGrafo*> nodos;
	    NodoGrafo *inicio1, *inicio2, *inicioBueno, *fin;
	    Posicion* posNodoI, *posNodo;
	    vector <Arista*> caminoCorto; 							// Contiene el camino mas corto calculado hasta el punto donde se queria ir
	    bool llegadoInicio = false;
	    bool llegadoFin = false;
	    bool llegadoAlarma = false;
	    Grafo *g; 												// Para poder calcular el camino mas corto
	    int iC;
	    float distNodoF, distNodoFY, distNodoI;
	    Comportamiento tipo;
	    bool bajada;
		
};

#endif // IRALARMA_H
