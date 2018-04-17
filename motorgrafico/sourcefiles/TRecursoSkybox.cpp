#include "../headerfiles/TRecursoSkybox.h"

Shader *rMesh::shader = nullptr;


TRecursoSkybox::TRecursoSkybox(vector<string> paths){
	if(shader == nullptr)
		shader = new Shader("motorgrafico/shaders/skybox.vs", "motorgrafico/shaders/skybox.fs");

	setupSkybox(paths);
}

void TRecursoSkybox::setupSkybox(vector<string> paths){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    loadCubeMap(paths);

}

void TRecursoSkybox::loadCubeMap(vector<string> paths){
	glGenTextures(1, &skyboxID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);

	int width, height, nrChannels;
	unsigned char *data;

	for(GLuint i = 0; i < paths.size(); i++){
		data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if(data){
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		} else{
			cout<< "Fallo en la carga de textura de la skybox: " <<paths[i]<<endl;
			stbi_image_free(data);
		}
	}
	glTexParametri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParametri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParametri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParametri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParametri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

TRecursoSkybox::~TRecursoSkybox(){

}



void TRecursoSkybox::draw(TDatosEntidad *datos)
{
    glDepthFunc(GL_LEQUAL);
    skyboxShader.use();

    glm::mat4 view = *(datos->view);
    glm::mat4 projection = *(datos->projection);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}  



