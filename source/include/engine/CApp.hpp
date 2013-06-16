#ifndef CAPP_HPP
#define CAPP_HPP
#include <irrlicht/irrlicht.h>
#include <engine/CStateManager.hpp>
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CApp
{
public:
    CApp();
    ~CApp();
    bool            init(SIrrlichtCreationParameters param,
                         const stringw &title, bool resize);
    IrrlichtDevice  *getDevice();
    IVideoDriver    *getDriver();
    IGUIEnvironment *getGui();
    bool            getShouldQuit();
    void            setShouldQuit(bool shouldQuit);
    void            loop();
private:
    CStateManager   *mStateManager;
    IrrlichtDevice  *mDevice;
    IVideoDriver    *mDriver;
    IGUIEnvironment *mGui;
    bool mShouldQuit;
};
#endif // CAPP_HPP
