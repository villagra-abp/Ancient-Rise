#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <vector>
#include <Behavior.h>


using namespace std;

// PARA EVITAR CODIGO REDUNDANTE EN LAS SUBCLASES 
class Composite : public Behavior
{
	public:
		void addChild(Behavior* child);
		void removeChild(Behavior* child);
		void clearChildren();


	protected:
		typedef vector<Behavior*> Behaviors;
		Behaviors m_Children;
};

#endif // COMPOSITE_H