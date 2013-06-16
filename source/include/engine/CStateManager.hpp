#ifndef CSTATE_MANAGER_HPP
#define CSTATE_MANAGER_HPP
#include <irrlicht/irrlicht.h>
#include <engine/CState.hpp>
#include <engine/cons.hpp>
#include <map>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
typedef map<game::STATES, CState*> stateMap_t;
typedef map<game::STATES, CState*>::Iterator stateMapIt_t;
class CStateManager
        : public IEventReceiver
{
public:
    CStateManager(IrrlichtDevice* device);
    ~CStateManager();
    virtual bool OnEvent(const SEvent &event);
    void registerState(game::STATES estate, CState * state);
    void switchState(game::STATES estate);
    void setNextState(game::STATES estate);
    bool update();
protected:
    stateMap_t mStates;
    CState* mMainState;
    game::STATES mNextState;
private:
    IrrlichtDevice* mDevice;
    u32 mLastTime;
};

#endif
