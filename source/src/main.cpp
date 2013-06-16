#include <iostream>
#include <irrlicht/irrlicht.h>
#include <engine/CApp.hpp>
#include <engine/CConfig.hpp>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif
int main()
{
    CConfig *cfg = new CConfig(L"../system/config.xml");
    if(!cfg->load())
    {
        std::cerr << "Can't read XML file" << std::endl;
        return 1;
    }

    CApp *app = new CApp();
    if(!app->init(cfg->getParam(), cfg->getConfig(L"title"),
                  cfg->getBool(L"resize")) )
    {
        std::cerr << "Could not init device." << std::endl;
        return 1;
    }
    app->loop();
    delete app;
    return 0;
}

