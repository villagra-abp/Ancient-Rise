#include "../headerfiles/stbpijo.h"


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

stbpijo::stbpijo(){}

unsigned char* stbpijo::stbpijo_load_image(string path ,int* width, int* height, int* nrChannels){
	unsigned char *data;

	data = stbi_load(path.c_str(), width, height, nrChannels, 0);

	return data;
}


void stbpijo::stbpijo_free(unsigned char* data){
	stbi_image_free(data);
}

