#ifndef RMESH_H
#define RMESH_H

/*
*	Clase para estructurar un poco los datos del recurso modelo
*/

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <unistd.h>
#include <glm/glm.hpp>

#include "../headerfiles/Shader.h"
#include "TRecursoMaterial.h"
#include "TRecursoTextura.h"
//#include "TGestorRecursos.h"

using namespace std;

struct Vertex{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
/*
struct Texture{
	unsigned int id;
	string type;
	string path;
};
*/

  
class rMesh{
	public:
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<TRecursoTextura*> textures;
		unsigned int VAO;

		rMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<TRecursoTextura*> textures, TRecursoMaterial* material);
		void draw(glm::mat4 mmodelo, glm::mat4 view, glm::mat4 projection, vector<float> intensidad, vector<glm::vec4> color, vector<glm::vec3> luzPosicion, 
			glm::vec3 camaraPosicion);

		void setMaterial(TRecursoMaterial* mat);

	private:
		unsigned int  VBO, EBO;

		static Shader *shaderText, *shaderNoText;
		static TRecursoTextura *estandar;

		void setupMesh();
		TRecursoMaterial* material;
		
};

#endif //RMESH_H