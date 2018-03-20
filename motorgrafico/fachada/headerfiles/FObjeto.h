#ifndef FOBJETO_H
#define FOBJETO_H

#include "vec3.h"
#include "FEntidad.h"

class FObjeto : public FEntidad{
	public:

		FObjeto();
		virtual ~FObjeto();

		void Rotar(vec3 rot, float ang) override;
		void Escalar(vec3 escalado);
		void Mover(vec3 pos) override;

		void setPosicion(vec3 pos) override;
		void setRotacion(vec3 rot, float ang) override;

		void isActive(bool flag) override;

		void Unir(FEntidad* padre) override;

		void setMalla(string path);
		void setMaterial(string nombre);

		bool getActive() override;
		TNodo* getNodo() override;
		vec3 getPosicion();

	private:

		bool active;
		TNodo *padre;
		TNodo *nodo, *rotacion, *traslacion;




};


#endif //FOBJETO_H