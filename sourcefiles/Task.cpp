#include "../headerfiles/Task.h"

/*
CONSTRUCTOR DE TAREA PARA INICIAR EL ESTADO DE LA TAREA  COMO INVALIDO 
*/
Task::Task(): m_eStatus(BH_INVALID)
{
}

Status Task::getStatus() const
{
	return m_eStatus;
}

Task::~Task()
{
    
}