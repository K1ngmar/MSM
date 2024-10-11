#pragma once

namespace MSM
{
    /*!
     * @brief -.
    */
    template <Template Derived>
    class State<Derived>
    {
        
        /*!
         * @brief Function to execute on entry of state.
        */
        template<EventType Event, StateMachineType StateMachine>
        virtual on_entry(const Event& evt, StateMachine& fsm)
        {};

        /*!
         * @brief Function to execute on exit of state.
        */
        template<EventType Event, StateMachineType StateMachine>
        virtual on_exit(const Event& evt, StateMachine& fsm)
        {};
    };

} /* End namespace MSM */
