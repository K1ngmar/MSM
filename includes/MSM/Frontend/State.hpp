#pragma once

namespace MSM
{
    /*!
     * @brief -.
    */
    template <class Derived>
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

    /*!
     * @brief A transition to a state inheiriting TerminateState will be the last transition executed.
     *        The statemachine will stop running after the on_entry() of this state is reached.
    */
    template <class Derived>
    class TerminateState<Derived>
    {

    };

} /* End namespace MSM */
