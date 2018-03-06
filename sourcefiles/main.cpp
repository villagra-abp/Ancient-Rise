//#include "../headerfiles/Mundo.h"


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

	// define a 120x50 rectangle
	sf::RectangleShape rectangle(sf::Vector2f(20, 20));

	// change the size to 100x100
	//rectangle.setSize(sf::Vector2f(10, 10));
	rectangle.setFillColor(sf::Color(100, 250, 50));

	TGestorRecursos* gestor = TGestorRecursos::getInstance();
	TRecursoMalla* ourModel = dynamic_cast<TRecursoMalla*>(gestor->getRecurso<TRecursoMalla>("caja"));



   	Shader ourShader("motorgrafico/shaders/vertex.vs", "motorgrafico/shaders/fragment1.fs");


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
		            if(inputKey == 16){
		            	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		            }
		            else if(inputKey == 4){
		            	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
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
		ourShader.use();
		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float) screenHeight, 0.1f, 100.f);
		//glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		// 3. now draw the object 
		glm::mat4 model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		ourShader.setMat4("model", model);

		ourModel->Draw(ourShader);

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


}

