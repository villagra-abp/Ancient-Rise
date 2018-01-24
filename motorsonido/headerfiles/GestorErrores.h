#ifndef GESTORERRORES_H
#define GESTORERRORES_H

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <cstddef>
#include <cstdio>
#include <iostream>

class GestorErrores{
public:
	~GestorErrores();
	static GestorErrores* getInstance();

	void errcheck(FMOD_RESULT result);

private:
	GestorErrores();
};

#endif //GESTORERRORES_H