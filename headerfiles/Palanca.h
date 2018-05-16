#ifndef PALANCA_H
#define PALANCA_H

#include "../headerfiles/Objeto.h"



class Palanca : public Objeto
{

	public:

		Palanca(Posicion* pos);
		virtual void update() override;
		virtual ~Palanca();
		void* getNode();

	private:

};

#endif // PALANCA_H

