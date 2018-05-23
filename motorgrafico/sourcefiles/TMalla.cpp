#include "../headerfiles/TMalla.h"

//Clase para la gestion de las mallas y su dibujado. Original.

TMalla::TMalla(){
	gestor = TGestorRecursos::getInstance();
	visible = true;
	billboard = false;
	//setMaterial("mat_naranja");
}

TMalla::TMalla(bool bill){
	gestor = TGestorRecursos::getInstance();
	visible = true;
	billboard = bill;
}

TMalla::~TMalla(){

}

void TMalla::cargarMalla(string path){
	mesh = gestor->getRecursoMalla(path);
}

void TMalla::setMaterial(string nombre){
	//material = gestor->getRecursoMat(nombre);
}


void TMalla::beginDraw(TDatosEntidad *datos){
	if(visible){
//		glm::vec3 ambient = material->getAmbiente();
//		glm::vec3 diffuse = material->getDifusa();
//		glm::vec3 specular = material->getEspecular();
//		float shininess =	material->getBrillo();
		if(billboard){
//		cout<<mmodelo[0][0]<<" "<<mmodelo[0][1]<<" "<<mmodelo[0][2]<<" "<<mmodelo[0][3]<<" "<<endl;
//		cout<<mmodelo[1][0]<<" "<<mmodelo[1][1]<<" "<<mmodelo[1][2]<<" "<<mmodelo[1][3]<<" "<<endl;
//		cout<<mmodelo[2][0]<<" "<<mmodelo[2][1]<<" "<<mmodelo[2][2]<<" "<<mmodelo[2][3]<<" "<<endl;
//		cout<<mmodelo[3][0]<<" "<<mmodelo[3][1]<<" "<<mmodelo[3][2]<<" "<<mmodelo[3][3]<<" "<<endl;
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					if(j == i)
						mmodelo[i][j] = 1;
					else
						mmodelo[i][j] = 0;
				}
			}
//		cout<<mmodelo[0][0]<<" "<<mmodelo[0][1]<<" "<<mmodelo[0][2]<<" "<<mmodelo[0][3]<<" "<<endl;
//		cout<<mmodelo[1][0]<<" "<<mmodelo[1][1]<<" "<<mmodelo[1][2]<<" "<<mmodelo[1][3]<<" "<<endl;
//		cout<<mmodelo[2][0]<<" "<<mmodelo[2][1]<<" "<<mmodelo[2][2]<<" "<<mmodelo[2][3]<<" "<<endl;
//		cout<<mmodelo[3][0]<<" "<<mmodelo[3][1]<<" "<<mmodelo[3][2]<<" "<<mmodelo[3][3]<<" "<<endl;
		}
		
		mesh->draw(mmodelo, datos); // (...) //Dibujado del recurso de malla OpenGL
	}
}
void TMalla::endDraw(){
}

void TMalla::isVisible(bool flag){
	visible = flag;
}
