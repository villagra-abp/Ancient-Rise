#include "../headerfiles/Repeat.h"


/*
Constructor para indicar el hijo del decorador
*/
Repeat::Repeat(Task* child): Decorator(child)
{

}
/*
Funcion para alamacenar el numero de veces que se va a hacer el comportamiento
*/
void Repeat::setCount(int count)
{
	m_iLimit=count;
}

void Repeat::onInitialize(Blackboard *b)
{
	m_iCounter=0;
}

Status Repeat::run()
{
	m_pChild->run();

	if(m_pChild->getStatus() == BH_RUNNING)  
	{
		return BH_RUNNING;
	}

	if(m_pChild->getStatus() == BH_FAILURE)  
	{
		return BH_FAILURE;
	}

	if(++m_iCounter==m_iLimit)
	{
		return BH_SUCCESS;
	}
}


