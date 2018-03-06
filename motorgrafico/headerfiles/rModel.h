#ifndef RMODEL_H
#define RMODEL_H

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif //STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <unistd.h>

#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../headerfiles/rMesh.h"

using namespace std;



unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model 
{
    public:
    	vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string directory;

        Model(const char *path)
        {
            loadModel(path);
        }
        ~Model();
        void Draw(Shader shader);	
    private:



        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             string typeName);
};

#endif //RMODEL_H