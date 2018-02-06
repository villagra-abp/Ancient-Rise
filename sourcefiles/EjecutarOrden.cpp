#include "../headerfiles/EjecutarOrden.h"

Status EjecutarOrden::run(Enemigo *e)
{   
   e->setCombate(false);

   switch(e->getOrden())
   {
      case 1: // Orden de Ataque
      {
          Status s = at->run(e);
          return s;
          break;
      }
      case 2: // Orden Activar Alarma
      {
        break;
      }

      case 3: //Orden Explorar
      {
        break;
      }

      case 4: // Orden IrAlarma
      {

        break;
      }
   }



   return BH_FAILURE;
}

void EjecutarOrden::onInitialize(Blackboard *b)
{
	  board = b;
	  enemBActual = nullptr;
	  at->onInitialize(b);
}

EjecutarOrden::~EjecutarOrden()
{
    board = nullptr;
}