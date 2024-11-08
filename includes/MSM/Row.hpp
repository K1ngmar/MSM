#pragma once

namespace MSM {

    /*!
     * @brief A row is a combination of a OriginState and al list of all transitions possible from this state.
    */
    template <class OriginStateType, class ...TransitionTypes>
    struct Row
    {
        using OriginState = OriginStateType;
        
        using Transitions = std::tuple<TransitionTypes...>;
    };

} /* End of namespace MSM */
