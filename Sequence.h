#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>
#include <Composite.h>


using namespace std;

// PERMITE AL BT SEGUIR UN PLAN A PROPOSITO. LAS SECUENCIAS EJECUTAN CADA UNO DE SUS COMPORTAMIENTOS HIJOS 
//EN UNA SECUENCIA HASTA QUE TODOS LOS HIJOS HAN SIDO EJECUTADOS CORRECTAMENTE O HASTA QUE UNO DE LOS HIJOS
//FALLE
class Sequence: public Composite
{
	protected:

		virtual ~Sequence();

		virtual void onInitialize() override;  // OVERRIDE INDICA QUE ESTAMOS INVAIDANDO OTRO FUNCION VIRTUAL
		virtual Status update() override;


		Behaviors::iterator m_CurrentChild; // PARA SABER EN QUE HIJO NOS ENCONTRAMOS ACTUALMENTE ( EL ITERATOR ES UN OBJETO QUE APUNTANDO A UN ELMENTO DE UN CONJUNTO DE ELEMENTOS 
											// (COMO UN ARRAY) TIENE LA HABILIDAD DE ITERAR A TRAVES DE LOS ELEMENTOS DE ESE RANGO QUE ESTA USANDO MEDIANTE DIFERENTES OPERADORES )
};

#endif // SEQUENCE_H