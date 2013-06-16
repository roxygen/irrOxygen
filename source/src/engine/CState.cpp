#include "engine/CState.hpp"
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif
CState::CState(IrrlichtDevice *Device):
    mDevice(Device)
{
}

void CState::onActivate()
{}
void CState::onDeactivate()
{}
void CState::update(f32 delta)
{}
void CState::activate()
{
    std::map<stringw, IGUIElement*>::iterator it;
    for(it = mGuiElement.begin(); it != mGuiElement.end(); it++)
    {
        it->second->setVisible(true);
    }
    onActivate();
}
void CState::deactivate()
{
    std::map<stringw, IGUIElement*>::iterator it;
    for(it = mGuiElement.begin(); it != mGuiElement.end(); it++)
    {
        it->second->setVisible(false);
    }
    onDeactivate();
}

bool CState::registerGUIElement(IGUIElement *regGUIElement,
                                const stringw &nameGUIElement)
{
    if(mGuiElement.find(nameGUIElement) != mGuiElement.end())
    {
        mGuiElement[nameGUIElement] = regGUIElement;
        mGuiElement[nameGUIElement]->setVisible(false);
        return true;
    }
    return false;
}
IGUIElement* CState::getElement(const stringw &nameGUIElement)
{
    return mGuiElement[nameGUIElement];
}
bool CState::generateEventSwitchState(game::STATES newState)
{
    SEvent se;
    se.EventType = EET_USER_EVENT;
    se.UserEvent.UserData1 = game::EVENT_SWITCH_STATE;
    se.UserEvent.UserData2 = newState;
    return mDevice->getEventReceiver()->OnEvent(se);
}
bool CState::generateEventSwitchNextState()
{
    SEvent se;
    se.EventType = EET_USER_EVENT;
    se.UserEvent.UserData1 = game::EVENT_SWITCH_NEXT_STATE;
    return mDevice->getEventReceiver()->OnEvent(se);
}
