#ifndef TGESTORRECURSOS_H
#define TGESTORRECURSOS_H

#include <iostream>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TRecursoMaterial.h"
#include "Shader.h"

class TGestorRecursos{
public:
	static TGestorRecursos* getInstance();
	virtual ~TGestorRecursos();
	/*
	template <class Tipo>
	
	TRecurso* getRecurso(string nombre_fichero){

		Tipo* r = dynamic_cast<Tipo*>(buscarRecurso(nombre_fichero));

		if(r == NULL){
			r = new Tipo();

			r->cargarFichero(nombre_fichero);
			r->setNombre(nombre_fichero);
			recursos.push_back(r);
		}

		return r;
	}*/
	TRecursoMalla* getRecursoMalla(string path);
//	TRecursoMaterial* getRecursoMat(string nombre);
//	TRecursoTexture *getRecursoT(string nombre);
	TRecurso* buscarRecurso(string nombre);

	Shader* getShader();

private:
	TGestorRecursos();
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
 	TRecursoMalla* cargarFichero(string nombre);
	void processNode(aiNode *node, const aiScene *scene, TRecursoMalla* malla);
    rMesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             string typeName);

	vector<TRecurso*> recursos;
	Shader* shader;
	int nivel;

};


#endif //TGESTORRECURSOS_H