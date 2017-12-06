#include "Composite.h"


/*
FUNCION PARA AÑADIR UN NUEVO HIJO AL VECTOR DE HIJOS 
*/
void Composite::addChild(Behavior* child)
{
	m_Children.push_back(child);  // METE EL ELEMENTO AL FINAL DEL VECTOR DESPUES DEL ACTUAL ULTIMO ELEMENTO QUE HAYA 
}

/*
FUNCION PARA BORRAR UN HIJO DEL VECTOR DE HIJOS 
*/
void Composite::removeChild(Behavior* child)
{

}

/*
FUNCION PARA VACIAR EL VECTOR DE HIJOS 
*/
void Composite::clearChildren()
{

}
