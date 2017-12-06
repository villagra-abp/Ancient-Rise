#ifndef BEHAVIORTREE_H
#define BEHAVIORTREE_H

#include <iostream>
#include <vector>
#include "Behavior.h"



using namespace std;

/**
SIRVE COMO PUNTO CENTRAL PARA ALMACENAR Y ACTUALIZAR EL ARBOL
*/
class BehaviorTree
{
	public:
		void tick();

	protected:
		Behavior* m_pProot;  // PUNTERO A LA RAIZ DEL BEHAVIOR TREE
};

#endif // BEHAVIORTREE_H