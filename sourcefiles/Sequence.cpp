#include "../headerfiles/Sequence.h"

void Sequence::onInitialize(Blackboard *b)
{
	m_CurrentChild = children.begin();
}

/*
FUNCION QUE PROCESA CADA TAREA HIJO ,UNO POR UNO, EN LA LISTA SALIENDO SI ALGUNO FALLA. 
DEVUELVE SUCCESS SI TODOS SE HAN EJECUTADO CORRECTAMENTE 
*/
Status Sequence::run(Enemigo *e)
{

	Status s = (*m_CurrentChild)->run(e);

	// Si el hijo falla o sige ejecutandose entonces devuelve el codido de estado
	if(s != BH_SUCCESS)
	{
		this->setStatus(s);
		return s;
	}

	// AVANZAMOS HASTA QUE LLEGEMOS AL FINAL DEL ARRAY (++ operador de incremento de iterator)
	if(++m_CurrentChild == children.end())
	{
		this->setStatus(BH_SUCCESS);
		
		return BH_SUCCESS;
	}
}

Sequence::~Sequence()
{
	
}