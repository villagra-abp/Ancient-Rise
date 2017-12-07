#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <vector>


using namespace std;


enum Status // CADA COMPORTAMIENTO, CUANDO SE EJECUTA, DEVUELVE UN ESTADO QUE ES CRITICO PARA QUE EL EBHAVIOR TREE FUNCIONE
/**
 * 
 ** Devuelve los valores de los estados validos para los comportamientos
 */
{
	BH_INVALID,
    BH_SUCCESS, // COMPLETION STATUS --> INDICA QUE TODO HA IDO COMO SE ESPERABA ( LO DEVUELVEN LAS ACCIONES )
    BH_FAILURE, // COMPLETION STATUS --> INDICA QUE ALGO HA IDO MAL
    BH_RUNNING, // INDICACION DE EJECUCION --> INDICA QUE LA EJECUCION ESTA EN MARCHA 
	BH_ABORTED,
};

// Clase Base para las tareas de la cual todos los nodos pueden heredar (REPRESENTA TODAS LAS TAREAS DEL ARBOL)
class Task
{
	public:

		Task();
		virtual ~Task();
		virtual void onInitialize()=0;
		virtual Status run()=0; // Metodo que se utiliza para ejecutar la tarea que devuelve un codigo de estado diciendo si ha tenido exito o no


	private:
		Status m_eStatus;
};

#endif // TASK_H