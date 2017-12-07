#ifndef SELECTOR_H
#define SELECTOR_H

#include <iostream>
#include <vector>
#include <Composite.h>


using namespace std;



class Selector: public Composite
{
	public:

		
		virtual ~Selector();
		virtual void onInitialize() override;
		virtual Status run() override;

		


	protected:
		Tasks::iterator m_Current; // PARA SABER EN QUE HIJO NOS ENCONTRAMOS ACTUALMENTE ( EL ITERATOR ES UN OBJETO QUE APUNTANDO A UN ELEMENTO DE UN CONJUNTO DE ELEMENTOS 
									// (COMO UN ARRAY) TIENE LA HABILIDAD DE ITERAR A TRAVES DE LOS ELEMENTOS DE ESE RANGO QUE ESTA USANDO MEDIANTE DIFERENTES OPERADORES )
		
		
};

#endif // SELECTOR_H