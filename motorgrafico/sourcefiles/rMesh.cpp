#include "../headerfiles/rMesh.h"


rMesh::rMesh(vector<Vertex> vert, vector<unsigned int> ind, vector<TRecursoTextura*> text, TRecursoMaterial* mat){
	vertices = vert;
	indices = ind;
	textures = text;
	material = mat;

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

void rMesh::draw(Shader shader, glm::mat4 mmodelo, glm::mat4 view, glm::mat4 projection, float intensidad, glm::vec4 color, glm::vec3 luzPosicion,
		 glm::vec3 camaraPosicion){
	
	glm::vec3 ambient, diffuse, specular;
	float shininess;

	ambient = material->getAmbiente();
	diffuse = material->getDifusa();
	specular = material->getEspecular();
	shininess = material->getBrillo();

	cout<<luzPosicion.x<<" "<<luzPosicion.y<<" "<<luzPosicion.z<<endl;

	shader.use();
	//glm::mat4 projection = glm::mat4(1);
	//glm::mat4 view = glm::mat4(1);
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	// 3. now draw the object 
	//glm::mat4 model = glm::mat4(1);
	//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
	//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	shader.setMat4("model", mmodelo);
	shader.setVec4("color", color);
	shader.setVec3("luzPos", luzPosicion);
	shader.setVec3("camPos", camaraPosicion);
	shader.setFloat("lightIntensity", intensidad);

	shader.setVec3("material.ambient",  ambient);
	shader.setVec3("material.diffuse",  diffuse);
	shader.setVec3("material.specular", specular);
	shader.setFloat("material.shininess", shininess);
	
	if(textures.size() != 0)
		glBindTexture(GL_TEXTURE_2D, textures[0]->getID());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//glActiveTexture(GL_TEXTURE0);

}

void rMesh::setMaterial(TRecursoMaterial* mat){
	material = mat;
}