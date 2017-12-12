#include <irrlicht/irrlicht.h>

using namespace irr;

class Eventlistener : public IEventReceiver{

public:

	 bool OnEvent(const SEvent& event);

	/*
    Para saber que tecla esta pulsada
    */

	/*virtual*/ bool IsKeyDown(EKEY_CODE keyCode) const;
	 bool IsKeyDown(char c);
	

	Eventlistener();


private:

	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool keyIsPressed[KEY_KEY_CODES_COUNT];

};
