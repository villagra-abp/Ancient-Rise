#ifndef TRECURSOMALLA_H
#define TRECURSOMALLA_H

#include <iostream>
#include <unistd.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "rMesh.h"
#include "directorios.h"
#include "TRecurso.h"

using namespace std;



unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class TRecursoMalla : public TRecurso{
    public:
    	vector<Texture> textures_loaded;
        vector<rMesh> meshes;
        string directory;

        TRecursoMalla()
        {
            //cargarFichero(name);
        }
        virtual ~TRecursoMalla() = default;
        void Draw(Shader shader);	
        void cargarFichero(string nombre) override;
        string getNombre() override;

		void setNombre(string nombre) override;
		string getPath(string name);


    private:


    	string name;
        void processNode(aiNode *node, const aiScene *scene);
        rMesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             string typeName);

        

		
};

#endif //TRECURSOMALLA