#pragma once

#include <typetraits>

/*!
 * @brief An event is just a type, it does not need to do anything else.
*/
template<typename Event>
concept IsEvent = std::typetraits::is_class<Event>::value;

/*!
 * @brief A state is required to have the on_entry() and on_exti() function in order to be valid.
*/
template <class T>
concept IsState requires(T state)
{
    state.on_entry(); // im not sure how to implement this yet.
    state.on_exit(); // im not sure how to implement this yet.
};

class <class T, IsEvent EventType, IsStateMachine StateMachineType>
concept IsGuard requires(T guard, const EventType& evt, StateMachineType& fsm)
{
    (bool)guard(evt, fsm);
};

class <class T, IsEvent EventType>
concept IsAction requires(T action, const EventType& evt)
{
    action(evt);
};
