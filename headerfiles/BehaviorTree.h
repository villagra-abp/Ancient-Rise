#ifndef BEHAVIORTREE_H
#define BEHAVIORTREE_H


#include "../headerfiles/Sequence.h"
#include "../headerfiles/Enemigo.h"


// Clase para construir la estructura del behavior tree para todos los tipos de enemigos
class BehaviorTree
{
	public:

		BehaviorTree(int c, Blackboard *b);
		void update(Enemigo *e);

		virtual ~BehaviorTree();

	private:

		Composite* m_pRoot; 					// Tarea raiz ( a partir de la cual se ejecutan todas las demas del arbol)
		int tipo;
		Blackboard *board;
		typedef vector<Task*> Composites;
		Composites comp; 						// Vector con todos los composites que contiene el arbol
		typedef vector<Task*> Tasks;
		Tasks task;
		
};

#endif // BEHAVIORTREE_H