/*#ifndef RESOURCES_H
#define RESOURCES_H

using namespace io;
using namespace std;


class Resources{

public: 
	static Resources* getInstance();
	bool initialise();
	void cleanUp();
	bool loadAll();


	bool loadFont(string filename);
	Font &getFont(string filename);

	bool loadTexture(string filename);
    Texture &getTexture(string filename);
        
    bool loadImage(string filename);
    Image &getImage(string filename);

    bool loadModel(string filename);
    Model &getModel(string filename);


private:
	Resources();
	//map<string, Font*> fonts;
	map<string, Texture*> textures;
	//map<string, Image*> images;
	map<string, Models*> models;

}


#endif //RESOURCES_H

*/