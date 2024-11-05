#pragma once

#include "MSM/Utility/TypeTraits.hpp"

namespace MSM {

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
    template <class StateTypeTag = State_Type_Normal_Tag>
    struct State
    {
        using StateType = StateTypeTag;
    };

    template<class State, class Event>
    void ExecuteOnEntry(State& state, const Event& e)
    {
        state.on_entry(e);
    }

} /* End namespace MSM */