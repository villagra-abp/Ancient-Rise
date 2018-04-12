#include "../headerfiles/TRecursoTextura.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

TRecursoTextura::TRecursoTextura(string path, string type){
	nombre = path;
	tipo = type;
	path = "resources/" + path;
	const char* c = path.c_str();
	unsigned char *data= stbi_load(c, &width, &height, &nrChannels, 0);

	setupText(data);
}


void TRecursoTextura::setupText(unsigned char* data){
	glGenTextures(1,&id);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(data){
	//Hay que usar RGBA luego
		cout<<width<<" "<<height<<endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		cout<<"Fallo en la carga de textura "<<nombre<<endl;
	}
	stbi_image_free(data);

}



void TRecursoTextura::setNombre(string name){
	nombre = name;
}

void TRecursoTextura::setTipo(string type){
	tipo = type;
}

unsigned int TRecursoTextura::getID(){
	return id;
}

string TRecursoTextura::getNombre(){
	return nombre;
}

string TRecursoTextura::getTipo(){
	return tipo;
}