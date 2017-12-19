#include <Sensor.h>
#include <GameObject.h>
#include <IMundo.h>

const GameObject* Sensor::see(const GameObject* g, Sensor::Dir d) const {
   // Cogemos la posición del personaje que mira.
   uint8_t x = g->getPosition.X;
   uint8_t y = g->getPosition.Y;

   // Dirección hacia la que mira el personaje.
   int8_t dx = getDespX(d); //Se obtiene?
   int8_t dy = getDespY(d); //Esta no hara falta

   //Tamaño del rango de visión del personaje.
   uint8_t r = g->getVisionSize(); //Rango de visión del personaje

   // Busca el primer elemento que se encuentra dentro del rango de vision.
   return findFirstGameObject(r, x, y, dx, dy);
}

int8_t Sensor::getDespY(Sensor::Dir d) const { // No sera necesario
   switch(d) {
      case DUP:     return  1;  //Mira Arriba
      case DDOWN:   return -1;  //Mira Abajo 
      default:      return  0;     
   }
}

int8_t Sensor::getDespX(Sensor::Dir d) const {
   switch(d) {
      case DLEFT:   return -1;  //Mira Izquierda    
      case DRIGHT:  return  1;  //Mira Derecha       
      default:      return  0;     
   }
}

const GameObject* Sensor::findFirstGameObject(uint8_t range, uint8_t x, uint8_t y, int8_t dx, int8_t dy) const {
   // Recorre el campo de vision hasta que encontramos un objeto (!= nullptr) 
   // o se acaba el rango de vision
   uint8_t map_size = m_env->getSize();
   const GameObject* seen = nullptr;
   do {
      //Debera ser ampliado para unir ambas direcciones en una
      //como un cono de vision orientado a inquierda o derecha
      //para poder detectar enemigos agachados o en plataformas 
      //inferiores
      x += dx;
      y += dy;

      seen = mundo->getGameObject(x, y);
   } while(!seen && x < size && y < size && x < range && y < range);

   // Return object seen
   return seen;
}