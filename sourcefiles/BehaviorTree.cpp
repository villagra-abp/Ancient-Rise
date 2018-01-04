#include "../headerfiles/BehaviorTree.h"
#include "../headerfiles/AvanzarPatrulla.h"
#include "../headerfiles/DetectarProta.h"
#include "../headerfiles/ComprobarSed.h"
#include "../headerfiles/BuscarAgua.h"
#include "../headerfiles/ComprobarVida.h"
#include "../headerfiles/Selector.h"
#include "../headerfiles/Huir.h"


BehaviorTree::BehaviorTree(int c, Blackboard *b):board(b)
{

	switch (c)
	{
		case 1: // Comportamiento Enemigos Basicos
		 {
			/* CREACION DE TAREAS */
			AvanzarPatrulla *avanzarP = new AvanzarPatrulla();  	// Patrulla
			DetectarProta *detectP = new DetectarProta();  			// Deteccion Protagonista
			ComprobarSed *checkSed = new ComprobarSed();			// Comprobacion sed
			BuscarAgua *bAgua = new BuscarAgua();					// Busqueda de agua
			ComprobarVida *cVida = new ComprobarVida();				// Comprobar Vida del enemigo
			Huir *huir = new Huir(); 								// Huir


			/* INICIALIZACIONES DE TAREAS */
			detectP->onInitialize(b); 								// Es necesario inicializar para poder pasar la blackboard
			avanzarP->onInitialize(b); 	
			checkSed->onInitialize(b);
			bAgua->onInitialize(b);
			cVida->onInitialize(b);
			huir->onInitialize(b);

			/* Sequencia para ver la vida del enemigo y huir si es baja */

			Sequence *seqCVida = new Sequence();

			seqCVida->addChildren(cVida);
			seqCVida->addChildren(huir);
			seqCVida->onInitialize(board);

			/* Selector para ver que hacer cuando detectamos al prota (Huir - Activar Alarma - Atacar)*/

			Selector *sDetect = new Selector();

			sDetect->addChildren(seqCVida);
			sDetect->onInitialize(board);							

			/* Sequencia para comprobar si detectamos al prota y ver que hacer */

			Sequence *seqDetect = new Sequence();

			seqDetect->addChildren(detectP);
			seqDetect->addChildren(sDetect);
			seqDetect->onInitialize(board);

			/* Sequencia para comprobar sed y buscar agua */
			Sequence *seqSed = new Sequence(); 				
			
			seqSed->addChildren(checkSed); 							// Añadimos sus hijos
			seqSed->addChildren(bAgua);
			seqSed->onInitialize(board);
						

			Selector *s1 = new Selector();
			m_pRoot=s1;												// Tarea raiz del arbol

			m_pRoot->addChildren(seqDetect);						// 1º Comprobamos si ha visto al prota
			m_pRoot->addChildren(seqSed);							// 2º Secuencia para ver si tiene sed
			m_pRoot->addChildren(avanzarP);							// 3º Metemos un hijo en el selector creado (Recorrido patrulla)
			m_pRoot->onInitialize(board);							// Inicializamos el selector para que el iterador apunte al principio del vector de hijos

			// Metemos todos los composites en el vector
			comp.push_back(seqDetect);
			comp.push_back(sDetect);
			comp.push_back(seqSed);
			comp.push_back(seqCVida);

			// Metemos todos las tareas en el vector
			task.push_back(avanzarP);
			task.push_back(detectP);
			task.push_back(checkSed);
			task.push_back(bAgua);
			task.push_back(cVida);
			task.push_back(huir);

			break;
		}
		case 2: // Comportamiento Enemigos Avanzados
		{
			break;
		}

	}



}


void BehaviorTree::update(Enemigo *e)
{
	Status s =m_pRoot->run(e);  								// Ejecutamos todos los hijos del selector hasta encontrar uno que tenga exito o no queden mas
	
	if(s == BH_SUCCESS) 										// Si el selector devuelve true quiere decir que se ha ejecutado una tarea con exito por lo que tenemos que salir del arbol
	{
		m_pRoot->onInitialize(board);							// Lo inicializamos para que el iterador apunte al principio del vector

		for (int i=0; i<comp.size();i++) 						// Recorremos el vector para incializar todos los composites del arbol
		{
			comp[i]->onInitialize(board);
		}

	}
}


BehaviorTree::~BehaviorTree()
{
	// Liberacion memoria ( o eso creo ) 

    delete m_pRoot;

    for(int i=0; i<comp.size(); i++)
    {
    	delete comp[i];
    }

    vector<Composite*>().swap(comp); 						 // Creamos un vector vacio sin memoria almacenada y lo cambiara por comp, liberando memoria

    for(int i2=0; i2<task.size();i2++)
    {
    	delete task[i2];
    }

    vector<Task*>().swap(task); 
}