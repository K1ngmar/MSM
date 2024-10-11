#pragma once

#include "Frontend/State.hpp"
#include "Frontend/State.hpp"
#include "Frontend/DestinationState.hpp"
#include "Frontend/TransitionAction.hpp"
#include "Frontend/TransitionGuard.hpp"

/*!
 * @brief Transition Table Row defines how to perform a State transtion based on an incomming event.
 * @tparam OriginState
 * @tparam IncommingEvent
 * @tparam DestinationState
 * @tparam TransitionAction Action performed in between the transtions of states.
 * @tparam TransitionGuard Transition is only executed if the guard is satisfied.
*/
template<State OriginState, Event IncommingEvent, State DestinationState, Action TransitionAction, Guard TransitionGuard>
class TTRow
{
    std::shared_ptr<FSM> fsm; /*!< The state machine. */

    OriginState ost; /*!< -. */
    DestinationState dst; /*!< -. */
    TransitionAction ta; /*!< -. */
    TransitionGuard tg; /*!< -. */

public:

    /*!
     * @brief -.
    */
    TTRow(std::shared_ptr<FSM> fsm_) : fsm(fsm_)

    {

    }

    /*!
     * @brief -.
    */
    bool CanPerformTransition() const
    {
        return transitionGuard();
    }

    /*!
     * @brief Calling this will perform the state transition.
    */
    void ProcessEvent(const IncommingEvent& incommingEvent)
    {
        originState.on_exit(originState, );
        transitionAction();
        destinationState.on_entry();
    }

};

