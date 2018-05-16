#include "../headerfiles/Fachada.h"
#include "../headerfiles/NodoGrafo.h"

static Fachada* instance = NULL;



//Con esto hacemos que sea singleton. Solo se puede crear el motorgrafico llamando a getInstance. Esta devuelve el motor si ya estaba creado, y sino lo crea
//Parametros: h-> Alto de la ventana, w-> Ancho de la ventana, fullscreen-> si será pantalla completa o no
Fachada* Fachada::getInstance(int h, int w, bool fullscreen) 
{
    if (instance == NULL) instance = new Fachada(h, w, fullscreen);
    return (instance);
}

Fachada* Fachada::getInstance() {
    
    return (instance);
}

glm::f32 Fachada::getTime()
{
	sf::Time elapsed1 = reloj.getElapsedTime();
    //std::cout << elapsed1.asSeconds() << std::endl;
    reloj.restart();
    return elapsed1.asSeconds();
}

//Destructor
Fachada::~Fachada(){
	//device->drop();
}

//Constructor. Solo accesible desde getInstance
Fachada::Fachada(int h, int w, bool fullscreen){
	
	sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4.3;
    settings.minorVersion = 3.3;
    
    std::cout << "depth bits:" << settings.depthBits << std::endl;
std::cout << "stencil bits:" << settings.stencilBits << std::endl;
std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;
    /** SUBTITULO DE VENTANA
 Para poner texto en el subtitulo de la ventana. Necesita de una 'L' delante del string
 debido a que lo necesita el motor de irrlicht
**/
    
    ventana= new sf::RenderWindow(sf::VideoMode(h, w), "Ancient Rise", sf::Style::Titlebar | sf::Style::Close, settings);
    ventana->setFramerateLimit(60);
    /*creo una vista*/
	/*creo una vista*/
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//  glCullFace(GL_FRONT);  
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.1f, 100.0f);
    ventana->setFramerateLimit(60);
	sf::View view(sf::FloatRect(0, 0, 1000, 600));
	
	view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	ventana->setView(view);
	ventana->setActive(true);

    bounding = false;
    /*
    SIrrlichtCreationParameters Parameters;
    Parameters.DriverType = video::EDT_OPENGL; 
    //Parameters.EventReceiver = &receiver;
    Parameters.WindowId = reinterpret_cast<void*>(ventana->getSystemHandle());
    device = createDeviceEx(Parameters);
    driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
    */
    //SIrrlichtCreationParameters Parameters;
    //device = createDeviceEx(Parameters);
	
}
sf::RenderWindow* Fachada::getVentana(){
  return ventana;

}

//Modifica la visibilidad del cursor
void Fachada::cursorVisible(bool f){
	//device->getCursorControl()->setVisible(f);

}

//Personaliza el sprite del cursor
void Fachada::cursorPersonalizar(std::string path){

}

//Dibuja todo lo dibujable
void Fachada::draw(){
    if(bounding)
	   motorgrafico->drawBounding();
    else
        motorgrafico->draw();
}

void Fachada::suspension(){
	//device->yield();
}

void Fachada::cerrar(){
	ventana->close();
}

void Fachada::destruirObjeto(void* nodo)
{
    FObjeto* node=(FObjeto*)nodo;

    delete node;
}


bool Fachada::getVentanaEstado(){
	return ventana->isOpen();
}



bool Fachada::getVentanaActiva(){
	//return device->isWindowActive();
}

int Fachada::getFPS(){
	return 60;
}

void Fachada::setNombreVentana(std::string text){
	wstring wide_string = wstring(text.begin(), text.end());
	const wchar_t* result = wide_string.c_str();

	//device->setWindowCaption(result);
}

void Fachada::setNombreVentana(wchar_t* text){
	//device->setWindowCaption(text);
}

void Fachada::setBounding(bool flag){
    bounding = flag;
}
FObjeto* Fachada::addCube(int x,int y,int z,bool flag){
    /*
    scene::ISceneNode * rec=smgr->addCubeSceneNode();
    
    if (rec)
    {
        
        rec->setPosition(core::vector3df(x,y,z));
        //rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
        rec->setMaterialFlag(video::EMF_LIGHTING, flag);
    }
    */
    FObjeto* enem = new FObjeto();
	
    enem->setMalla("resources/pared.obj");
    enem->Escalar(vec3(2,2,2));
	

	enem->setPosicion(vec3(x,y,z));
	enem->Rotar(vec3(0,1,1), 5.f);
    
    return enem;
}
FObjeto* Fachada::addSphere(int x,int y,int z,bool flag){
    //scene::ISceneNode * rec=smgr->addSphereSceneNode();
    /*if (rec) 
    {
        
        rec->setPosition(core::vector3df(x,y,z));
        //rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
        rec->setMaterialFlag(video::EMF_LIGHTING, flag);
    }
    */
    
    FObjeto* prota = new FObjeto();
	
    prota->setAnimacion("resources/esfera.obj");
    prota->Escalar(vec3(2,2,2));
	

	prota->setPosicion(vec3(x,y,z));
	//prota->Rotar(vec3(0,1,0), -4.5f);
    
    return prota;
}
FObjeto* Fachada::addMalla(float x,float y,float z,string ruta){
    
    FObjeto* malla = new FObjeto();
//    FBillboard* malla = new FBillboard();
	
    malla->setMalla(ruta);
    malla->Escalar(vec3(2,2,2));
	

	malla->setPosicion(vec3(x,y,z));
	//malla->Rotar(vec3(0,1,0), -4.5f);
    
    return malla;
}

FBillboard* Fachada::addBillboard(float x,float y,float z,string ruta){
     FBillboard* malla = new FBillboard();
    
    malla->setMalla(ruta);
    malla->Escalar(vec3(2,2,2));
    

    malla->setPosicion(vec3(x,y,z));

    return malla;
}

FObjeto* Fachada::addAnimacion(int x, int y, int z, string path){

    FObjeto* objeto = new FObjeto();
    
    objeto->setAnimacion(path);
    objeto->Escalar(vec3(2,2,2));
    
    objeto->setPosicion(vec3(x,y,z));
    
    return objeto;
}

void Fachada::rotObj(void* nodo, float x, float y, float z, float angulo){
    FObjeto* o=(FObjeto*)nodo;
    o->Rotar(vec3(x,y,z), angulo);
}

void Fachada::movObj(void* nodo, float x, float y, float z){
    FObjeto* o=(FObjeto*)nodo;
    o->Mover(vec3(x,y,z));
}

Posicion* Fachada::getPosicion(void * nodo){

    FObjeto* node=(FObjeto*)nodo;
    vec3 pos=node->getPosicion();
    Posicion* posicion= new Posicion(pos.x,pos.y,pos.z);
    //std::cout<<posicion->getPosX()<<endl;
    return posicion;
}

bool Fachada::setScala(void * nodo,Posicion* scala){
    
    FObjeto * node=(FObjeto*)nodo;
    node->Escalar(vec3(scala->getPosX(),scala->getPosY(),scala->getPosZ()));
    return true;
    
}
bool Fachada::setPosicion(void * nodo,Posicion* pos){
    FObjeto* node=(FObjeto*)nodo;
    vec3 position=vec3(pos->getPosX(),pos->getPosY(),0);
    
    node->setPosicion(position);
    return true;
}
bool Fachada::setMaterialFlag(void * nodo,bool b){
    //scene::ISceneNode * node=(scene::ISceneNode*)nodo;
    //node->setMaterialFlag(video::EMF_LIGHTING, b);
    return true;
}
bool Fachada::setMaterial(void * nodo,std::string ruta){
    //scene::ISceneNode * node=(scene::ISceneNode*)nodo;
    //node->setMaterialTexture(0,driver->getTexture(ruta));
    return true;
}
/* Funcion para dibujar los diferentes mapas del juego en funcion del nivel en el que estemos */
FObjeto* Fachada::drawTerreno(int nivel){
    
	FObjeto* suelo = new FObjeto();

    switch(nivel){

        case 1: 
        {    
           suelo->setMalla("resources/Niveles/nivel2.obj");
           suelo->Escalar(vec3(0.8,0.8,2.5));
           suelo->Mover(vec3(-103,-7,-35));
           
           break;
        }

        case 2:
        {
           suelo->setMalla("resources/Niveles/nivel3.obj");
           suelo->Escalar(vec3(0.733,0.755,1.5));
           suelo->Mover(vec3(-107,0,-40));
           break;
        }
    }
	
    //suelo = addCube(-220,-9,0, false);
    
	
	
	//suelo->Rotar(vec3(0,1,0), -3.f);
    suelo->Rotar(vec3(1,0,0), 1.57f);
	
    return suelo;
    
}
void Fachada::addMenu(int tipo){
    
    FObjeto* menu = new FObjeto();
    addFlecha(1);
    if(tipo==1){
        ///Añado el menu
        menu->setMalla("resources/menu.obj");
        menu->setPosicion(vec3(.5f,-.5f,.5f));
        menu->Escalar(vec3(.1f,.1f,.1f));
        menu->Rotar(vec3(1,0,0), 1.5f);
        
    }else{
        ///Añado el menu
        menu->setMalla("resources/menu.obj");
        menu->setPosicion(vec3(.5f,-.5f,.5f));
        menu->Escalar(vec3(.1f,.1f,.1f));
        menu->Rotar(vec3(1,0,0), 1.5f);
        
    }
}
void Fachada::addFlecha(int pos){
    
    FObjeto* flecha = new FObjeto();
    flecha->setMalla("resources/porraelite.3DS");
    flecha->setPosicion(vec3(-4.f,pos*3,.5f));
    flecha->Escalar(vec3(.01f,.01f,.01f));
    
}
FCamara* Fachada::addCamara(Posicion* p){
 
    //cam = smgr->addCameraSceneNode(0, core::vector3df(p->getPosX(),50,-140), core::vector3df(0,5,0));
	//device->getCursorControl()->setVisible(true);
    
    FCamara* camara = new FCamara();
	camara->Activar();
	vec3 camaraOrigin = vec3(-160,-20,-130);
	//cajita->Unir(cajita2);
	//cajita->Mover(vec3(0,0,4));
	camara->Mover(camaraOrigin);
	//camara->Rotar(vec3(0,1,0), 3.0f);
    
    return camara;
    
}
FLuz* Fachada::addLuz(Posicion* p){
 
    FColor* color = new FColor(1.0f,		1.0f,	1.0f, 1.0f);
	glm::vec4 vColor;

	FLuz* luz = new FLuz(color);
	vec3 luzOrigin = vec3(-160,0,80);
	luz->Mover(luzOrigin);
    
    return luz;
}

FLuz* Fachada::addLuzDireccional(Posicion* p){
    FColor* color = new FColor(1.0f,        1.0f,   1.0f, 1.0f);

    vec3 dir(p->getPosX(), p->getPosY(), p->getPosZ());

    FLuz* luz = new FLuz(color, dir);
    
    return luz;
}


FLuz* Fachada::addLuzDirigida(Posicion* p, Posicion* d){
    FColor* color = new FColor(1.0f,        0.0f,   0.0f, 1.0f);

    vec3 pos(p->getPosX(), p->getPosY(), p->getPosZ());
    vec3 dir(d->getPosX(), d->getPosY(), d->getPosZ());

    FLuz* luz = new FLuz(color, dir, 20.0f, 25.0f);
    vec3 luzOrigin = vec3(-160,0,80);
    luz->Mover(pos);
    
    return luz;
}


FSkybox* Fachada::addSkybox(vector<string> paths){
    FSkybox* skybox = new FSkybox();

    skybox->setSkybox(paths);

    return skybox;
}

/**
FUNCION PARA crear el objeto estatico
**/
void Fachada::CreateGround(b2World& world, float X, float Y,float largo,float alto)
{
    Y=-Y+50;
   
    X=X-191;
    float posX=X+(largo/2);
    float posY=Y+(alto/2);
    /*
    std::cout<<"posX vale: "<<posX <<endl;
    std::cout<<"posY vale: "<<posY <<endl;
    std::cout<<"largo vale: "<<largo <<endl;
    std::cout<<"alto vale: "<<alto <<endl;
    */
    b2BodyDef BodyDef;
    BodyDef.position.Set(posX, posY);
    BodyDef.type = b2_staticBody;
    b2Body* Ground = world.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox(largo/2, alto/2);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.friction = 0.4f;
    FixtureDef.shape = &Shape;
    Ground->CreateFixture(&FixtureDef);

    bodies.push_back(Ground);   // Metemos todos los bodies en un vector para poder borrarlos despues
    //cout<<bodies.size()<<endl;
}

void Fachada::destruirBodies()
{
    for(size_t i=0; i<bodies.size();i++)
    {
        if(bodies[i]!=nullptr)
        {
            bodies[i]->GetWorld()->DestroyBody(bodies[i]);
        }
    }
    bodies.clear();
}
