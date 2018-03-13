#ifndef OBJETO_H
#define OBJETO_H

#include "vec3.h"

class Objeto{
	public:

		Objeto();
		~Objeto();

		void Rotar(vec3 rotacion, float angulo);
		void Escalar(vec3 escalado);
		void Mover(vec3 posicion);

		void setPosicion(vec3 posicion);
		void setRotacion(vec3 rotacion, float angulo);

		void isVisible(bool flag);

		void Unir(Objeto padre);

		void cargarMalla(string path);

	protected:
		TNodo* getNodo();

	private:

		bool visible;
		TNodo* padre;
		TNodo* malla, rotacion, traslacion;




};


#endif //OBJETO_H