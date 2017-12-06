#ifndef DECORATOR_H
#define DECORATOR_H

#include <iostream>
#include <vector>
#include <Behavior.h>


using namespace std;

// ES UNA RAMA EN BEHAVIOR TREE CON UN UNICO HIJO QUE SIRVE PARA ENVOLVER COMPORTAMIENTOS 
// CON OTROS PARA AÑADIR DETALLES ( EJEMPLO: COMPORTAMIENTO QUE HACE QUE SE REPITA SU HIJO N VECES)
class Decorator : public Behavior
{
	public:

		Decorator(Behavior* child);


	protected:
		Behavior* m_pChild;
};

#endif // DECORATOR_H