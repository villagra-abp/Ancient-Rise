#ifndef CANAL_H
#define CANAL_H

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>

class Canal{
public:
	Canal(FMOD::Channel* channel);
	~Canal();
	FMOD::Channel* getCanal();
	void setCanal(FMOD::Channel* channel);
private:
	FMOD::Channel* canal;
};

#endif //CANAL_H