#include <engine/CStateManager.hpp>

CStateManager::CStateManager(IrrlichtDevice *device)
{
    mDevice = device;
    mMainState = NULL;
    mNextState = game::STATE_NONE;
    mLastTime = 0;
}

CStateManager::~CStateManager()
{
    for(stateMapIt_t it = mStates.getIterator(); !it.atEnd(); it++)
    {
        delete it->getValue();
    }
    mStates.clear();
}

bool CStateManager::OnEvent(const SEvent &event)
{
    if(event.EventType == irr::EET_USER_EVENT)
    {
        switch(event.UserEvent.UserData1)
        {
        case game::EVENT_SWITCH_STATE:
        {
            switchState((game::STATES)event.UserEvent.UserData2);
            return true;
        } break;
        case game::EVENT_SWITCH_NEXT_STATE:
        {
            switchState(mNextState);
            return true;
        } break;
        }
    }
    if(mMainState)
    {
        return mMainState->OnEvent(event);
    }
    return false;
}

void CStateManager::registerState(game::STATES estate, CState *state)
{
    if(mStates.find(estate))
    {
        delete mStates[estate];
        mStates.remove(estate);
    }
    mStates[estate] = state;
}
void CStateManager::switchState(game::STATES estate)
{
    if(mMainState)
    {
        mMainState->deactivate();
    }
    if(estate == game::STATE_NONE)
    {
        mMainState = NULL;
    }
    else
    {
        mMainState = mStates[estate];
        mMainState->activate();
    }
}

void CStateManager::setNextState(game::STATES estate)
{
    mNextState = estate;
}
bool CStateManager::update()
{
    if(!mMainState)
        return false;
    u32 deltaTime = mDevice->getTimer()->getTime() - mLastTime;
    mMainState->update(deltaTime/ 1000.f);
    mLastTime = mDevice->getTimer()->getTime();
    return true;
}
