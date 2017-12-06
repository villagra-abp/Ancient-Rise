#include "Behavior.h"


Behavior::Behavior(): m_eStatus(BH_INVALID)
{

}


Status Behavior::tick()
{
	if(m_eStatus==!BH_RUNNING) 
	{
		onInitialize();
	}

	m_eStatus=update();

	if(m_eStatus !=BH_RUNNING)
	{
		onTerminate(m_eStatus);
	}

	return m_eStatus; 
}
/*
METODO QUE SE LLAMA SOLO UNA VEZ DESPUES DE QUE EL UPDATE TERMINE
*/
void onTerminate(Status)
{
	
}

/*
METODO QUE SE LLAMA SOLO UNA VEZ DESPUES DE LLAMAR AL UPDATE 
*/
void onInitialize()
{

}

Behavior::~Behavior()
{
    
}