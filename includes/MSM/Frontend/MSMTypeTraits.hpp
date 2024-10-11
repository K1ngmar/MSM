#pragma once

#include <typetraits>

/*!
 * @brief An event is just a type, it does not need to do anything else.
*/
template<typename Event>
concept EventType = std::typetraits::is_class<Event>::value;

/*!
 * @brief A state is required to have the on_entry() and on_exti() function in order to be valid.
*/
template <class T>
concept StateType requires(T state, FSM fsm, State ost, Event evt, DestinationState dst, TransitionAction at, Guard tg)
{
    state.on_entry(fsm, ost, evt, dst, ta, tg);
    state.on_exit(fsm, ost, evt, dst, ta, tg);
};
