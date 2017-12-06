#include "Decorator.h"


Decorator::Decorator(Behavior* child): m_pChild(child)
{

}

void Behavior::onInitialize()
{

}

void Behavior::onTerminate(Status)
{

}