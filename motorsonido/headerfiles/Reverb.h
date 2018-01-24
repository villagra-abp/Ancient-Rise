#ifndef REVERB_H
#define REVERB_H

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>

class Reverb{
public:
	Reverb(FMOD::Reverb3D* cosa);
	~Reverb();

	float getX();
	float getY();
	float getZ();
	float getMin();
	float getMax();

	void setTipo(const char* tipo);
	void setAtributos3D(float x, float y, float z, float min, float max);



private:
	FMOD::Reverb3D* reverb;


};

#endif //REVERB_H