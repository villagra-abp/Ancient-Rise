/* 
 * File:   main.cpp
 * Author: Victor Conejero Vicente
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
//#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tinyxml2.h>
#include <array>

// CLASES.
#include "Pj.h"
#include "Objeto.h"

using namespace std;
using namespace sf;

/*
 * 
 */

//Tamanyo de la Window (X, Y)
#define kWinX 800
#define kWinY 400

//------------------------------------------------------------------------------

int main(int argc, char** argv) {
    
//--Window Definition
    RenderWindow window(sf::VideoMode(kWinX, kWinY), "demoSensores");
    
//--Personaje
    sf::Vector2f pos = sf::Vector2f(20,200);
    Pj* pj1 = new Pj(pos, 180.0, 0.36);

    float pjVarX = 0.0;
    float pjVarRange = 0.0;
    float pjVarPend = 0.0;

//--Objetos
    int idCont = 0;     //Contador para asignar IDs a los objetos creados.
    int contPos = 15;   //Contador para mantener la posicion en la Window de los objetos vistos.
    
    typedef vector<Objeto*> circulos;
    circulos vistos;
    circulos objetos;
    circulos toDraw;
    
//--Objetos Estaticos
    Objeto* obj1 = new Objeto(idCont++, Color::Red, 300, 200, 10);
    objetos.push_back(obj1);
    Objeto* obj2 = new Objeto(idCont++, Color::Yellow, 400, 200, 10);
    objetos.push_back(obj2);
    Objeto* obj3 = new Objeto(idCont++, Color::Magenta, 500, 200, 10);
    objetos.push_back(obj3);
    
//--Objeto Movible
    CircleShape circle1;
    circle1.setRadius(10);
    circle1.setPosition(200, 200);
    circle1.setFillColor(Color::Cyan);
    circle1.setOrigin(circle1.getRadius(), circle1.getRadius());

    float objVarX = 0.0;
    float objVarY = 0.0;
  
//--Keyboard Definition
    array<Keyboard::Key,10> kboard = {Keyboard::D, Keyboard::A, Keyboard::Up, Keyboard::Down, 
                            Keyboard::Right, Keyboard::Left, Keyboard::Multiply, Keyboard::Divide,
                            Keyboard::Add, Keyboard::Subtract};

//-----------------------------------------------------------------------------

//--Bucle de Ejecución, con Ventana Abierta    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   

        //--Keyboard Control    
            for(int i = 0; i < kboard.size(); i++){
                if(Keyboard::isKeyPressed(kboard[i])){
                    switch(i){
                    //--Movimiento Personaje (D, Derecha || A, Izquierda)
                        case 0: pjVarX += 3.0;      break;
                        case 1: pjVarX -= 3.0;      break;
                    //--Movimiento Objeto Mov. (↑, Up || ↓, Down || →, Right || ←, Left)
                        case 2: objVarY -= 0.8;     break;
                        case 3: objVarY += 0.8;     break;
                        case 4: objVarX += 0.8;     break;
                        case 5: objVarX -= 0.8;     break;
                    //--Movimiento Objeto Mov. (*, Range plus || /, Range minus || +, Pend plus || -, Pend minus)    
                        case 6: pjVarRange += 3.0;  break;
                        case 7: pjVarRange -= 3.0;  break;
                        case 8: pjVarPend += 0.01;   break;
                        case 9: pjVarPend -= 0.01;   break;               
                    }
                }
            }

        //--Envio del movimiento de cada elemento en el bucle actual a sus Updates correspondientes.
            pj1->update(pjVarX);
            pj1->setXRange(pj1->getXRange() + pjVarRange);
            pj1->setYPend(pj1->getYPend() + pjVarPend);
            circle1.setPosition(circle1.getPosition().x + objVarX, circle1.getPosition().y + objVarY);

        //--Reseteo de los movimientos una vez actualizados.    
            pjVarX = 0.0;
            pjVarRange = 0.0;
            pjVarPend = 0.0;

            objVarX = 0.0;
            objVarY = 0.0;

        //--Window Close Proc Event    
            if (event.type == sf::Event::Closed)
                    window.close();
        }
        
        //Comprobamos si el objeto está en vista. to Function.
        if(!objetos.empty()){
            for(int i = 0; i < objetos.size(); i++){
                if(objetos[i]!=NULL){
                    if(pj1->checkInSigth(objetos[i]->getCirculo()->getPosition())){
                        if(!objetos[i]->getState()){
                            objetos[i]->setState(true);
                            vistos.push_back(objetos[i]);
                            
                        }
                    }else{
                        for(int j = 0; j < vistos.size(); j++){
                            if(vistos[j]!=NULL){
                                if(objetos[i]->getId() == vistos[j]->getId()){
                                    vistos.erase(vistos.begin() + j);
                                    objetos[i]->setState(false);
                                }
                             }
                        }
                    }                    
                }
            }
        }
        
//------Salidas de consola
        
//------Window Management
        window.clear();
    
    //--toDraw Cleaning vector
        toDraw.erase(toDraw.begin(), toDraw.end());
        contPos = 15;

    //--PJ 1 Draws
        window.draw(*pj1->getPersonaje());
        window.draw(*pj1->getAreaVision());
        
    //--Moving Object Draws
        window.draw(circle1);
        window.draw(*obj1->getCirculo());
        window.draw(*obj2->getCirculo());
        window.draw(*obj3->getCirculo());
        
    //--Objects in vision Draws. to Function.
        if(pj1->checkInSigth(circle1.getPosition())){
            toDraw.push_back(new Objeto(-1 , circle1.getFillColor(), contPos, 10, 5));
            contPos += 15; 
        }       
        
        for(int j = 0; j < vistos.size(); j++){
            if(vistos[j]!=NULL)
                toDraw.push_back(new Objeto(vistos[j]->getId() , vistos[j]->getCirculo()->getFillColor(), contPos, 10, 5));
                contPos += 15;   
        }

        for(int i = 0; i < toDraw.size(); i++){
            window.draw(*toDraw[i]->getCirculo());
        }
        
    //--Window Display   
        window.display();
    }
   
    return 0;
}
