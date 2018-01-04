#include "../headerfiles/Huir.h"
#include <ctime>


Status Huir::run(Enemigo *e)
{   
    
	clock_t startTime = clock();

    double  duration = startTime / CLOCKS_PER_SEC;

    //cout<<duration<<endl;

    if(duration<1)
    {

    }

    return BH_SUCCESS;
    
}


void Huir::onInitialize(Blackboard *b)
{
	board = b;
}

Huir::~Huir()
{
    board = nullptr;
}
