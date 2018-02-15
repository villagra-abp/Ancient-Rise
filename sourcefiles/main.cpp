//#include "../headerfiles/Mundo.h"


#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


using namespace std;



/*
Estos son los 5 sub namespace del motor de Irrlicht

1º irr::core--> En este podemos encontrar las clases basicas como vectores, planos, arrays, listas y demas
2º irr::gui--> Contiene clases utiles para la facil creacion de una interfaz grafica de usuario
3º irr::io-->  Proporciona interfaces para la entrada/salida. Lectura y escritura de ficheros, acceso a ficheros zip, ficheros xml..
4º irr::scene--> Se encuentra toda la gestion de la escena
5º irr::video--> Contiene clases para acceder al driver del video. Todo el rendererizado 3d o 2d se realiza aqui
*/




int main()
{
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


	/* PRUEBAS OPENGL
	*/

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};	

	unsigned int VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const char* vertexShaderSource = "#version 330 core\n"
							"layout (location =0) in vec3 position; \n"
							"void main(){\n"
							"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
							"}\0";

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	 int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

	const char* fragmentShaderSource = "#version 330 core\n"
							"out vec4 FragColor;\n"
							"void main(){\n"
							"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
							"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);  

	


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
		            if(inputKey == 57){

		            }
		            //std::cout<<evento->key.code<<"\n";
		            keyPressed = true;
		           
		        }   
		        break;
		    }
		    
		    
		}
        //	ventana.close();
		//

		/*OPENGL PRUEBAS*/

		// 0. copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 1. then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);  
		// 2. use our shader program when we want to render an object
		glUseProgram(shaderProgram);
		// 3. now draw the object 
		glBindVertexArray(VBO);
		glDrawArrays(GL_TRIANGLES,0,3);
		//someOpenGLFunctionThatDrawsOurTriangle(); 
	/* BUCLE PRINCIPAL DEL JUEGO */

		/*OPENGLPRUEBAS*/



		 //ventana->draw(rectangle);
		ventana->display();

		/* ACTUALIZAMOS EL MUNDO */
	//	mundo->update();
		
		//ventana.display();
		
	}

	/*
	After we are done with the render loop, we have to delete the Irrlicht
	Device created before with createDevice(). In the Irrlicht Engine, you
	have to delete all objects you created with a method or function which
	starts with 'create'. The object is simply deleted by calling ->drop().
	See the documentation at irr::IReferenceCounted::drop() for more
	information.
	*/

	/**

	Hay que eliminar el objete device que creamos anteriormente antes de terminar con el bucle de render
	En el motor de irrlicht todos los objetos que se han creado mediante una funcion que empieza por
	'create' deben ser eliminados y esto se hace simplemente llamanado a '->drop()'

	**/

	//ventana.close();
}

