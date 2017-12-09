#include "../headerfiles/Decorator.h"


/*
Constructor para crear el hijo del decorador
*/
Decorator::Decorator(Task* child): m_pChild(child)
{

}