#include "../headerfiles/Canal.h"

Canal::Canal(FMOD::Channel* channel){
	canal = channel;
}

Canal::~Canal(){

}

FMOD::Channel* Canal::getCanal(){
	return canal;
}

void Canal::setCanal(FMOD::Channel* channel){
	canal = channel;
}