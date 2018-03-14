#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <vector>

#include <irrlicht/irrlicht.h>
#include <SFML/Graphics.hpp>
#include "../headerfiles/Blackboard.h"




using namespace std;
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


enum Status // CADA COMPORTAMIENTO, CUANDO SE EJECUTA, DEVUELVE UN ESTADO QUE ES CRITICO PARA QUE EL EBHAVIOR TREE FUNCIONE
/**
 * 
 ** Devuelve los valores de los estados validos para los comportamientos
 */
{
	BH_INVALID,
    BH_SUCCESS, // COMPLETION STATUS --> INDICA QUE TODO HA IDO COMO SE ESPERABA ( LO DEVUELVEN LAS ACCIONES )
    BH_FAILURE, // COMPLETION STATUS --> INDICA QUE ALGO HA IDO MAL
    BH_RUNNING, // INDICACION DE EJECUCION --> INDICA QUE LA EJECUCION ESTA EN MARCHA, LA TAREA AUN SE ESTA EJECUTANDO
	BH_ABORTED,
};

// Clase Base para las tareas de la cual todos los nodos pueden heredar (REPRESENTA TODAS LAS TAREAS DEL ARBOL)
class Task
{
	public:

		Task();
		virtual ~Task();
		virtual void onInitialize(Blackboard *b)=0;   // El igual a 0 quiere decir que este metodo no se va a implementar aqui (la clase se convierte en abstracta) sino que va a ser 
										 // implementado en una clase derivada.
		virtual Status run(Enemigo *e)=0; 		 // Metodo que se utiliza para ejecutar la tarea que devuelve un codigo de estado diciendo si ha tenido exito o no
		Status getStatus() const;
		Status setStatus(Status s);


	private:
		Status m_eStatus;
};

#endif // TASK_H
