#ifndef IRALARMA_H
#define IRALARMA_H

#include "../headerfiles/Task.h"

// Tarea (Accion) para saber ir hacia la alarma que esta sonando
class IrAlarma : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~IrAlarma();


	private:
		
		Blackboard *board;
	    f32 frameDeltaTime;		  // Tiempo
	    vector<Objeto*> a;
<<<<<<< HEAD
	    scene::ISceneNode* enemigoNode;
		
		//Datos de alarma
	    core::vector3df alarmaPosition;
=======
	    void* enemigoNode;
		
		//Datos de alarma
	    Posicion* alarmaPosition;
>>>>>>> 89a4e0e937ec5c5d2e6bf07d446473ff8dc14279
		float alarmaX;
		int distanciaAlarma;
		
};

<<<<<<< HEAD
#endif // IRALARMA_H
=======
#endif // IRALARMA_H
>>>>>>> 89a4e0e937ec5c5d2e6bf07d446473ff8dc14279
