#pragma once

#include "MSM/Utility/UniqueTuple.hpp"

namespace MSM {

    /*!
     * @brief A row is a combination of a OriginState and al list of all transitions possible from this state.
    */
    template <class OriginStateType, class ...TransitionTypes>
    struct Row
    {
        using OriginState = OriginStateType;
        
        using Transitions = std::tuple<TransitionTypes...>;

        /*!
         * @brief A tuple containing all unique events defined in this row.
        */
        using UniqueEventsInThisRow = MSM::Utility::UniqueTupleFromTuple
        <
            MSM::Utility::tuple_cat_t
            <
                std::tuple<typename TransitionTypes::Event>...
            >
        >;
    };

} /* End of namespace MSM */
