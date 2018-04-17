#include "../headerfiles/TSkybox.h"


TSkybox::TSkybox(){}


TSkybox::TSkybox(vector<string> path){
	cargarSkybox(path);
}


TSkybox::~TSkybox(){}


void TSkybox::cargarSkybox(vector<string> path){
	skybox = TGestorRecursos::getInstance()->getRecursoSkybox(path);
}


void TSkybox::beginDraw(TDatosEntidad *datos){
	skybox->draw(datos);
}


void TSkybox::endDraw(){}

