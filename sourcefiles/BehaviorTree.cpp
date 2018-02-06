#include "../headerfiles/BehaviorTree.h"
#include "../headerfiles/AvanzarPatrulla.h"
#include "../headerfiles/DetectarProta.h"
#include "../headerfiles/ComprobarSed.h"
#include "../headerfiles/BuscarAgua.h"
#include "../headerfiles/ComprobarVida.h"
#include "../headerfiles/Selector.h"
#include "../headerfiles/Huir.h"
#include "../headerfiles/Repeat.h"
#include "../headerfiles/CheckAlarmaDes.h"
#include "../headerfiles/ActivarAlarma.h"
#include "../headerfiles/Atacar.h"
#include "../headerfiles/ComprobarHambre.h"
#include "../headerfiles/BuscarComida.h"
#include "../headerfiles/AlarmaSonando.h"
#include "../headerfiles/IrAlarma.h"
#include "../headerfiles/AliadoCerca.h"
#include "../headerfiles/OrdenAtaque.h"
#include "../headerfiles/EjecutarOrden.h"
#include "../headerfiles/CheckOrden.h"

BehaviorTree::BehaviorTree(int c, Blackboard *b):board(b)
{
	/* Seleccionamos el comportamiento del enemigo */
	switch (c)
	{
		case 1: /* Comportamiento Enemigos Basicos*/
		 {
			/* CREACION DE TAREAS */
			AvanzarPatrulla *avanzarP = new AvanzarPatrulla();  	// Patrulla
			DetectarProta *detectP = new DetectarProta();  			// Deteccion Protagonista
			ComprobarSed *checkSed = new ComprobarSed();			// Comprobacion sed
			ComprobarHambre *checkHambre = new ComprobarHambre();   // COmprobacion hambre
			BuscarAgua *bAgua = new BuscarAgua();					// Busqueda de agua
			BuscarComida *bComida = new BuscarComida(); 			// Busqueda de comida
			ComprobarVida *cVida = new ComprobarVida();				// Comprobar Vida del enemigo
			Huir *huir = new Huir(); 								// Huir
			CheckAlarmaDes *checkAD = new CheckAlarmaDes(); 		// Comprobar alarma cerca y desactivada
			ActivarAlarma *actAlarm = new ActivarAlarma(); 			// Activar la alarma
			Atacar *ataque = new Atacar(); 							// Ataque
			AlarmaSonando *alarmS = new AlarmaSonando(); 			// Alarma sonando cerca
			IrAlarma *irAlarm = new IrAlarma();						// Ir hacia la alarma
			EjecutarOrden *ejOrden = new EjecutarOrden(); 			// Ejecutar ordenes
			CheckOrden *checkOrden = new CheckOrden(); 				// Comprobar ordenes


			/* INICIALIZACIONES DE TAREAS */

			detectP->onInitialize(b); 								// Es necesario inicializar para poder pasar la blackboard
			avanzarP->onInitialize(b); 	
			checkSed->onInitialize(b);
			bAgua->onInitialize(b);
			cVida->onInitialize(b);
			huir->onInitialize(b);
			checkAD->onInitialize(b);
			actAlarm->onInitialize(b);
			ataque->onInitialize(b);
			checkHambre->onInitialize(b);
			bComida->onInitialize(b);
			alarmS->onInitialize(b);
			irAlarm->onInitialize(b);
			ejOrden->onInitialize(b);
			checkOrden->onInitialize(b);


			/* ORDENES DE SUPERIORES */
			Sequence *seqOrden = new Sequence();

			seqOrden->addChildren(checkOrden);
			seqOrden->addChildren(ejOrden);
			seqOrden->onInitialize(board);
			
			/*    DETECCION DEL PROTA 		*/ 

			/* Sequencia para ver la vida del enemigo y huir si es baja */

			Sequence *seqCVida = new Sequence();

			seqCVida->addChildren(cVida);
			seqCVida->addChildren(huir);
			seqCVida->onInitialize(board);	

			/* Sequencia para comprobar si hay una alarma cerca y desactivada , para activarla */

			Sequence *seqAlarmaDes = new Sequence();

			seqAlarmaDes->addChildren(checkAD);
			seqAlarmaDes->addChildren(actAlarm);
			seqAlarmaDes->onInitialize(board);

			/* Selector para ver que hacer cuando detectamos al prota (Huir - Activar Alarma - Atacar)*/

			Selector *sDetect = new Selector();

			sDetect->addChildren(seqCVida);
			sDetect->addChildren(seqAlarmaDes);
			sDetect->addChildren(ataque);
			sDetect->onInitialize(board);							

			/* Sequencia para comprobar si detectamos al prota y ver que hacer */

			Sequence *seqDetect = new Sequence();

			seqDetect->addChildren(detectP);
			seqDetect->addChildren(sDetect);
			seqDetect->onInitialize(board);


			/*    ALARMA SONANDO		*/ 
			/* Sequencia para comprobar si la alarma esta sonando y elegir si ir a la alarma o explorar la zona */
			Sequence *seqAlarmAct = new Sequence();

			seqAlarmAct->addChildren(alarmS);
			seqAlarmAct->addChildren(irAlarm);
			seqAlarmAct->onInitialize(board);


			/*    BUSQUEDA DE AGUA		*/ 

			/* Sequencia para comprobar sed y buscar agua */
			Sequence *seqSed = new Sequence(); 				
			
			seqSed->addChildren(checkSed); 							// Añadimos sus hijos
			seqSed->addChildren(bAgua);
			seqSed->onInitialize(board);


			/*    BUSQUEDA DE COMIDA	*/ 

			/* Sequencia para comprobar hambre y buscar comida */
			Sequence *seqHambre = new Sequence(); 

			seqHambre->addChildren(checkHambre);
			seqHambre->addChildren(bComida);
			seqHambre->onInitialize(board);



						
			/*    RAIZ DEL ARBOL		*/ 

			Selector *s1 = new Selector();
			m_pRoot=s1;												// Tarea raiz del arbol

			m_pRoot->addChildren(seqOrden);							// 1º Comprobamos si ha recibido una orden
			m_pRoot->addChildren(seqDetect);						// 2º Comprobamos si ha visto al prota
			m_pRoot->addChildren(seqAlarmAct); 						// 3º Comprobamos si no hay ninguna alarma cerca sonando
			m_pRoot->addChildren(seqSed);							// 4º Secuencia para ver si tiene sed
			m_pRoot->addChildren(seqHambre); 						// 5º Secuencia para ver si tiene hambre
			m_pRoot->addChildren(avanzarP);							// 6º Metemos un hijo en el selector creado (Recorrido patrulla)
			m_pRoot->onInitialize(board);							// Inicializamos el selector para que el iterador apunte al principio del vector de hijos



			// Metemos todos los composites/Decoradores en el vector
			comp.push_back(seqDetect);
			comp.push_back(sDetect);
			comp.push_back(seqSed);
			comp.push_back(seqCVida);
			comp.push_back(seqAlarmaDes);
			comp.push_back(seqHambre);
			comp.push_back(seqAlarmAct);
			comp.push_back(seqOrden);
			

			// Metemos todos las tareas en el vector
			task.push_back(avanzarP);
			task.push_back(detectP);
			task.push_back(checkSed);
			task.push_back(bAgua);
			task.push_back(cVida);
			task.push_back(huir);
			task.push_back(checkAD);
			task.push_back(actAlarm);
			task.push_back(ataque);
			task.push_back(bComida);
			task.push_back(alarmS);
			task.push_back(irAlarm);
			task.push_back(checkOrden);
			task.push_back(ejOrden);

			break;
		}
		case 2: /* Comportamiento Enemigos Elites */
		{	
			/* CREACION DE TAREAS */
			AvanzarPatrulla *avanzarP = new AvanzarPatrulla();  	// Patrulla
			DetectarProta *detectP = new DetectarProta();  			// Deteccion Protagonista
			ComprobarSed *checkSed = new ComprobarSed();			// Comprobacion sed
			ComprobarHambre *checkHambre = new ComprobarHambre();   // COmprobacion hambre
			Atacar *ataque = new Atacar(); 							// Ataque
			BuscarAgua *bAgua = new BuscarAgua();					// Busqueda de agua
			BuscarComida *bComida = new BuscarComida(); 			// Busqueda de comida
			AlarmaSonando *alarmS = new AlarmaSonando(); 			// Alarma sonando cerca
			AliadoCerca *aliadoC = new AliadoCerca(); 				// Aliado cerca
			OrdenAtaque *orAtaq = new OrdenAtaque(); 				// Orden de Ataque
			CheckAlarmaDes *checkAlDes = new CheckAlarmaDes(); 		// Comprobar Alarma desactivada


			/* INICIALIZACIONES DE TAREAS */
			avanzarP->onInitialize(b); 
			detectP->onInitialize(b);
			checkSed->onInitialize(b);
			bAgua->onInitialize(b);
			checkHambre->onInitialize(b);
			bComida->onInitialize(b);
			alarmS->onInitialize(b);
			aliadoC->onInitialize(b);
			orAtaq->onInitialize(b);
			ataque->onInitialize(b);
			checkAlDes->onInitialize(b);


			/* Sequencia para comprobar alarma cerca y desactivada; y mandar activarla */
			Sequence *seqAlOrden = new Sequence();
			seqAlOrden->addChildren(checkAlDes);
			seqAlOrden->onInitialize(board);

			/* Selector para seleccionar la orden ha mandar (activar alarma - Atacar ) */
			Selector *selOrden = new Selector();
			selOrden->addChildren(seqAlOrden);
			selOrden->addChildren(orAtaq);
			selOrden->onInitialize(board);


			/* Sequencia para comprobar si hay un aliado basico cerca y mandarle una orden */
			Sequence *seqAliadoC = new Sequence();
			seqAliadoC->addChildren(aliadoC);
			seqAliadoC->addChildren(selOrden);
			seqAliadoC->onInitialize(board);

			/* Selector para ver que hacer cuando hemos detectado al prota */
			Selector *selDetect = new Selector();
			selDetect->addChildren(seqAliadoC);
			selDetect->addChildren(ataque);
			selDetect->onInitialize(board);

			/* Sequencia para comprobar si detectamos al prota y ver que hacer */
			Sequence *seqDetect = new Sequence();
			seqDetect->addChildren(detectP);
			seqDetect->addChildren(selDetect);
			seqDetect->onInitialize(board);

			/*    BUSQUEDA DE AGUA		*/ 

			/* Sequencia para comprobar sed y buscar agua */
			Sequence *seqSed = new Sequence(); 				
			
			seqSed->addChildren(checkSed); 							// Añadimos sus hijos
			seqSed->addChildren(bAgua);
			seqSed->onInitialize(board);


			/*    BUSQUEDA DE COMIDA	*/ 

			/* Sequencia para comprobar hambre y buscar comida */
			Sequence *seqHambre = new Sequence(); 

			seqHambre->addChildren(checkHambre);
			seqHambre->addChildren(bComida);
			seqHambre->onInitialize(board);

			/*    ALARMA SONANDO		*/ 
			/* Sequencia para comprobar si la alarma esta sonando y ver si hay algun aliado cerca */
			Sequence *seqAlarmAct = new Sequence();

			seqAlarmAct->addChildren(alarmS);
			seqAlarmAct->addChildren(seqAliadoC);
			seqAlarmAct->onInitialize(board);

			/*    RAIZ DEL ARBOL		*/ 

			Selector *s1 = new Selector();
			m_pRoot=s1;												// Tarea raiz del arbol

			m_pRoot->addChildren(seqDetect); 						// 1º Comprobamos si ha detectado al prota
			m_pRoot->addChildren(seqAlarmAct); 						// 2º Comprobamos si hay una alarma sonando
			m_pRoot->addChildren(seqSed);							// 3º Si tenemos sed
			m_pRoot->addChildren(seqHambre); 						// 4º SI tenemos hambre
			m_pRoot->addChildren(avanzarP); 						// 5º Avanzar patrulla
			m_pRoot->onInitialize(board);


			// Metemos todos los composites/Decoradores en el vector
			comp.push_back(seqDetect);
			comp.push_back(seqSed);
			comp.push_back(seqHambre);
			comp.push_back(seqAlarmAct);
			comp.push_back(seqAliadoC);
			comp.push_back(selOrden);
			comp.push_back(selDetect);
			comp.push_back(seqAlOrden);


			// Metemos todos las tareas en el vector
			task.push_back(avanzarP);
			task.push_back(detectP);
			task.push_back(checkSed);
			task.push_back(bAgua);
			task.push_back(checkHambre);
			task.push_back(bComida);
			task.push_back(alarmS);
			task.push_back(aliadoC);
			task.push_back(orAtaq);
			task.push_back(ataque);
			task.push_back(checkAlDes);


			break;
		}
		case 3: /* Comportamiento Enemigos Avanzados (Igual que los basicos pero sin tener que atender a ordenes de los superiores)*/
		{
			/* CREACION DE TAREAS */
			AvanzarPatrulla *avanzarP = new AvanzarPatrulla();  	// Patrulla
			DetectarProta *detectP = new DetectarProta();  			// Deteccion Protagonista
			ComprobarSed *checkSed = new ComprobarSed();			// Comprobacion sed
			ComprobarHambre *checkHambre = new ComprobarHambre();   // COmprobacion hambre
			BuscarAgua *bAgua = new BuscarAgua();					// Busqueda de agua
			BuscarComida *bComida = new BuscarComida(); 			// Busqueda de comida
			ComprobarVida *cVida = new ComprobarVida();				// Comprobar Vida del enemigo
			Huir *huir = new Huir(); 								// Huir
			CheckAlarmaDes *checkAD = new CheckAlarmaDes(); 		// Comprobar alarma cerca y desactivada
			ActivarAlarma *actAlarm = new ActivarAlarma(); 			// Activar la alarma
			Atacar *ataque = new Atacar(); 							// Ataque
			AlarmaSonando *alarmS = new AlarmaSonando(); 			// Alarma sonando cerca
			IrAlarma *irAlarm = new IrAlarma();						// Ir hacia la alarma


			/* INICIALIZACIONES DE TAREAS */
			detectP->onInitialize(b); 								// Es necesario inicializar para poder pasar la blackboard
			avanzarP->onInitialize(b); 	
			checkSed->onInitialize(b);
			bAgua->onInitialize(b);
			cVida->onInitialize(b);
			huir->onInitialize(b);
			checkAD->onInitialize(b);
			actAlarm->onInitialize(b);
			ataque->onInitialize(b);
			checkHambre->onInitialize(b);
			bComida->onInitialize(b);
			alarmS->onInitialize(b);
			irAlarm->onInitialize(b);

			/*    DETECCION DEL PROTA 		*/ 
			/* Sequencia para ver la vida del enemigo y huir si es baja */
			Sequence *seqCVida = new Sequence();

			seqCVida->addChildren(cVida);
			seqCVida->addChildren(huir);
			seqCVida->onInitialize(board);	

			/* Sequencia para comprobar si hay una alarma cerca y desactivada , para activarla */
			Sequence *seqAlarmaDes = new Sequence();

			seqAlarmaDes->addChildren(checkAD);
			seqAlarmaDes->addChildren(actAlarm);
			seqAlarmaDes->onInitialize(board);

			/* Selector para ver que hacer cuando detectamos al prota (Huir - Activar Alarma - Atacar)*/
			Selector *sDetect = new Selector();

			sDetect->addChildren(seqCVida);
			sDetect->addChildren(seqAlarmaDes);
			sDetect->addChildren(ataque);
			sDetect->onInitialize(board);							

			/* Sequencia para comprobar si detectamos al prota y ver que hacer */
			Sequence *seqDetect = new Sequence();

			seqDetect->addChildren(detectP);
			seqDetect->addChildren(sDetect);
			seqDetect->onInitialize(board);


			/*    ALARMA SONANDO		*/ 
			/* Sequencia para comprobar si la alarma esta sonando y elegir si ir a la alarma o explorar la zona */
			Sequence *seqAlarmAct = new Sequence();

			seqAlarmAct->addChildren(alarmS);
			seqAlarmAct->addChildren(irAlarm);
			seqAlarmAct->onInitialize(board);


			/*    BUSQUEDA DE AGUA		*/ 
			/* Sequencia para comprobar sed y buscar agua */
			Sequence *seqSed = new Sequence(); 				
			
			seqSed->addChildren(checkSed); 							// Añadimos sus hijos
			seqSed->addChildren(bAgua);
			seqSed->onInitialize(board);


			/*    BUSQUEDA DE COMIDA	*/ 
			/* Sequencia para comprobar hambre y buscar comida */
			Sequence *seqHambre = new Sequence(); 

			seqHambre->addChildren(checkHambre);
			seqHambre->addChildren(bComida);
			seqHambre->onInitialize(board);

			/*    RAIZ DEL ARBOL		*/ 
			Selector *s1 = new Selector();
			m_pRoot=s1;												// Tarea raiz del arbol

			m_pRoot->addChildren(seqDetect);						// 1º Comprobamos si ha visto al prota
			m_pRoot->addChildren(seqAlarmAct); 						// 2º Comprobamos si no hay ninguna alarma cerca sonando
			m_pRoot->addChildren(seqSed);							// 3º Secuencia para ver si tiene sed
			m_pRoot->addChildren(seqHambre); 						// 4º Secuencia para ver si tiene hambre
			m_pRoot->addChildren(avanzarP);							// 5º Metemos un hijo en el selector creado (Recorrido patrulla)
			m_pRoot->onInitialize(board);							// Inicializamos el selector para que el iterador apunte al principio del vector de hijos

			// Metemos todos los composites/Decoradores en el vector
			comp.push_back(seqDetect);
			comp.push_back(sDetect);
			comp.push_back(seqSed);
			comp.push_back(seqCVida);
			comp.push_back(seqAlarmaDes);
			comp.push_back(seqHambre);
			comp.push_back(seqAlarmAct);

			// Metemos todos las tareas en el vector
			task.push_back(avanzarP);
			task.push_back(detectP);
			task.push_back(checkSed);
			task.push_back(bAgua);
			task.push_back(cVida);
			task.push_back(huir);
			task.push_back(checkAD);
			task.push_back(actAlarm);
			task.push_back(ataque);
			task.push_back(bComida);
			task.push_back(alarmS);
			task.push_back(irAlarm);

			break;
		}

	}



}


void BehaviorTree::update(Enemigo *e)
{
	
	Status s =m_pRoot->run(e);  								// Ejecutamos todos los hijos del selector y cuando uno se ejecute con exito entonces salimos del arbol
	
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

    vector<Task*>().swap(comp); 						 // Creamos un vector vacio sin memoria almacenada y lo cambiara por comp, liberando memoria

    for(int i2=0; i2<task.size();i2++)
    {
    	delete task[i2];
    }

    vector<Task*>().swap(task); 

}