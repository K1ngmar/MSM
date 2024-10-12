#pragma once

#include "Frontend/TTrow.hpp"

namespace MSM
{

namespace Front
{

    /*!
     * @brief Statemachine frontend.
    */
    template <class Derived>
    class StateMachine<Derived>
    {
    private:

        /*!
         * @brief Gets executed on entry of statemachine.
        */
        template <class Event, class FSM>
        virtual void on_entry(Event const& evt, FSM& fsm) = 0;

        /*!
         * @brief Gets executed on exit of state machine.
        */
        template <class Event, class FSM>
        virtual void on_exit(Event const& evt, FSM& fsm)
        {};

        /*!
         * @brief When implementing a State machine overload this function to set the initial state when the state machine is constructed.
        */
        virtual State InitialState() const = 0;
    };


} /* End of namespace Front*/

} /* End of namespace MSM */
