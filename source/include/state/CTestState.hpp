#ifndef CTEST_STATE_HPP
#define CTEST_STATE_HPP
#include <irrlicht/irrlicht.h>
#include <engine/CState.hpp>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
class CTestState: public CState
{
public:
    CTestState(IrrlichtDevice *Device);
    void update(f32 delta);
    void onActivate();
    void onDeactivate();
    virtual bool OnEvent(const SEvent &event);
};

#endif
