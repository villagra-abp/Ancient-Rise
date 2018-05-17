#ifndef PUERTA_H
#define PUERTA_H

#include "../headerfiles/Objeto.h"



class Puerta : public Objeto
{

	public:

		Puerta(Posicion* pos);
		virtual void update() override;
		virtual ~Puerta();
		void* getNode();

	private:

};

#endif // PUERTA_H

