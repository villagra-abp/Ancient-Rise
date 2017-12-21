#include "Pj.h"


Pj::Pj(Vector2f position, float xlength, float pendValue){      //CONSTRUCTOR DE PERSONAJE
    
    //Definicion de variables.
    personaje = new sf::RectangleShape;
    areaVision = new sf::ConvexShape;
    areaVisionNeg = new sf::ConvexShape;
    lastFacedDir = true;
    
    //Parametros para el rango de vision del personaje.
    visionXmax = xlength;
    valorPendiente = pendValue;

    //RectangleShape personaje;
    personaje->setSize(Vector2f(20,20));
    personaje->setOutlineColor(Color::Green);
    personaje->setOutlineThickness(8);
    personaje->setPosition(position.x, position.y);

    //Llamada al contructor del area de vision del personaje.
    this->visionBuilder();     
}

void Pj::visionBuilder (){  //Aplica (y=x*m), con x(max) = visionXmax , m = valorPendiente .
    

    //xlength, x maxima, en realidad es el unico parametro que se recibe, Y se calcula a partir de este
    //float y = 120.0; // y maxima, se aplicara desde el punto inicial hacia arriba y hacia abajo
    float ylength = visionXmax * valorPendiente;
    float xlength = visionXmax;
    Vector2f pjPos = personaje->getPosition();

    
    //2 formas convexas que engloban el area de vision de un personaje. 1-> Mirando Derecha, 2-> Mirando Izquierda  
    // de 6 puntos. O 3 simplificada.

    //Facing Right
    areaVision->setPointCount(3);

    // definiendo puntos ( + 20 para las posiciones hacia la derecha pues punto inicial del pj en esquina sup izq. ancho pj = 20)
    areaVision->setPoint(0, sf::Vector2f(pjPos.x+20, pjPos.y));                     //Punto inicial, altura de los ojos. (MIN X, 1/2 Y)
    areaVision->setPoint(1, sf::Vector2f(pjPos.x+xlength+20, pjPos.y-ylength));     //Altura maxima del rango de vision, Final superior parte triangular ( X, MIN Y)
    areaVision->setPoint(2, sf::Vector2f(pjPos.x+xlength+20, pjPos.y+ylength));     //Altura minima del rango de vision, Final inferior parte triangular ( X, MAX Y)
    
    //Facing Left
    areaVisionNeg->setPointCount(3);

    // definiendo puntos
    areaVisionNeg->setPoint(0, sf::Vector2f(pjPos.x, pjPos.y));                     //Punto inicial, altura de los ojos. (MIN X, 1/2 Y)
    areaVisionNeg->setPoint(1, sf::Vector2f(pjPos.x-xlength, pjPos.y-ylength));     //Altura maxima del rango de vision, Final superior parte triangular ( X, MIN Y)
    areaVisionNeg->setPoint(2, sf::Vector2f(pjPos.x-xlength, pjPos.y+ylength));     //Altura minima del rango de vision, Final inferior parte triangular ( X, MAX Y)
}

void Pj::update(float dirx){             //Movimientos del personaje.
    
    personaje->setPosition(personaje->getPosition().x+dirx, personaje->getPosition().y);

    if(dirx>0){
        lastFacedDir=true;
    } else if(dirx<0){
        lastFacedDir=false;
    }
}

bool Pj::checkInSigth(Vector2f objPos){

    bool inSight = false;  //Valor para retorno, si la posicion recibida se encuentra
    // dentro del rango de vision sera TRUE.

    float pjxmin;          // Valor real en la ventana del punto del area con X Minima.
    float pjxmax;          // Valor real en la ventana del punto del area con X Maxima.
    float pjymin;          // Valor real en la ventana del punto del area con Y Minima, respecto a la X recibida.        
    float pjymax;          // Valor real en la ventana del punto del area con Y Maxima, respecto a la X recibida.
    float xReady;

    if(lastFacedDir){ 	//Mira hacia derecha
	pjxmin = personaje->getPosition().x + 20;
	pjxmax = personaje->getPosition().x + 20 + visionXmax;
        xReady = objPos.x - pjxmin;
    }else{				//Mira hacia izquierda
	pjxmin = personaje->getPosition().x - visionXmax;
	pjxmax = personaje->getPosition().x;
        xReady = -(objPos.x - pjxmax);
    }

    if(objPos.x < pjxmax && objPos.x > pjxmin){
        pjymax = xReady * valorPendiente + personaje->getPosition().y;
	pjymin = personaje->getPosition().y - (pjymax-personaje->getPosition().y);
        
        if(objPos.y > pjymin && objPos.y < pjymax){
            inSight = true;
	}
    }

    return inSight;
}

// SETERS.

void Pj::setXRange(float xRange){
    visionXmax = xRange;

    this->visionBuilder();
}

void Pj::setYPend(float yPend){
    valorPendiente = yPend;

    this->visionBuilder();
}

// GETERS.

float Pj::getXRange(){
    return visionXmax;
}
float Pj::getYPend(){
    return valorPendiente;
}

sf::RectangleShape* Pj::getPersonaje(){
    return personaje;
}

sf::ConvexShape* Pj::getAreaVision(){
    if(lastFacedDir){
        return areaVision;
    }else{
        return areaVisionNeg;
    }
}


Pj::~Pj(){      //DESTRUCTOR DE PERSONAJE
    delete [] personaje;

    delete [] areaVision;
    areaVision = nullptr;

    delete [] areaVisionNeg;
    areaVisionNeg = nullptr;
}
