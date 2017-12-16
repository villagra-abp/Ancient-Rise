#include "../headerfiles/BehaviorTree.h"



BehaviorTree::BehaviorTree(int t, Blackboard *b):board(b)
{

	
	if(t==1)
	{

		AvanzarPatrulla *avanzarP = new AvanzarPatrulla();  // Creamos la tarea para patrullar
		DetectarProta *detectP = new DetectarProta();  // Creamos la tarea para ver si hemos visto al prota
		Selector s1;
		sel=s1;

		detectP->onInitialize(b); 						// Inicializamos la tarea y le pasamos la blackboard
		avanzarP->onInitialize(b); 						

		sel.addChildren(detectP);
		sel.addChildren(avanzarP);							// Metemos un hijo en el selector creado
		sel.onInitialize(board);						// Lo inicializamos para que el iterador apunte al principio del vector

	}

}


void BehaviorTree::update()
{
	Status s =sel.run();  			// Ejecutamos todos los hijos del selector hasta encontrar uno que tenga exito o no queden mas
	
	if(s == BH_SUCCESS) // Si el selector devuelve true quiere decir que se ha ejecutado una tarea con exito por lo que tenemos que salir del arbol
	{
		sel.onInitialize(board);				// Lo inicializamos para que el iterador apunte al principio del vector
	}

	
}


BehaviorTree::~BehaviorTree()
{
    //dtor
}