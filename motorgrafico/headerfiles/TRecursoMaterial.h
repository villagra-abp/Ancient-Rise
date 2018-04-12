#ifndef TRECURSOMATERIAL_H
#define TRECURSOMATERIAL_H

#include <iostream>
#include <unistd.h>

#include "TRecurso.h"
#include "glm/glm.hpp"


class TRecursoMaterial : public TRecurso{

public:
	TRecursoMaterial();
	TRecursoMaterial(string nombre, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	virtual ~TRecursoMaterial();

	virtual string getNombre() override;
	float getBrillo();
	glm::vec3 getAmbiente();
	glm::vec3 getDifusa();
	glm::vec3 getEspecular();

	virtual void setNombre(string nombre) override;
	//virtual void cargarFichero(string nombre) override;

private:
	string nombre;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};



#endif //TRECURSOMATERIAL_H