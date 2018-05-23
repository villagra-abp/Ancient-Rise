#include "../headerfiles/TRecursoTextura.h"

//Clase para la gestion de texturas. Original. Se aprendió sobre texturas en https://learnopengl.com/Getting-started/Textures

TRecursoTextura::TRecursoTextura(string path, string type){
	nombre = path;
	tipo = type;
	path = "resources/" + path;
	const char* c = path.c_str();
	unsigned char *data= pijo->stbpijo_load_image(c, &width, &height, &nrChannels);

	setupText(data);
}


void TRecursoTextura::setupText(unsigned char* data){
	glGenTextures(1,&id);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum formato;
	if(data){
	//Hay que usar RGBA luego
		//cout<<width<<" "<<height<<endl;
		if(nrChannels == 1)
			formato = GL_RED;
		else if(nrChannels == 3)
			formato = GL_RGB;
		else if (nrChannels == 4)
			formato = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, formato, width, height, 0, formato, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		cout<<"Fallo en la carga de textura "<<nombre<<endl;
	}
	pijo->stbpijo_free(data);

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