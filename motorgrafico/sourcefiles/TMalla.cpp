#include "../headerfiles/TMalla.h"

TMalla::TMalla(){
	gestor = TGestorRecursos::getInstance();
	visible = true;
	setMaterial("mat_naranja");
}
TMalla::~TMalla(){

}

void TMalla::cargarMalla(string path){
	mesh = gestor->getRecursoMalla(path);
}

void TMalla::setMaterial(string nombre){
	//material = gestor->getRecursoMat(nombre);
}

void TMalla::beginDraw(glm::mat4 view, glm::mat4 projection, float intensidad, glm::vec4 color, glm::vec3 luzPosicion, glm::vec3 camaraPosicion){
	if(visible){
//		glm::vec3 ambient = material->getAmbiente();
//		glm::vec3 diffuse = material->getDifusa();
//		glm::vec3 specular = material->getEspecular();
//		float shininess =	material->getBrillo();
		
		mesh->draw(*gestor->getShader(), mmodelo, view, projection, intensidad, color, luzPosicion, camaraPosicion); // (...) //Dibujado del recurso de malla OpenGL
	}
}
void TMalla::endDraw(){
}

void TMalla::isVisible(bool flag){
	visible = flag;
}
