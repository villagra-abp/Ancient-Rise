#ifndef TRECURSOTEXTURA_H
#define TRECURSOTEXTURA_H

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "TRecurso.h"
#include "stbpijo.h"

using namespace std;

class TRecursoTextura : public TRecurso {
public:
	TRecursoTextura(string nombre, string tipo);
	virtual ~TRecursoTextura() = default;

	unsigned int getID();
	string getNombre() override;
	string getTipo();

	void setNombre(string nombre) override;
	void setTipo(string tipo);
	void setupText(unsigned char* data);

private:

	string nombre, tipo;
	int width, height, nrChannels;
	unsigned int id;
	stbpijo* pijo;
};


#endif //TRECURSOTEXTURA_H