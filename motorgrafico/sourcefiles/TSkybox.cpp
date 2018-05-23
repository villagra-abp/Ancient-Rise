#include "../headerfiles/TSkybox.h"

//Clase para la gestion del nodo que contendra la skybox. Original.

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

