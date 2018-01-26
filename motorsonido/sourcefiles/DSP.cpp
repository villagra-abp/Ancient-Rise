#include "../headerfiles/DSP.h"

DSP::DSP(FMOD::DSP* ndsp){
	dsp = ndsp;
}
DSP::~DSP(){

}

FMOD::DSP* DSP::getDSP(){
	return dsp;
}