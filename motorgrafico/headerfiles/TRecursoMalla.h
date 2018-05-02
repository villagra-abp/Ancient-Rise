#ifndef TRECURSOMALLA_H
#define TRECURSOMALLA_H

#include <iostream>
#include <unistd.h>


#include "rMesh.h"
#include "directorios.h"
#include "TRecurso.h"
#include "TRecursoMaterial.h"
#include "TRecursoTextura.h"
#include "TDatosEntidad.h"

using namespace std;





class TRecursoMalla : public TRecurso{
    public:
    	

        TRecursoMalla();
        virtual ~TRecursoMalla() = default;
        void draw(glm::mat4 mmodelo, TDatosEntidad *datos);	
        void drawBoundingBox(glm::mat4 mmodelo, TDatosEntidad *datos);

        void addMesh(rMesh mesh);
       
        string getNombre() override;
        string getDirectorio();
//      string getPath(string name);

        float getMaxX(){return max_x;}
        float getMaxY(){return max_y;}
        float getMaxZ(){return max_z;}

        float getMinX(){return min_x;}
        float getMinY(){return min_y;}
        float getMinZ(){return min_z;}

        void setMaxX(float max){max_x = max;}
        void setMaxY(float max){max_y = max;}
        void setMaxZ(float max){max_z = max;}

        void setMinX(float min){min_x = min;}
        void setMinY(float min){min_y = min;}
        void setMinZ(float min){min_z = min;}

		void setNombre(string nombre) override;
		void setDirectorio(string direct);


    private:

        static Shader* boundingShader;

        string directory;
    	string name;
        float max_x, min_x, max_y, min_y, max_z, min_z;

        
        vector<TRecursoTextura*> textures_loaded;
        vector<rMesh> meshes;
        

		
};

#endif //TRECURSOMALLA

