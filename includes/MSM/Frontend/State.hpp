#pragma once

namespace MSM { namespace Front {

    /*!
     * @brief Tag to use for the inital state, no transition to this state will be possible.
    */
    struct State_Type_Initial_Tag {};

    /*!
     * @brief Tag to use for normal states.
    */
    struct State_Type_Normal_Tag {};

    /*!
     * @brief Tag to use for the terminal state, no state transition from this state will be possible.
    */
    struct State_Type_Final_Tag {};


    /*!
     * @brief -.
    */
    template <class StateTypeTag = State_Type_Initial_Tag>
    class State
    {
        using StateType = StateTypeTag;
        
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

} /* End namespace Front*/

} /* End namespace MSM */
