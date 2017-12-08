/*#include <../headerfiles/Evenlistener.h>


Eventlistener::Eventlistener(){
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

virtual bool Eventlistener::IsKeyDown(EKEY_CODE keyCode) const{
		return KeyIsDown[keyCode];
	}

virtual bool Eventlistener::OnEvent(const SEvent& event){
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        {
           KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
           //keyIsPressed[event.KeyInput.Key] = event.KeyInput.
        }
		/*
		Always return false by default. If you return true you tell the engine
		that you handled this event completely and the Irrlicht should not
		process it any further. So for example if you return true for all
		EET_KEY_INPUT_EVENT events then Irrlicht would not pass on key-events
		to it's GUI system.
		*/
		/*
		return false;
	}*/