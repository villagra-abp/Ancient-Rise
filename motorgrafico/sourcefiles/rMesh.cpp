#include "../headerfiles/rMesh.h"

Shader *rMesh::shaderText = nullptr;
Shader *rMesh::shaderNoText = nullptr;
TRecursoTextura *rMesh::estandar = nullptr;

rMesh::rMesh(vector<Vertex> vert, vector<unsigned int> ind, vector<TRecursoTextura*> text, TRecursoMaterial* mat){
	vertices = vert;
	indices = ind;
	textures = text;
	material = mat;

	if(shaderText == nullptr)
		shaderText = new Shader("motorgrafico/shaders/vertex.vs", "motorgrafico/shaders/fragment1.fs");
	if(shaderNoText == nullptr)
		shaderNoText = new Shader("motorgrafico/shaders/vertex.vs", "motorgrafico/shaders/noText.fs");
	if(estandar == nullptr)
		estandar = new TRecursoTextura("blanco.png", "texture_diffuse");
	
	setupMesh();
}




void rMesh::setupMesh(){

	glGenBuffers(1,&VBO);
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//for(int i = 0; i < vertices.size(); i++)
	//		cout<<"x: "<<vertices[i].Normal.x<<" y: "<<vertices[i].Normal.y<<" z: "<<vertices[i].Normal.z<<endl;

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

void rMesh::draw(glm::mat4 mmodelo, TDatosEntidad *datos){
	//glm::mat4 view, glm::mat4 projection, vector<glm::vec4> color, vector<glm::vec3> luzPosicion, glm::vec3 camaraPosicion
	Shader* shader = shaderNoText;
	glm::vec3 ambient, diffuse, specular;
	float shininess;

//	if(textures.size() != 0)
		shader = shaderText;
//	else
//		shader = shaderNoText;
	ambient = material->getAmbiente();
	diffuse = material->getDifusa();
	specular = material->getEspecular();
	shininess = material->getBrillo();

	glm::mat4 projection = datos->projection;
	glm::mat4 view = datos->view;
	glm::vec3 camaraPosicion = datos->camaraPosicion;

	//Datos luces puntuales
	vector<glm::vec4> colorPuntual = datos->colorPuntual;
	vector<glm::vec3> posicionPuntual = datos->posicionPuntual;
	vector<vector<float>> atenuacionPuntual = datos->atenuacionPuntual;

	//Datos luz dirigida
	glm::vec3 colorDir = datos->colorDir;
	glm::vec3 directionDir = datos->directionDir;
	//cout<<luzPosicion.x<<" "<<luzPosicion.y<<" "<<luzPosicion.z<<endl;

	glm::vec3 positionFlash = datos->positionFlash;
 	glm::vec3 directionFlash = datos->directionFlash;
 	glm::vec3 colorFlash = datos->colorFlash;

 	vector<float> cortes = datos->corteFlash;
 	vector<float> atenuacionFlash = datos->atenuacionFlash;

	shader->use();
	//glm::mat4 projection = glm::mat4(1);
	//glm::mat4 view = glm::mat4(1);
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	// 3. now draw the object 
	//glm::mat4 model = glm::mat4(1);
	//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
	//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	shader->setMat4("model", mmodelo);
//	shader->setVec4("color", color);
//	shader->setVec3("luzPos", luzPosicion);
	shader->setVec3("camPos", camaraPosicion);

	shader->setVec3("material.ambient",  ambient);
	shader->setVec3("material.diffuse",  diffuse);
	shader->setVec3("material.specular", specular);
	shader->setFloat("material.shininess", shininess);

	//declarando lucecitas
	//Puntuales
	shader->setFloat("pointLights[0].linear", atenuacionPuntual[0][0]);
	shader->setFloat("pointLights[0].quadratic", atenuacionPuntual[0][1]);
	shader->setVec3("pointLights[0].position", posicionPuntual[0]);
	shader->setVec3("pointLights[0].color", colorPuntual[0]);

//	cout<<"Posicion puntual 1: "<<posicionPuntual[0].x<<" "<<posicionPuntual[0].y<<" "<<posicionPuntual[0].z<<endl;
//	cout<<"Color puntual 1: "<<colorPuntual[0].x<<" "<<colorPuntual[0].y<<" "<<colorPuntual[0].z<<endl;

//	shader->setFloat("pointLights[1].linear",atenuacionPuntual[1][0]);
//	shader->setFloat("pointLights[1].quadratic", atenuacionPuntual[1][1]);
//	shader->setVec3("pointLights[1].position", luzPosicion[1]);
//	shader->setVec3("pointLights[1].color", color[1]);

//	shader->setFloat("pointLights[2].linear",atenuacionPuntual[2][0]);
//	shader->setFloat("pointLights[2].quadratic", atenuacionPuntual[2][1]);
//	shader->setVec3("pointLights[2].position", luzPosicion[2]);
//	shader->setVec3("pointLights[2].color", color[2]);

	//Dirigidas
	shader->setFloat("flashLight.linear", atenuacionFlash[0]);
	shader->setFloat("flashLight.quadratic", atenuacionFlash[1]);
	shader->setVec3("flashLight.position", positionFlash);
	shader->setVec3("flashLight.direction", directionFlash);
	shader->setVec3("flashLight.color", colorFlash);
	shader->setFloat("flashLight.cutOff", cortes[0]);
	shader->setFloat("flashLight.extCutOff",cortes[1]);

	//Direccionales

	shader->setVec3("dirLight.color", colorDir);
	shader->setVec3("dirLight.direction", directionDir);
	
//	if(textures.size() != 0)
//		glBindTexture(GL_TEXTURE_2D, textures[0]->getID());

	if(textures.size() == 0){														//Sin texturas
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, estandar->getID());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, estandar->getID());
	} else if(textures.size() == 1){												//Solo textura difusa
		glActiveTexture(GL_TEXTURE0);		
		glBindTexture(GL_TEXTURE_2D, textures[0]->getID());		//Difusa

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, estandar->getID());		//Especular
	} else {																		//Con textura difusa y especular
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]->getID());		//DIfusa

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]->getID());		//Especular
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//glActiveTexture(GL_TEXTURE0);

}

void rMesh::setMaterial(TRecursoMaterial* mat){
	material = mat;
}