#ifndef REPEAT_H
#define REPEAT_H

#include <iostream>
#include <vector>
#include "../headerfiles/Decorator.h"

using namespace std;


// Decorador para repetir el comportamiento hijo un numero determinado de veces
class Repeat : public Decorator
{
	public:

		Repeat(Task* child);
		void setCount(int count);
		void onInitialize();
		Status run();


	protected:
		 int m_iLimit;  	// Establece el limite de repeticiones del comportamiento hijo
		 int m_iCounter; 	// Contador para saber por que repetición vamos
};

#endif // REPEAT_H