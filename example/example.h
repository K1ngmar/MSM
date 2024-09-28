
#pragma once

#include "FSM/FSM.h"

class SomeManagerClass : public StateMachine<SomeManagerClass>
{
    enum class State
    {
        Starting,
        Loading,
        Calculating,
        ShuttingDown
    };


};
