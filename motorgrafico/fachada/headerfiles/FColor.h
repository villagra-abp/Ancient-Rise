#ifndef FCOLOR_H
#define FCOLOR_H

#include <glm/glm.hpp>
#include "vec4.h"
/*
enum class Color{
		FColor NEGRO = new FColor(0,0,0,1),
		FColor BLANCO	= new FColor(1,1,1,1)
	};
*/
class FColor{

public:


	//NEGRO =  = FColor(0,		0,		0,	1);
	/*
	//Colores predeterminados
	static const FColor    	NEGRO 		=  new	FColor(0,0,0);
	static const FColor  	BLANCO; 	//	= 	glm::vec4(1.0f, 	1.0f,	1.0f);
	static const FColor  	ROJO; 		//= 	glm::vec4(1.0f, 	0,		0);
	static const FColor  	VERDE; 		//= 	glm::vec4(0,		1.0f,	0);
	static const FColor  	AZUL; 		//= 	glm::vec4(0,		0,		1.0f);
	static const FColor  	AMARILLO; 	//= 	glm::vec4(1.0f,		1.0f,	0);
	static const FColor  	MORADO; 	//	= 	glm::vec4(1.0f,		0,		1.0f);
	static const FColor  	CYAN; 		//= 	glm::vec4(0,		1.0f,	1.0f);
	static const FColor  	NARANJA; 	//	= 	glm::vec4(1.0f,		0.5f,	0);
	static const FColor  	GRIS;		//	=	BLANCO * 0.5f;
	static const FColor  	MARRON;		//=	glm::vec4(0.64f,	0.16f,	0.16f);
	static const FColor  	ROSA;		//	=	glm::vec4(0.73f,	0.56f,	0.56f);
	static const FColor  	VIOLETA;	//	=	glm::vec4(0.31f,	0.18f,	0.31f);
	static const FColor  	ESCARLATA;	//=	glm::vec4(0.55f,	0.09f,	0.09f);
*/

	/*
	static const glm::vec4 BLANCO 		= 	glm::vec4(1.0f, 	1.0f,	1.0f);
	static const glm::vec4 ROJO 		= 	glm::vec4(1.0f, 	0,		0);
	static const glm::vec4 VERDE 		= 	glm::vec4(0,		1.0f,	0);
	static const glm::vec4 AZUL 		= 	glm::vec4(0,		0,		1.0f);
	static const glm::vec4 AMARILLO 	= 	glm::vec4(1.0f,		1.0f,	0);
	static const glm::vec4 MORADO 		= 	glm::vec4(1.0f,		0,		1.0f);
	static const glm::vec4 CYAN 		= 	glm::vec4(0,		1.0f,	1.0f);
	static const glm::vec4 NARANJA 		= 	glm::vec4(1.0f,		0.5f,	0);
	static const glm::vec4 MAGENTA 		= 	glm::vec4(1.0f,		0,		1.0f);
	static const glm::vec4 GRIS			=	BLANCO * 0.5f;
	static const glm::vec4 MARRON		=	glm::vec4(0.64f,	0.16f,	0.16f);
	static const glm::vec4 ROSA			=	glm::vec4(0.73f,	0.56f,	0.56f);
	static const glm::vec4 VIOLETA		=	glm::vec4(0.31f,	0.18f,	0.31f);
	static const glm::vec4 ESCARLATA	=	glm::vec4(0.55f,	0.09f,	0.09f);

	*/
//	Color algo = Color::BLANCO;

	FColor();
	FColor(vec4 valores);
	FColor(glm::vec4 valores);
	FColor(float r, float g, float b, float a);
	~FColor();

	void setColor(vec4 valores);
	void setColor(glm::vec4 valores);
	void setColor(float r, float g, float b, float a);
	//void setColor(string nombre);

	glm::vec4 getColor();
private:
	glm::vec4 color;
};


#endif //FCOLOR_H