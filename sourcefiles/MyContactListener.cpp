#include "../headerfiles/MyContactListener.h"




void MyContactListener::BeginContact(b2Contact* contact)
{
    //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      Protagonista * body1= static_cast<Protagonista*>( bodyUserData );
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      Enemigo*body2=static_cast<Enemigo*>( bodyUserData );
      if ( body1 && body2)
      {
	std::cout << "colisiona" << std::endl;
        body1->comprobarColision(body2);
      }
        
}
void MyContactListener::EndContact(b2Contact* contact)
{
    
}
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    
}
void MyContactListener::PostSolve(b2Contact* contact,const b2ContactImpulse* impulse)
{
    
}
