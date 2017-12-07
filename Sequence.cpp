#include <Sequence.h>

void Sequence::onInitialize()
{
	m_CurrentChild = children.begin();
}

/*
FUNCION QUE PROCESA CADA TAREA HIJO ,UNO POR UNO, EN LA LISTA SALIENDO SI ALGUNO FALLA. 
DEVUELVE SUCCESS SI TODOS SE HAN EJECUTADO CORRECTAMENTE 
*/
Status Sequence::run()
{

	Status s = (*m_CurrentChild)->run();

	// Si el hijo falla o sige ejecutandose entonces devuelve el codido de estado
	if(s != BH_SUCCESS)
	{
		return s;
	}

	// AVANZAMOS HASTA QUE LLEGEMOS AL FINAL DEL ARRAY (++ operador de incremento de iterator)
	if(++m_CurrentChild == children.end())
	{
		return BH_SUCCESS;
	}
}