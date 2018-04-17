#ifndef FSKYBOX_H
#define FSKYBOX_H

#include "TMotorTAG.h"

class FSkybox {
public:
	FSkybox();
	virtual ~FSkybox();

	void setSkybox(vector<string> paths);
	void isActive(bool flag){active = flag;}

	bool getActive() { return active;}
	TNodo* getNodo() { return nodo;}
private:
	bool active;

	TNodo *nodo, *padre;
};	

#endif //FSKYBOX_H