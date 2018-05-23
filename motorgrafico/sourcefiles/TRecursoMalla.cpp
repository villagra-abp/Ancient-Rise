#include "../headerfiles/TRecursoMalla.h"

//Funcion para la gestion de las mallas y sus datos. Original salvo la ultima funcion. Mas detalles en ella.

Shader *TRecursoMalla::boundingShader= nullptr;
TRecursoMalla::TRecursoMalla(){
	if(boundingShader == nullptr) boundingShader = new Shader("motorgrafico/shaders/vertex.vs", "motorgrafico/shaders/bounding.fs");
	max_x = NAN;
	max_y = NAN;
	max_z = NAN;
	min_x = NAN;
	min_y = NAN;
	min_z = NAN;
}

void TRecursoMalla::draw(glm::mat4 mmodelo, TDatosEntidad *datos)
{	
    for(unsigned int i = 0; i < meshes.size(); i++)
        {	
        	meshes[i].draw(mmodelo, datos);
        }
    if(datos->bounding == true)
	    drawBoundingBox(mmodelo, datos);
}  

void TRecursoMalla::addMesh(rMesh mesh){
	meshes.push_back(mesh);
}

void TRecursoMalla::setNombre(string nombre){
	name = nombre;
}

void TRecursoMalla::setDirectorio(string direct){
	directory = direct;
}

string TRecursoMalla::getNombre(){
	return name;
}

string TRecursoMalla::getDirectorio(){
	return directory;
}

//Altamente inspirado en el codigo de https://en.wikibooks.org/wiki/OpenGL_Programming/Bounding_box  con modificaciones para adaptarlo al proyecto

void TRecursoMalla::drawBoundingBox(glm::mat4 mmodelo, TDatosEntidad *datos){
	  // Cube 1x1x1, centered on origin

	boundingShader->use();

	glLineWidth(2);

  GLfloat vertices[] = {
    -0.5, -0.5, -0.5, 1.0,
     0.5, -0.5, -0.5, 1.0,
     0.5,  0.5, -0.5, 1.0,
    -0.5,  0.5, -0.5, 1.0,
    -0.5, -0.5,  0.5, 1.0,
     0.5, -0.5,  0.5, 1.0,
     0.5,  0.5,  0.5, 1.0,
    -0.5,  0.5,  0.5, 1.0,
  };
  GLuint vbo_vertices;
  glGenBuffers(1, &vbo_vertices);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLushort elements[] = {
    0, 1, 2, 3,
    4, 5, 6, 7,
    0, 4, 1, 5, 2, 6, 3, 7
  };
  GLuint ibo_elements;
  glGenBuffers(1, &ibo_elements);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  GLfloat
    gmin_x, gmax_x,
    gmin_y, gmax_y,
    gmin_z, gmax_z;

    gmin_x = min_x;
    gmin_y = min_y;
    gmin_z = min_z;

    gmax_x = max_x;
    gmax_y = max_y;
    gmax_z = max_z;

 //   cout<<max_x<<" "<<min_x<<" "<<max_y<<" "<<min_y<<" "<<max_z<<" "<<min_z<<endl;
  
  glm::vec3 size = glm::vec3(gmax_x-gmin_x, gmax_y-gmin_y, gmax_z-gmin_z);
  glm::vec3 center = glm::vec3((gmin_x+gmax_x)/2, (gmin_y+gmax_y)/2, (gmin_z+gmax_z)/2);
  glm::mat4 transform = glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);

  /* Apply object's transformation matrix */
  glm::mat4 m = mmodelo * transform;
 // unsigned int ID;
 // glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(m));
  boundingShader->setMat4("model", m);
  boundingShader->setMat4("projection", datos->projection);
  boundingShader->setMat4("view", datos->view);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
  int attribute_v_coord = 0;
  glEnableVertexAttribArray(attribute_v_coord);
  glVertexAttribPointer(
    attribute_v_coord,  // attribute
    4,                  // number of elements per vertex, here (x,y,z,w)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
  glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
  glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4*sizeof(GLushort)));
  glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8*sizeof(GLushort)));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisableVertexAttribArray(attribute_v_coord);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDeleteBuffers(1, &vbo_vertices);
  glDeleteBuffers(1, &ibo_elements);
}
