#include "../headerfiles/Fachada.h"


#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../motorgrafico/fachada/headerfiles/Fachada.h"



using namespace std;

#include "../motorgrafico/headerfiles/Shader.h"
#include "../headerfiles/Camera.h"
#include "../motorgrafico/headerfiles/TGestorRecursos.h"





int main()
{	

	//const char* ironMan = "resources/cajitaobj.obj";
	//const char* ironMan = "resources/IronMan.obj";
	int screenWidth = 800;
	int screenHeight = 600;

	sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4.6;
    settings.minorVersion = 3.3;

	sf::RenderWindow* ventana = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "Ancient Rise", sf::Style::Titlebar | sf::Style::Close, settings);
    /*creo una vista*/
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.1f, 100.0f);
    ventana->setFramerateLimit(60);
	sf::View view(sf::FloatRect(0, 0, 1000, 600));
	
	view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	ventana->setView(view);
	ventana->setActive(true);
	//Mundo* mundo = new Mundo(ventana);

	/*
	TGestorRecursos* gestor = TGestorRecursos::getInstance();
	TRecursoMalla* ourModel = dynamic_cast<TRecursoMalla*>(gestor->getRecurso<TRecursoMalla>("caja"));


   	Shader ourShader("motorgrafico/shaders/vertex.vs", "motorgrafico/shaders/fragment1.fs");

	*/
	TMotorTAG* motorgrafico = TMotorTAG::getInstance();

	vector<FObjeto*> objetos;
	
	FObjeto* cajita2 = new FObjeto();
	cajita2->setMalla("resources/cajaColor.obj");
	//cajita2->setMaterial("mat_rosa");
	//cajita2->Escalar(vec3(0.1f, 0.1f, 0.1f));
	objetos.push_back(cajita2);

	FObjeto* esfera = new FObjeto();
	esfera->setMalla("resources/escenario.3DS");
	//esfera->Escalar(vec3(0.1f,0.1f,0.1f));
	//esfera->setMaterial("mat_negro");
	objetos.push_back(esfera);

	FObjeto* esfera2 = new FObjeto();
	esfera2->setMalla("resources/esfera.obj");
	//esfera2->setMaterial("mat_naranja");
	objetos.push_back(esfera2);


	FObjeto* cajita = new FObjeto();
	cajita->setMalla("resources/cajitaobj.obj");
	//cajita->setMaterial("mat_naranja");
	objetos.push_back(cajita);
	
	FObjeto* suelo = new FObjeto();
	FObjeto* techo = new FObjeto();
	suelo->setMalla("resources/espejo.obj");
	techo->setMalla("resources/espejo.obj");

	suelo->Mover(vec3(0,-4,0));
	suelo->Escalar(vec3(10,1,10));
	techo->Mover(vec3(0,10,0));
	techo->Escalar(vec3(10,1,10));

	vector<FObjeto*> suelos;

	FObjeto* paredTrasera = new FObjeto();
	FObjeto* paredDerecha = new FObjeto();
	FObjeto* paredIzquierda = new FObjeto();
	

	suelos.push_back(paredTrasera);
	suelos.push_back(paredDerecha);
	suelos.push_back(paredIzquierda);
	

	for(int i = 0; i < suelos.size(); i++){
		suelos[i]->setMalla("resources/pared.obj");
		suelos[i]->Escalar(vec3(11,11,11));
	}

	paredTrasera->Mover(vec3(0,0,10));
	paredTrasera->Rotar(vec3(0,1,0), 1.6f);
	paredIzquierda->Mover(vec3(-10,0,0));
	paredDerecha->Mover(vec3(10,0,0));

	//paredDerecha->Rotar(vec3(0,0,1), 1.0f);

	//FObjeto* ironMan = new FObjeto();
	//ironMan->setMalla("resources/IronMan.obj");
	cajita->Mover(vec3(0,0,0));
	esfera2->Mover(vec3(0,5,0));
	cajita2->Mover(vec3(4,0,0));
	esfera->Mover(vec3(-4,0,0));
	FCamara* camara = new FCamara();
	camara->Activar();
	vec3 camaraOrigin = vec3(0,0,10);
	//cajita->Unir(cajita2);
	cajita->Mover(vec3(0,0,4));
	camara->Mover(camaraOrigin);
	camara->Rotar(vec3(0,1,0), 3.0f);
	
	

	FColor* color = new FColor(1.0f,		1.0f,	1.0f, 1.0f);
	glm::vec4 vColor;

	FLuz* luz = new FLuz(1.0f,color);
	vec3 luzOrigin = vec3(0,0,-10);
	luz->Mover(luzOrigin);
//
//	FObjeto* lampara = new FObjeto();
//	lampara->setMalla("resources/cajitaobj.obj");
//	lampara->setMaterial("mat_rosa");
//	lampara->Unir(luz);
//	//lampara->Escalar(vec3(0.3,0.3,0.3));

	vec3 posicion(0,0,0);

	bool flag = false;
	bool flag2 = false;
	
	while(ventana->isOpen())
	{
		char inputKey;
		bool keyPressed;
		//ventana->clear(sf::Color::Black);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Evento
		sf::Event* evento = new sf::Event; 
		//Obtener eventos
		while (ventana->pollEvent(*evento))
		{
		    switch (evento-> type)
		    {
		        case sf::Event::Closed:
		       
		            ventana->close();
		        break;

		        case sf::Event::KeyPressed:
		        {    
		            inputKey = evento->key.code;
		            //std::cout<<evento->key.code<<std::endl;		
		            switch(inputKey){
		            	case 0: 		//A
		            		//camara->Mover(vec3(-0.25f,0,0));
		            		camara->Rotar(vec3(0,-1,0), 0.25f);
		            		//cajita->Mover(vec3(0,0,0.5f));
		            		break;
		            	case 1:			//B?
		            		posicion = cajita->getPosicion();
							cout<<posicion.x<<" "<<posicion.y<<" "<<posicion.z<<endl;
							break;
		            	case 2: 		//C
		            		luz->Mover(vec3(0,1.0f,0));
		            		break;
		            	case 3:			//D
		            		//camara->Mover(vec3(0.25f,0,0));
		            		camara->Rotar(vec3(0,1,0), 0.25f);
		            		//cajita->Mover(vec3(0,0,-0.5f));
		            		break;
		            	case 4:			//E
		            		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		            		break;
		            	case 5:			//F
		            		//Aumentar azul
		            		color = luz->getColor();
		            		vColor = color->getColor();
		            		vColor += glm::vec4(0,0,0.05f,0);
		            		color->setColor(vColor);
		            		luz->setColor(color);
		            		break;
		            	case 6:			//G
		            		//Disminuir azul
		            		color = luz->getColor();
		            		vColor = color->getColor();
		            		vColor = vColor - glm::vec4(0,0,0.05f,0);
		            		color->setColor(vColor);
		            		luz->setColor(color);
		            		break;
		            	case 7:			//H
		            		//Aumentar rojo
		            		color = luz->getColor();
		            		vColor = color->getColor();
		            		vColor += glm::vec4(0.05f,0,0,0);
		            		color->setColor(vColor);
		            		luz->setColor(color);
		            		break;
		            	case 8: 		//I
		            		//Disminuir rojo
		            		color = luz->getColor();
		            		vColor = color->getColor();
		            		vColor += glm::vec4(-0.05f,0,0,0);
		            		color->setColor(vColor);
		            		luz->setColor(color);
		            		break;
		            	case 9:			//J
		            		//Aumentar verde
		            		color = luz->getColor();
		            		vColor = color->getColor();
		            		vColor += glm::vec4(0,0.05f,0,0);
		            		color->setColor(vColor);
		            		luz->setColor(color);
		            		break;
		            	case 10:		//K
		            		//Disminuir verde
		            		color = luz->getColor();
		            		vColor = color->getColor();
		            		vColor += glm::vec4(0,-0.05f,0,0);
		            		color->setColor(vColor);
		            		luz->setColor(color);
		            		break;
		            	case 11:		//L
		            		if(flag2){
		            			cajita->setMalla("resources/cajitaobj.obj");
		            			cajita->Escalar(vec3(1.0f,1.0f,1.0f));
		            			flag2 = false;
		            		} else {
		            			cajita->setMalla("resources/IronMan.obj");
		            			cajita->Escalar(vec3(0.1f,0.1f,0.1f));
		            			flag2 = true;
		            		}
		            		break;
		            	case 12:		//M
		            		camara->Mover(vec3(0,1,0));
		            		break;
		            	case 13:		//N
		            		camara->Mover(vec3(0,-1,0));
		            		break;
		            	case 16:		//Q
		            		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		            		break;
		            	case 18:		//S
		            		luz->Mover(vec3(0,0,-1.0f));		       
		            		break;

		            	case 19:		//T
		            		luz->setPosicion(luzOrigin);
		            		break;	
		            	case 22:		//W
		            		luz->Mover(vec3(0,0,1.0f));
		            		break;
		            	case 25:		//Z
		            		luz->Mover(vec3(0,-1.0f,0));
		            		break;
		            	case 57:		//Space
		            		if(flag) flag = false;
		            		else flag = true;
		            		break;

		            	case 73: 		//arriba
		            		camara->Mover(vec3(0,0,-1));
		            		break;
		            	case 74: 		//abajoo
		            		camara->Mover(vec3(0,0,1));
		            		break;
		            	case 71: 		//izquierda
		            		camara->Mover(vec3(-1,0,0));
		            		break;
		            	case 72:		//derecha
		            		camara->Mover(vec3(1,0,0));
		            		break;
		            }
		          
		            keyPressed = true;
		           
		        }   
		        break;
		    }
		    
		    
		}
 
	
		for(int i = 0; i < objetos.size(); i++){
			if(flag) objetos[i]->Rotar(vec3(0,1,0), 0.025f);
				//cajita->Rotar(vec3(0,0,1), 0.025f);
				//cajita2->Rotar(vec3(0,0,1), 0.025f);
		}

		motorgrafico->draw();


		ventana->display();

		
	}

	delete motorgrafico;
	//delete fachada;
}

