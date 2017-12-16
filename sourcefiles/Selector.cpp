#include "../headerfiles/Selector.h"


/*
FUNCION QUE INICIALIZA LA SECUENCIA PARA QUE EMPIECE AL PRINCIPIO DEL ARRAY DE HIJOS
*/
void Selector::onInitialize(Blackboard *b)
{
	m_Current = children.begin(); // DEVUELVE UN ITERADOR APUNTANDO AL PRIMER ELEMENTO DEL VECTOR
}

/*
FUNCION PARA EJECUTAR LAS TAREAS DE LOS HIJOS. SI ALGUNA SE EJECUTA CON EXITO ENTONCES TERMINA Y DEVUELVE 
EL ESTADO. SINO CONTINUA EJECUTANDO EL RESTO DE SUS HIJOS HASTA LLEGAR AL FINAL
*/
Status Selector::run()
{
	
	Status s = (*m_Current)->run();  // Ejecutamos la tarea del hijo en el que nos encontramos

	if(s!=BH_FAILURE)  // Si la tarea ha tenido exito o sigue ejecutandose devolvemos el estado de la misma, sino seguimos probando a ejecutar el resto
	{
		return s;
	}

	// Avanzamos al siguiente hijo y comprobamos que no se haya acabado ya el vector
	if(++m_Current == children.end())
	{
		return BH_FAILURE;
	}

}


Selector::~Selector()
{
	
}