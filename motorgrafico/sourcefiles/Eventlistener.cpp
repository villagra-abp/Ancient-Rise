#include "../headerfiles/Eventlistener.h"


Eventlistener::Eventlistener(){
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

bool Eventlistener::IsKeyDown(EKEY_CODE keyCode) const{
		return KeyIsDown[keyCode];
	}

//Llama al key correspondiente a su letra, número o tecla especial (0-> Espacio, 1-> Ctrl, 2-> Shift, 3-> Escape, 4-> Enter)	
bool Eventlistener::IsKeyDown(char keyCode){
	bool flag = false;
	switch(keyCode){


		case 'q':
			flag = this->IsKeyDown(irr::KEY_KEY_Q);
			break;
		case 'w':
			flag = this->IsKeyDown(irr::KEY_KEY_W);
			break;
		case 'e':
			flag = this->IsKeyDown(irr::KEY_KEY_E);
			break;
		case 'r':
			flag = this->IsKeyDown(irr::KEY_KEY_R);
			break;
		case 't':
			flag = this->IsKeyDown(irr::KEY_KEY_T);
			break;
		case 'y':
			flag = this->IsKeyDown(irr::KEY_KEY_Y);
			break;
		case 'u':
			flag = this->IsKeyDown(irr::KEY_KEY_U);
			break;
		case 'i':
			flag = this->IsKeyDown(irr::KEY_KEY_I);
			break;
		case 'o':
			flag = this->IsKeyDown(irr::KEY_KEY_O);
			break;
		case 'p':
			flag = this->IsKeyDown(irr::KEY_KEY_P);
			break;
		case 'a':
			flag = this->IsKeyDown(irr::KEY_KEY_A);
			break;
		case 's':
			flag = this->IsKeyDown(irr::KEY_KEY_S);
			break;
		case 'd':
			flag = this->IsKeyDown(irr::KEY_KEY_D);
			break;
		case 'f':
			flag = this->IsKeyDown(irr::KEY_KEY_F);
			break;
		case 'g':
			flag = this->IsKeyDown(irr::KEY_KEY_G);
			break;
		case 'h':
			flag = this->IsKeyDown(irr::KEY_KEY_H);
			break;
		case 'j':
			flag = this->IsKeyDown(irr::KEY_KEY_J);
			break;
		case 'k':
			flag = this->IsKeyDown(irr::KEY_KEY_K);
			break;
		case 'l':
			flag = this->IsKeyDown(irr::KEY_KEY_L);
			break;
/*		case 'ñ':
			flag = this->IsKeyDown(irr::KEY_KEY_Ñ);
			break;*/
		case 'z':
			flag = this->IsKeyDown(irr::KEY_KEY_Z);
			break;
		case 'x':
			flag = this->IsKeyDown(irr::KEY_KEY_X);
			break;
		case 'c':
			flag = this->IsKeyDown(irr::KEY_KEY_C);
			break;
		case 'v':
			flag = this->IsKeyDown(irr::KEY_KEY_V);
			break;
		case 'b':
			flag = this->IsKeyDown(irr::KEY_KEY_B);
			break;
		case 'n':
			flag = this->IsKeyDown(irr::KEY_KEY_N);
			break;
		case 'm':
			flag = this->IsKeyDown(irr::KEY_KEY_M);
			break;
		case '1':
			flag = this->IsKeyDown(irr::KEY_NUMPAD1);
			break;
		case '2':
			flag = this->IsKeyDown(irr::KEY_NUMPAD2);
			break;
		case '3':
			flag = this->IsKeyDown(irr::KEY_NUMPAD3);
			break;
		case '4':
			flag = this->IsKeyDown(irr::KEY_NUMPAD4);
			break;
		case '5':
			flag = this->IsKeyDown(irr::KEY_NUMPAD5);
			break;
		case '6':
			flag = this->IsKeyDown(irr::KEY_NUMPAD6);
			break;
		case '7':
			flag = this->IsKeyDown(irr::KEY_NUMPAD7);
			break;
		case '8':
			flag = this->IsKeyDown(irr::KEY_NUMPAD8);
			break;
		case '9':
			flag = this->IsKeyDown(irr::KEY_NUMPAD9);
			break;
		case '0':
			flag = this->IsKeyDown(irr::KEY_NUMPAD0);
			break;
		case 0: //Space
			flag = this->IsKeyDown(irr::KEY_SPACE);
			break;
		case 1: //Ctrl
			flag = this->IsKeyDown(irr::KEY_CONTROL);
			break;
		case 2:	//Shift
			flag = this->IsKeyDown(irr::KEY_SHIFT);
			break;
		case 3://Esc
			flag = this->IsKeyDown(irr::KEY_ESCAPE);
			break;
		case 4://Enter
			flag = this->IsKeyDown(irr::KEY_RETURN);
			break;
		default:
			flag = false;
			break;

		return flag;
	}
}

bool Eventlistener::OnEvent(const SEvent& event){
		// Remember whether each key is down or up
		if (event.EventType == EET_KEY_INPUT_EVENT)
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
		
		return false;
	}