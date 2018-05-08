#ifndef FBILLBOARD_H
#define FBILLBOARD_H

#include "FObjeto.h"

class FBillboard : public FObjeto{
public:
	FBillboard();
	virtual ~FBillboard();
	void Rotar(vec3 rot, float ang) override;

	void setRotacion(vec3 rot, float ang) override;

	void setMalla(string path);

private:

};

#endif //FBILLBOARD_H