/*#include "../headerfiles/Mundo.h"
#include "../headerfiles/Fachada.h"
#include "../headerfiles/Protagonista.h"

int main()
{

    //Creo la fachada 
    Fachada* fachada = fachada->getInstance(800,600,false);
    //Protagonista* prota = prota->getInstance();
	// CREAMOS IRRLICHT DEVICE 

	IrrlichtDevice *device = fachada->getDevice();
    sf::RenderWindow* ventana = fachada->getVentana();

	if (!device)
		return 1;
	

	// CREAMOS MUNDO DEL JUEGO 

	Mundo* mundo = new Mundo();

	

	// BUCLE PRINCIPAL DEL JUEGO 

	while(device->run())
	{
		char inputKey;
		bool keyPressed;
		//Evento
		sf::Event* evento = new sf::Event; 
		//Obtener eventos
		while (ventana->pollEvent(*evento))
		{
		    switch (evento-> type)
		    {
		        case sf::Event::Closed:
		       
		            //ventana.close();
		            device->closeDevice();
		        break;

		        case sf::Event::KeyPressed:
		        {    
		            inputKey = evento->key.code;
		            //std::cout<<evento->key.code<<"\n";
		            keyPressed = true;
		           
		        }   
		        break;
		    }
		    
		    
		}
        ventana->clear();
        
		//
		//ventana.draw(rectangle);
		// ACTUALIZAMOS EL MUNDO 
		mundo->update();
		
		//ventana.display();
		

	}

	


	delete fachada;
}

*/


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
	sf::RenderWindow* ventana = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "Ancient Rise", sf::Style::Titlebar | sf::Style::Close);
    /*creo una vista*/
    glewInit();
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

	FObjeto* cajita = new FObjeto();
	cajita->setMalla("resources/cajitaobj.obj");
	objetos.push_back(cajita);
	FObjeto* cajita2 = new FObjeto();
	cajita2->setMalla("resources/mono.obj");
	objetos.push_back(cajita2);
	FObjeto* cajita3 = new FObjeto();
	cajita3->setMalla("resources/cajitaobj.obj");
	objetos.push_back(cajita3);
	//FObjeto* ironMan = new FObjeto();
	//ironMan->setMalla("resources/IronMan.obj");

	cajita2->Mover(vec3(4,0,0));
	cajita3->Mover(vec3(-4,0,0));
	FCamara* camara = new FCamara();
	camara->Activar();
	vec3 camaraOrigin = vec3(0,0,-15);
	camara->Mover(camaraOrigin);
	FColor* color = new FColor(0,0,1.0f, 1.0f);

	/*
	TNodo *Escena = new TNodo();
    TNodo *RotarLuz = new TNodo();
    TNodo *RotarCam = new TNodo();
    TNodo *RotarCoche = new TNodo();
    Escena->addHijoBack(RotarLuz);
    Escena->addHijoBack(RotarCam);
    Escena->addHijoBack(RotarCoche);
    TNodo *TraslaLuz = new TNodo();
    TNodo *TraslaCam = new TNodo();
    TNodo *TraslaCoche = new TNodo();
    RotarLuz->addHijoBack(TraslaLuz);
    RotarCam->addHijoBack(TraslaCam);
    RotarCoche->addHijoBack(TraslaCoche);

    TTransf *TransfRotaLuz = new TTransf();
    TransfRotaLuz->rotar(1.2, 0, 0, 42.0);
	TTransf *TransfRotaCam = new TTransf();
	TransfRotaCam->rotar(1.2, 0, 0, 94.0);
	TTransf *TransfRotaCoche = new TTransf();
	TransfRotaCoche->rotar(1.2, 0, 0, 57.0);

	TTransf *TransfTraslaLuz = new TTransf();
    TransfTraslaLuz->trasladar(20.0, 0, 0);
    TTransf *TransfTraslaCam = new TTransf();
    TransfTraslaCam->trasladar(12.0, 0, 0);
    TTransf *TransfTraslaCoche = new TTransf();
    TransfTraslaCoche->trasladar(52.0, 0, 0);

	RotarLuz->setEntidad(TransfRotaLuz);
	RotarCam->setEntidad(TransfRotaCam);
	RotarCoche->setEntidad(TransfRotaCoche);

	TraslaLuz->setEntidad(TransfTraslaLuz);
	TraslaCam->setEntidad(TransfTraslaCam);
	TraslaCoche->setEntidad(TransfTraslaCoche);


	TLuz *EntLuz = new TLuz();
	TCamara *EntCam = new TCamara();
	TMalla *MallaChasis = new TMalla();

    MallaChasis->cargarMalla("caja");
	
	TNodo *NLuz = new TNodo();
	NLuz->setEntidad(EntLuz);
	TNodo *NCam = new TNodo();
	NCam->setEntidad(EntCam);
	TNodo *NChasis = new TNodo();
	NChasis->setEntidad(MallaChasis);

	TraslaLuz->addHijoBack(NLuz);
    TraslaCam->addHijoBack(NCam);
    TraslaCoche->addHijoBack(NChasis);

    */

	//Fachada* fachada = Fachada::getInstance();

	//fachada->drawEscena();

	while(ventana->isOpen())
	{
		char inputKey;
		bool keyPressed;
		ventana->clear(sf::Color::Black);
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
		            	case 2: 		//C
		            		camara->Mover(vec3(0,0.25f,0));
		            		break;
		            	case 3:			//D
		            		//camara->Mover(vec3(0.25f,0,0));
		            		camara->Rotar(vec3(0,1,0), 0.25f);
		            		//cajita->Mover(vec3(0,0,-0.5f));
		            		break;
		            	case 4:			//Q
		            		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		            		break;
		            	case 16:		//E
		            		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		            		break;
		            	case 18:		//S
		            		camara->Mover(vec3(0,0,-1.0f));
		            		break;
		            	case 22:		//W
		            		camara->Mover(vec3(0,0,1.0f));
		            		break;
		            	case 25:		//Z
		            		camara->Mover(vec3(0,-0.25f,0));
		            		break;
		            	case 57:		//Space
		            		camara->setPosicion(camaraOrigin);
		            		break;
		            }
		          
		            keyPressed = true;
		           
		        }   
		        break;
		    }
		    
		    
		}
        //	ventana.close();
		//

		/*OPENGL PRUEBAS*/

		// 0. copy our vertices array in a buffer for OpenGL to use
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 1. then set the vertex attributes pointers
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(0);  
		// 2. use our shader program when we want to render an object
		//glUseProgram(shaderProgram);
		//ourShader.use();
		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float) screenHeight, 0.1f, 100.f);
		//glm::mat4 view = camera.GetViewMatrix();
		//glm::mat4 projection = glm::mat4(1);
		//glm::mat4 view = glm::mat4(1);
		//ourShader.setMat4("projection", projection);
		//ourShader.setMat4("view", view);
		//// 3. now draw the object 
		//glm::mat4 model = glm::mat4(1);
		////model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		////model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//ourShader.setMat4("model", model);

		//cajita->Rotar(vec3(0,0,1), 0.05f);
		for(int i = 0; i < objetos.size(); i++){
			objetos[i]->Rotar(vec3(0,1,0), 0.05f);
		}
		

		motorgrafico->draw();

		//ourModel->Draw(ourShader);

//		glBindVertexArray(VAO1);
//		glDrawArrays(GL_TRIANGLES,0,3);		//someOpenGLFunctionThatDrawsOurTriangle(); 
//		glBindVertexArray(VAO2);
//		glDrawArrays(GL_TRIANGLES,0,3);
	/* BUCLE PRINCIPAL DEL JUEGO */

		/*OPENGLPRUEBAS*/



		 //ventana->draw(rectangle);
		ventana->display();

		/* ACTUALIZAMOS EL MUNDO */
	//	mundo->update();
		
		//ventana.display();
		
	}


	//delete fachada;
}

