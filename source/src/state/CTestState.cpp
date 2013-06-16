#include <state/CTestState.hpp>
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif
CTestState::CTestState(IrrlichtDevice *Device):
    CState(Device)
{

}
void CTestState::onActivate()
{
    mDevice->getLogger()->log("Activate test state");
    mDevice->getGUIEnvironment()->getFont(L"../data/fonts/Tahoma.xml");

}
void CTestState::onDeactivate()
{
    mDevice->getLogger()->log("Deactivate test state");
}
void CTestState::update(f32 delta)
{
    //...
}
bool CTestState::OnEvent(const SEvent &event)
{
    return false;
}
