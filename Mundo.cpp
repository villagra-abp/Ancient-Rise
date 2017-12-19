#include <Mundo.h>
#include <Enemigo.h>
#include <EnemigoSensor.h>
#include <Protagonista.h>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <irrlicht.h>

Mundo::Mundo()
{
    // Matriz de objetos a NULL
   for(uint8_t i = 0; i < kMapSize; ++i) {
      for(uint8_t j = 0; j < kMapSize; ++j) {
         m_objMatrix[i][j] = nullptr;
      }
   }
}


//void CScene::initialize(IVideoDriver* driver, ISceneManager* smgr, IGUIEnvironment* guienv) {
   // Añade los gameobjects creados
   //Protagonista *prota = new Protagonista(device, smgr);
   //addGameObject(prota, prota->getPosition().X);
//}

void Mundo::addGameObject(GameObject* o, core::vector3df position) {
   uint16_t x = position.X ;
   uint16_t y = position.Y ;

   // Comprueba por excepciones
   if (x >= kMapSize || y >= kMapSize) {
      throw std::out_of_range(
         static_cast<std::string>("Out of scene matrix (")
            + std::to_string(x) + "," 
            + std::to_string(y) + ")");
   } else if (m_objMatrix[x][y] != nullptr) {
      throw std::logic_error(
         static_cast<std::string>("Duplicated object at (") 
            + std::to_string(x) + "," 
            + std::to_string(y) + ")");
   }

   // Add a gameObject to the scene
   m_objMatrix[x][y] = o;
   o->setLocation(x, y);
   //m_gameObjects.push_back(o);
}

void CScene::update() {
   // Update gameobjects, Aqui se deberian invocar los updates de todos los gameobjects
   // Beware! Use a normal iteration because 
   // m_gameObjects gets modified when an object is deleted
   size_t s = m_gameObjects.size();
   for (size_t i=0; i < s; i++) {
      CGameObject *g = m_gameObjects[i];
      g->update();
      moveGameObject(g);
      // Check if game object has been removed
      // then go back 1 item (next item its at index i, not i+1)
      if (m_gameObjects.size() != s) {
         s = m_gameObjects.size();
         --i;
      }
   }
}

Mundo::~Mundo()
{
    // Borra todos los Game Objects
   for(CGameObject* g : m_gameObjects) {
      delete g;
   }
   m_gameObjects.clear();
}

void Mundo::moveGameObject(GameObject *g) {
   // Only if object wants to move
   
   uint16_t x  = g->getX();
   uint16_t y  = g->getY();
   uint16_t nx = g->getNextX();
   uint16_t ny = g->getNextY();
      
   if (x != nx || y!= ny) { //Wants to Move
      // Check for collisions
      GameObject *gdest = m_objMatrix[nx][ny];

      if(nx >= 0 && nx < kMapSize && gdest == nullptr){
         // Move because destiny place is empty
         m_objMatrix[x][y]   = nullptr;
         m_objMatrix[nx][ny] = g;        
      } else {
         // Cannot move to a non-empty place
         nx = x; ny = y;
      }
      // Make the movement effective
      g->setLocation(nx, ny);
   }
}

const GameObject* CScene::getGameObject(uint16_t x, uint16_t y) const {
   // Return a Game Object only if it is inside map boundaries
   if (x < kMapSize && y < kMapSize)   
      return m_objMatrix[x][y];

   // Return nullptr for all outside-boundaries coordinates
   return nullptr;
}
