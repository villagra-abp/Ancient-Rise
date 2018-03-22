#include "../headerfiles/FColor.h"
/*
NEGRO 		= FColor(0,		0,		0);
BLANCO 		= FColor(1.0f, 	1.0f, 	1.0f); 	
ROJO 		= FColor(1.0f,	0,		0); 
VERDE 		= FColor(0,		1.0f,	0);
AZUL 		= FColor(0,		0,		1.0f); 
AMARILLO 	= FColor(1.0f, 	1.0f,	0);
MORADO 		= FColor(1.0f,	0,		1.0f);
CYAN 		= FColor(0,		1.0f,	1.0f); 
NARANJA 	= FColor(1.0f,	0.5f,	0);
GRIS		= FColor(0.5f,	0.5f,	0.5f);	
MARRON		= FColor(0.64f,	0.16f,	0.16f);
ROSA		= FColor(0.73f,	0.56f,	0.56f);
VIOLETA		= FColor(0.31f,	0.18f,	0.31f);
ESCARLATA	= FColor(0.55f,	0.09f,	0.09f);
*/
FColor::FColor(){
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}


FColor::FColor(vec4 valores){
	color = glm::vec4(valores.x, valores.y, valores.z, valores.a);
}


FColor::FColor(glm::vec4 valores){
	color = valores;
}


FColor::FColor(float r, float g, float b, float a){
	color = glm::vec4(r,g,b,a);
}


FColor::~FColor(){}


void FColor::setColor(vec4 valores){
	color = glm::vec4(valores.x, valores.y, valores.z, valores.a);
}

void FColor::setColor(glm::vec4 valores){
	color = valores;
}


void FColor::setColor(float r, float g, float b, float a){
	color = glm::vec4(r,g,b,a);
}



glm::vec4 FColor::getColor(){
	return color;
}

