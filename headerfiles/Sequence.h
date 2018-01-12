#ifndef SEQUENCE_H
#define SEQUENCE_H


#include "../headerfiles/Composite.h"




class Sequence: public Composite
{
	public:

		
		virtual ~Sequence();
		virtual void onInitialize(Blackboard *b) override;
		virtual Status run(Enemigo *e) override;

		


	protected:
		Tasks::iterator m_CurrentChild;
		
		
};

#endif // SEQUENCE_H