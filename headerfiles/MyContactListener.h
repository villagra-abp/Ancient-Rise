#include <Box2D/Box2D.h>
#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Enemigo.h"
class MyContactListener : public b2ContactListener
  {
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
  };

