#include <EnemigoSensor.h>


/**
CONSTRUCTOR DE ENEMIGO BASICO
**/
EnemigoSensor::EnemigoSensor(Sensor* s, IrrlichtDevice *dev, ISceneManager* smgr, Posicion *posiciones[]):Enemigo(dev, smgr, posiciones)
    : m_dir(1), v_sensor(s) 
{

    //ESTADISTICAS ENEMIGO BASICO

    this->setEnergia(100.f);
    this->setHambre(100.f);
    this->setSalud(100.f);
    this->setSed(100.f);
    this->setVelocidad(8.f);

}

/**
PARA COMPROBAR EN QUE COMPORTAMIENTO ESTA EL ENEMIGO
**/
void EnemigoSensor::Update()
{
    const CGameObject* g;

    g = getProtaSeenAtPresentMovementDirection();

    if (v_sensor(this, dir)->isPlayer() ) // APLICACION DE SENSOR!
        this.AvistadoProta();

}


const Protagonista* EnemigoSensor::getProtaSeenAtPresentMovementDirection() const{
    
    Sensor::Dir dir = getSeeDir();
    return m_vsensor->see(this, dir);
}

Sensor::Dir EnemigoSensor::getSeeDir() const {
    if (m_dir > 0)
      return Sensor::DRIGHT;

   return Sensor::DLEFT;
}
/**
FUNCION PARA VER QUE HACE EL ENEMIGO BASICO CUANDO VE AL PROTAGONISTA
**/
void EnemigoSensor::AvistadoProta()
{
    

}


EnemigoSensor::~EnemigoSensor()
{
    //dtor
    if (m_vsensor) {
      delete m_vsensor;
      m_vsensor = nullptr;
   }
}
