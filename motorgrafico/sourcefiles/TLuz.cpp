#include "../headerfiles/TLuz.h"

TLuz::TLuz(){
	intensidad = 1;
	color = glm::vec4(1,1,1,1);
}

TLuz::TLuz(glm::vec4 colo){
	color = colo;
}

TLuz::TLuz(float inten, glm::vec4 colo){
	intensidad = inten;
	color = colo;
}


TLuz::~TLuz(){

}



glm::vec4 TLuz::getColor(){
	return color;
}


float TLuz::getIntensidad(){
	return intensidad;
}


void TLuz::setActive(bool flag){
	active = flag;
}


void TLuz::setIntensidad(float inten){
	intensidad = inten;
}	


void TLuz::setColor(glm::vec4 colo){
	color = colo;
}

