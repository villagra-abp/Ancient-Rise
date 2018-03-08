#ifndef RMESH_H
#define RMESH_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <unistd.h>
#include <glm/glm.hpp>

#include "../headerfiles/Shader.h"

using namespace std;

struct Vertex{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

struct Texture{
	unsigned int id;
	string type;
	string path;
};


  
class rMesh{
	public:
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		unsigned int VAO;

		rMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		void Draw(Shader shader);

	private:
		unsigned int  VBO, EBO;

		void setupMesh();
		
};

#endif //RMESH_H