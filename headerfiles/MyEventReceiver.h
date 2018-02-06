#include "../headerfiles/Protagonista.h"





class MyEventReceiver : public IEventReceiver
{
public:

   
    MyEventReceiver();
    virtual bool OnEvent(const SEvent& event);
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;
    void checkInput(Protagonista *prota,const f32 Time);
    void checkSigilo(Protagonista *prota);
    void checkCombate(Protagonista *prota);
    void saltar(Protagonista *p, bool salta);
    void moverse(Protagonista *p,const f32 Time);
    void atacar(Protagonista *p,bool b);
    void ralentizar(Protagonista *p);
    void sprintar(Protagonista *p);
    void direccion(Protagonista *p,int n);
    void setMando(bool b);
    //devuelve el estado del mando
    const SEvent::SJoystickEvent & GetJoystickState() const
    {
        return JoystickState;
    }

private:

    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    bool keyIsPressed[KEY_KEY_CODES_COUNT];
    SEvent::SJoystickEvent JoystickState;
    bool mando=false;


};
