#ifndef ENGINE_CONS_H
#define ENGINE_CONS_H
namespace game
{
    enum EVENTS
    {
        EVENT_SWITCH_STATE = 1,
        EVENT_SWITCH_NEXT_STATE
    };

    enum STATES
    {
        STATE_NONE = 200,
        STATE_LOADER,
        STATE_MAIN_MENU,
        STATE_GAME_MENU,
        STATE_GAME,
        STATE_OPTIONS
    };

}//namespace cons
#endif
