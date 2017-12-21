/* 
 * File:   pj.h
 * Author: Victor Conejero Vicente
 */

#ifndef PJ_H
#define PJ_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Pj
{
    public:
        
        Pj(Vector2f position, float xlength, float pendValue);               //ctr
        
        // Updates.
        virtual void update(float dirx);
        virtual bool checkInSigth(Vector2f objPos);
        
        // Seters.        
        virtual void setXRange(float xRange);
        virtual void setYPend(float yPend);

        // Geters.
        virtual sf::RectangleShape* getPersonaje();
        virtual sf::ConvexShape* getAreaVision();
        virtual float getXRange();
        virtual float getYPend();

        virtual ~Pj();                        //dtr 
        
    private:
        
        // Methods.
        virtual void visionBuilder ();
        
        // Variables.
        RectangleShape* personaje;
        ConvexShape* areaVision;
        ConvexShape* areaVisionNeg;
        bool lastFacedDir;
        float visionXmax;
        float valorPendiente;
};

#endif /* PJ_H */

