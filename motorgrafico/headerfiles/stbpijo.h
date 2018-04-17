//façade para la libreria stbi_image

#ifndef STBPIJO_H
#define STBPIJO_H

#include <iostream>

using namespace std;

class stbpijo{
public:
	stbpijo();
	virtual ~stbpijo() = default;

	unsigned char* stbpijo_load_image(string path ,int* width, int* height, int* nrChannels);
	void stbpijo_free(unsigned char* data);

private:
};

#endif