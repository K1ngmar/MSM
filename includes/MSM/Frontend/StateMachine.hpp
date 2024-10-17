#pragma once

#include "Frontend/TTrow.hpp"

namespace MSM { namespace Front {

    /*!
     * @brief Statemachine frontend.
    */
    class StateMachine
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

    };


} /* End of namespace Front */

} /* End of namespace MSM */
