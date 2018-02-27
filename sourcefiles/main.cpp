//#include "../headerfiles/Mundo.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

#include "../headerfiles/Shader.h"
#include "../headerfiles/Camera.h"


/*
Estos son los 5 sub namespace del motor de Irrlicht

1º irr::core--> En este podemos encontrar las clases basicas como vectores, planos, arrays, listas y demas
2º irr::gui--> Contiene clases utiles para la facil creacion de una interfaz grafica de usuario
3º irr::io-->  Proporciona interfaces para la entrada/salida. Lectura y escritura de ficheros, acceso a ficheros zip, ficheros xml..
4º irr::scene--> Se encuentra toda la gestion de la escena
5º irr::video--> Contiene clases para acceder al driver del video. Todo el rendererizado 3d o 2d se realiza aqui
*/
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

/*
*
*SHAAADEEEEEEER
*
*
*/

  


/*
*
*	MEEEEEEEEEEEEEEEEEESH
*
*/
class Mesh{
	public:
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		void Draw(Shader shader);

	private:
		unsigned int VAO, VBO, EBO;

		void setupMesh();
};

Mesh::Mesh(vector<Vertex> vert, vector<unsigned int> ind, vector<Texture> text){
	vertices = vert;
	indices = ind;
	textures = text;

	setupMesh();
}
//Hay que retocar
void Mesh::setupMesh(){
	glGenBuffers(1,&VBO);
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
					&indices[0], GL_STATIC_DRAW);

	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,Normal));

	//vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,TexCoords));

	glBindVertexArray(0);

	
}

void Mesh::Draw(Shader shader){
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for(unsigned int i = 0; i < textures.size(); i++){
		glActiveTexture(GL_TEXTURE0 + i);

		string number;
		string name = textures[i].type;
		if(name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if(name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.setFloat(("material."+name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


/*
*MODEEEEEEEEEEEEEEL
*
*/

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model 
{
    public:
    	/*Data*/
    	vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string directory;
        /*  Functions   */
        Model(char *path)
        {
            loadModel(path);
        }
        void Draw(Shader shader);	
    private:
        /*  Model Data  */

        /*  Functions   */
        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             string typeName);
};

void Model::Draw(Shader shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}  

void Model::loadModel(string path){
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}  

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

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
    	vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                        aiTextureType_DIFFUSE, "texture_diffuse");
    	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    	vector<Texture> specularMaps = loadMaterialTextures(material, 
                                        aiTextureType_SPECULAR, "texture_specular");
    	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}  

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName){

	vector<Texture> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){

		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;

		for(unsigned int j = 0; j < textures_loaded.size(); j++){
			if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0){
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if(!skip){
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}		
	}
	return textures;
}

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma){
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


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{

	char* ironMan = "resources/IronMan.obj";
	int screenWidth = 800;
	int screenHeight = 600;

	sf::RenderWindow* ventana = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "Ancient Rise", sf::Style::Titlebar | sf::Style::Close);
    /*creo una vista*/
    glewInit();
    ventana->setFramerateLimit(60);
	sf::View view(sf::FloatRect(0, 0, 1000, 600));
	
	view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	ventana->setView(view);
	ventana->setActive(true);
	//Mundo* mundo = new Mundo(ventana);


	// define a 120x50 rectangle
	sf::RectangleShape rectangle(sf::Vector2f(20, 20));

	// change the size to 100x100
	//rectangle.setSize(sf::Vector2f(10, 10));
	rectangle.setFillColor(sf::Color(100, 250, 50));

	/*ASSIMP*/

	Model ourModel(ironMan);


	/* PRUEBAS OPENGL
	*/
/*
	float vertices[] = {
		//First triangle
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
    	

	};	
	float vertices2[] = {
		0.5f,  -0.5f, 0.0f,
    	-0.5f,-0.5f,0.0f,
    	-0.5f, 0.5f, 0.0f
	};

	



	unsigned int VBO1, VBO2;
	unsigned int VAO1;
	unsigned int VAO2;

	glGenBuffers(1,&VBO1);
	glGenBuffers(1,&VBO2);
	glGenVertexArrays(1,&VAO1);
	glGenVertexArrays(1,&VAO2);

	glBindVertexArray(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

/*
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const char* vertexShaderSource = "#version 330 core\n"
							"layout (location =0) in vec3 position; \n"
							"void main(){\n"
							"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
							"}\0";

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

	const char* fragmentShaderSource = "#version 330 core\n"
							"out vec4 FragColor;\n"
							"void main(){\n"
							"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
							"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
*/
   	Shader ourShader("motorgrafico/shaders/vertex.vs", "motorgrafico/shaders/fragment.fs");

/*
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	*/


	while(ventana->isOpen())
	{

		char inputKey;
		bool keyPressed;
		ventana->clear(sf::Color::Black);
		//Evento
		sf::Event* evento = new sf::Event; 
		//Obtener eventos
		while (ventana->pollEvent(*evento))
		{
		    switch (evento-> type)
		    {
		        case sf::Event::Closed:
		       
		            ventana->close();
		        break;

		        case sf::Event::KeyPressed:
		        {    
		            inputKey = evento->key.code;
		            //std::cout<<evento->key.code<<std::endl;		
		            if(inputKey == 16){
		            	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		            }
		            else if(inputKey == 4){
		            	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		            }
		            keyPressed = true;
		           
		        }   
		        break;
		    }
		    
		    
		}
        //	ventana.close();
		//

		/*OPENGL PRUEBAS*/

		// 0. copy our vertices array in a buffer for OpenGL to use
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 1. then set the vertex attributes pointers
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(0);  
		// 2. use our shader program when we want to render an object
		//glUseProgram(shaderProgram);
		ourShader.use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float) screenHeight, 0.1f, 100.f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		// 3. now draw the object 
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		ourShader.setMat4("model", model);
		ourModel.Draw(ourShader);
		//glBindVertexArray(VAO1);
		//glDrawArrays(GL_TRIANGLES,0,3);		//someOpenGLFunctionThatDrawsOurTriangle(); 
	
		//glBindVertexArray(VAO2);
		//glDrawArrays(GL_TRIANGLES,0,3);
	/* BUCLE PRINCIPAL DEL JUEGO */

		/*OPENGLPRUEBAS*/



		 //ventana->draw(rectangle);
		ventana->display();

		/* ACTUALIZAMOS EL MUNDO */
	//	mundo->update();
		
		//ventana.display();
		
	}

	/*
	After we are done with the render loop, we have to delete the Irrlicht
	Device created before with createDevice(). In the Irrlicht Engine, you
	have to delete all objects you created with a method or function which
	starts with 'create'. The object is simply deleted by calling ->drop().
	See the documentation at irr::IReferenceCounted::drop() for more
	information.
	*/

	/**

	Hay que eliminar el objete device que creamos anteriormente antes de terminar con el bucle de render
	En el motor de irrlicht todos los objetos que se han creado mediante una funcion que empieza por
	'create' deben ser eliminados y esto se hace simplemente llamanado a '->drop()'

	**/

	//ventana.close();
}

