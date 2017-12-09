#include "../headerfiles/Composite.h"

/*
FUNCION PARA AÑADIR HIJOS A LA TAREA 
*/
void Composite::addChildren(Task *child)
{
	children.push_back(child);
	
}

