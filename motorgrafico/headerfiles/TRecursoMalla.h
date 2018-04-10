#ifndef TRECURSOMALLA_H
#define TRECURSOMALLA_H

#include <iostream>
#include <unistd.h>


#include "rMesh.h"
#include "directorios.h"
#include "TRecurso.h"
#include "TRecursoMaterial.h"
#include "TRecursoTextura.h"

using namespace std;





class TRecursoMalla : public TRecurso{
    public:
    	vector<TRecursoTextura*> textures_loaded;
        vector<rMesh> meshes;

        TRecursoMalla()
        {
            //cargarFichero(name);
        }
        virtual ~TRecursoMalla() = default;
        void draw(Shader shader, glm::mat4 mmodelo, glm::mat4 view, glm::mat4 projection, float intensidad, glm::vec4 color, glm::vec3 luzPosicion,
                    glm::vec3 camPosicion);	

        void addMesh(rMesh mesh);
       
        string getNombre() override;
        string getDirectorio();
        string getPath(string name);

		void setNombre(string nombre) override;
		void setDirectorio(string direct);


    private:

        string directory;
    	string name;
        

        

		
};

#endif //TRECURSOMALLA

