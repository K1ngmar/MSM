#pragma once

#include <typetraits>

template<typename Event>
concept EventType = std::typetraits::is_class<Event>::value;

/*!
 * @brief A state is required to have the on_entry() and on_exti() function in order to be valid.
*/
template <typename State>
concept StateType requires(State state)
{
    state.on_entry();
    state.on_exit();
};
