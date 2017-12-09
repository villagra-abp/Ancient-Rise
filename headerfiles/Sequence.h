#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>
#include "../headerfiles/Composite.h"


using namespace std;



class Sequence: public Composite
{
	public:

		
		virtual ~Sequence();
		virtual void onInitialize() override;
		virtual Status run() override;

		


	protected:
		Tasks::iterator m_CurrentChild;
		
		
};

#endif // SEQUENCE_H