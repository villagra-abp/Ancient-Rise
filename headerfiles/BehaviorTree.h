#ifndef BEHAVIORTREE_H
#define BEHAVIORTREE_H

#include <iostream>
#include <vector>
#include <irrlicht.h>
#include "../headerfiles/AvanzarPatrulla.h"
#include "../headerfiles/DetectarProta.h"
#include "../headerfiles/Selector.h"



using namespace std;
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;





class BehaviorTree
{
	public:

		BehaviorTree(int t, Blackboard *b);
		void update();

		virtual ~BehaviorTree();

	private:

		//Task* m_pRoot;
		int tipo;
		Blackboard *board;
		Selector sel;

		
};

#endif // BEHAVIORTREE_H