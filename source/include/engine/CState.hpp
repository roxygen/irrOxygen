#ifndef CSTATE_HPP
#define CSTATE_HPP
#include <irrlicht/irrlicht.h>
#include <engine/cons.hpp>
#include <map>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
class CState: public IEventReceiver
{
public:
    CState(IrrlichtDevice *Device);
    virtual void update(irr::f32 delta);
    virtual void activate();
    virtual void deactivate();
    virtual void onActivate();
    virtual void onDeactivate();
    virtual bool registerGUIElement(IGUIElement* regGUIElement,
                                    const stringw &nameGUIElement);
    virtual IGUIElement* getElement(const stringw &nameGUIElement);
    virtual bool generateEventSwitchState(game::STATES newState);
    virtual bool generateEventSwitchNextState();
protected:
    IrrlichtDevice *mDevice;
    std::map<stringw, IGUIElement*> mGuiElement;
};

#endif
