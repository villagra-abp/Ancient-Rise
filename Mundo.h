#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include <GameObject.h>
#include <IMundo.h>

class Mundo : public GameObject, public IMundo 
{
    public:
        typedef std::vector<CGameObject*> TObjVec;

        Mundo();
        ~Mundo();
		
		virtual void  update()  override;
		
		uint8_t            getSize() const override { return kMapSize; }
		const CGameObject* getGameObject(uint8_t x, uint8_t y) const override;
		
		void addGameObject   (GameObject* o, core::vector3df position);
		void moveGameObject  (GameObject *g);
		
		bool isPlayer()       const override { return false; }
		
		//void initialize(IVideoDriver* driver, ISceneManager* smgr, IGUIEnvironment* guienv);
		//void removeGameObject(GameObject* o);
		
		//bool thereIsAPlayer() const { return m_thereIsAPlayer; }
   		//bool isMortal()       const override { return false; }

    protected:

    private:
    	static constexpr uint16_t kMapSize = 100;

   		TObjVec        m_gameObjects;
   		CGameObject*   m_objMatrix[kMapSize][kMapSize];
   		//bool           m_thereIsAPlayer;
};

#endif // MUNDO_H
