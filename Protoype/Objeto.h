/* 
 * File:   Objeto.h
 * Author: Victor Conejero Vicente
 */

#ifndef OBJETO_H
#define OBJETO_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Objeto
{
    public:
        
        Objeto(int idCont, Color color, float x, float y, float radius);        //ctr
        
        // Seters.
        virtual bool setState(bool state);

        // Geters.
        virtual int getId();
        virtual sf::CircleShape* getCirculo();
        virtual bool getState();

        virtual ~Objeto();      //dtr 
        
    private:

        // Variables.
        CircleShape* obj;
        int id;
        bool alreadyIN;
};

#endif /* OBJETO_H */

