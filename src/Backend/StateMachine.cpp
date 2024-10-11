#include "MSM/FSM.hpp"

StateMachine::StateMachine()
    : currentState(InitialState()) 
{

}

void StateMachine::SetStateActive(const State& incommingState)
{
    currentState = incommingState;
}

const State& StateMachine::CurrentState() const
{
    return currentState;
}
