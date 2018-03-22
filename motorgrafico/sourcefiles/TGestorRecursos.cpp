#include "../headerfiles/TGestorRecursos.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

static TGestorRecursos* instance = NULL;

TGestorRecursos* TGestorRecursos::getInstance(){
	if(instance == NULL)
		instance = new TGestorRecursos();

	return instance;
}


TGestorRecursos::TGestorRecursos(){
	shader = new Shader("motorgrafico/shaders/vertex.vs", "motorgrafico/shaders/fragment1.fs");
}

TGestorRecursos::~TGestorRecursos(){

}

TRecursoMalla* TGestorRecursos::getRecursoMalla(string path){
	TRecursoMalla* r = dynamic_cast<TRecursoMalla*>(buscarRecurso(path));

	if(r == NULL){
		
		r = cargarFichero(path);
		r->setNombre(path);
		recursos.push_back(r);
	}

	return r;
}

/*
TRecursoMaterial* TGestorRecursos::getRecursoMat(string nombre){
		Tipo* r = dynamic_cast<Tipo*>(buscarRecurso(nombre_fichero));

		if(r == NULL){
			r = new Tipo();

			r->cargarFichero(nombre_fichero);
			r->setNombre(nombre_fichero);
			recursos.push_back(r);
		}

}
*/


TRecurso* TGestorRecursos::buscarRecurso(string path){
	bool flag = false;
	TRecurso *rec = nullptr;

	for(int i=0;i<recursos.size() && !flag;i++){
		if(recursos[i]->getNombre()==path){
			flag = true;
			rec = recursos[i];
		}
	}
	return rec;
}



Shader* TGestorRecursos::getShader(){
	return shader;
}

//ASSIMP

TRecursoMalla* TGestorRecursos::cargarFichero(string path){

	//string path = getPath(name);
	TRecursoMalla *malla = new TRecursoMalla();

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        
    }
    malla->setDirectorio(path.substr(0, path.find_last_of('/')));

    processNode(scene->mRootNode, scene, malla);

    return malla;
}

void TGestorRecursos::processNode(aiNode *node, const aiScene *scene, TRecursoMalla* malla)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {	
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        malla->addMesh(processMesh(mesh, scene));	
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {	
        processNode(node->mChildren[i], scene, malla);
    }
}  

rMesh TGestorRecursos::processMesh(aiMesh *mesh, const aiScene *scene)
{

    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    TRecursoMaterial* rMaterial;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector; 

        //Posiciones
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z; 
		vertex.Position = vector;
		//Normales
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;  
		//Texturas
		if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
		    glm::vec2 vec;
		    vec.x = mesh->mTextureCoords[0][i].x; 
		    vec.y = mesh->mTextureCoords[0][i].y;
		    vertex.TexCoords = vec;
		}
		else
    		vertex.TexCoords = glm::vec2(0.0f, 0.0f);  

        vertices.push_back(vertex);
    }
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
	    aiFace face = mesh->mFaces[i];
	    for(unsigned int j = 0; j < face.mNumIndices; j++)
	        indices.push_back(face.mIndices[j]);
	    
	}  
    // process material
    if(mesh->mMaterialIndex >= 0)
    {	
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        //Material
        aiString name;
        material->Get(AI_MATKEY_NAME, name);
        string nombre = name.C_Str();
        //cout<<nombre<<endl;

       rMaterial = dynamic_cast<TRecursoMaterial*>(buscarRecurso(nombre));

       if(rMaterial == nullptr){
       		aiColor3D ambiente, difusa, especular;
        	float shininess;

        	material->Get(AI_MATKEY_COLOR_DIFFUSE, difusa);
        	material->Get(AI_MATKEY_COLOR_SPECULAR, especular);
        	material->Get(AI_MATKEY_COLOR_AMBIENT, ambiente);

        	material->Get(AI_MATKEY_SHININESS, shininess);

        	//glm::vec3 ambient(ambiente.r, ambiente.g, ambiente.b);
        	//glm::vec3 diffuse(difusa.r, difusa.g, difusa.b); 
        	//glm::vec3 specular(especular.r, especular.g, especular.b);

        	glm::vec3 ambient = glm::vec3(ambiente.r, ambiente.g, ambiente.b);
        	glm::vec3 diffuse = glm::vec3(difusa.r, difusa.g, difusa.b);
        	glm::vec3 specular = glm::vec3(especular.r, especular.g, especular.b);


       		rMaterial = new TRecursoMaterial(nombre, ambient, diffuse, specular, shininess);
			recursos.push_back(rMaterial);
  		}


       	//Texturas
    	vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                        aiTextureType_DIFFUSE, "texture_diffuse");
    	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    	vector<Texture> specularMaps = loadMaterialTextures(material, 
                                        aiTextureType_SPECULAR, "texture_specular");
    	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    
    return rMesh(vertices, indices, textures, rMaterial);
}  

vector<Texture> TGestorRecursos::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName){
 
	vector<Texture> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		/*
		for(unsigned int j = 0; j < textures_loaded.size(); j++){
			if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0){
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		*/
		if(!skip){
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), "directory");
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			//textures_loaded.push_back(texture);
		}		
	}
	return textures;
}

unsigned int TGestorRecursos::TextureFromFile(const char *path, const string &directory, bool gamma){
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char * data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if(data){
		GLenum format;
		if(nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}