
#pragma once

#include <tuple>

/*!
 * @brief Interface for a state machine.
 * When you intheirit this class make sure you:
 * - Define an enum called `State` which contains all states
 * -
*/
template <class Derived>
class FSM
{
private:

    /*!
     * <originState, event, eventEntryFunction, transitionFunction, guard>
    */
    template<class Event>
    using TransitionTableRow_t = std::tuple<Derived::State, Event, 
    
    Derived::State currentState; /*!< -. */

    FSM();

    template<class Event>
    void ProcessEvent(const Event);

    friend class Derived;


};
