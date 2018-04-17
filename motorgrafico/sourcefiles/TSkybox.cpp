#include "../headerfiles/TSkybox.h"


TSkybox::TSkybox(){}


TSkybox::TSkybox(string path){
	cargarSkybox(path);
}


TSkybox::~TSkybox(){}


void TSkybox::cargarSkybox(string path){
	skybox = TGestorRecursos::getInstance()->getSkybox(path);
}


void TSkybox::beginDraw(TDatosEntidad *datos){
	skybox->draw(datos);
}


void TSkybox::endDraw(){}

