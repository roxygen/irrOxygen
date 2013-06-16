#include "engine/CApp.hpp"
#include <state/CTestState.hpp>
CApp::CApp():
    mDriver(0),
    mDevice(0),
    mGui(0),
    mShouldQuit(false),
    mStateManager(0)
{
}
CApp::~CApp()
{
    if(mStateManager)
    {
        delete mStateManager;
    }
    if(mDevice)
    {
        mDevice->closeDevice();
        mDevice->drop();
    }
}
IrrlichtDevice* CApp::getDevice()
{
    return this->mDevice;
}
IVideoDriver*   CApp::getDriver()
{
    return this->mDriver;
}
IGUIEnvironment*CApp::getGui()
{
    return this->mGui;
}
bool CApp::getShouldQuit()
{
    return this->mShouldQuit;
}
void CApp::setShouldQuit(bool shouldQuit)
{
    this->mShouldQuit = shouldQuit;
}
bool CApp::init(SIrrlichtCreationParameters param, const stringw &title, bool resize)
{
    mDevice = createDeviceEx(param);
    if(!mDevice)
        return false;
    mDriver = mDevice->getVideoDriver();
    mGui    = mDevice->getGUIEnvironment();
    mDevice->setWindowCaption(title.c_str());
    mDevice->setResizable(resize);
    mStateManager = new CStateManager(mDevice);
    mStateManager->registerState(game::STATE_GAME, new CTestState(mDevice));
    mStateManager->switchState(game::STATE_GAME);
    mDevice->setEventReceiver(mStateManager);
    return true;
}
void CApp::loop()
{
    while(!mShouldQuit && mDevice->run())
    {
        if(mDevice->isWindowActive())
        {
            mDriver->beginScene(true, true, SColor(255, 101, 101, 140));

            mGui->drawAll();
            mDriver->endScene();
            if(!mStateManager->update())
            {
                mDevice->getLogger()->log("State List is empty");
                mShouldQuit = true;
            }
        }
        else
        {
            mDevice->yield();
        }
    }
}
