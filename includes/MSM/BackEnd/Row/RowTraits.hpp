#pragma once

namespace MSM
{
    /*!
     * @brief Tag for a normal transition without action or guard.
     *        Row<Origin, Event, Target, none, none>
    */
    struct Normal_Transition_Tag {};

    /*!
     * @brief Tag for a normal transition without guard.
     *        Row<Origin, Event, Target, Action, none>
    */
    struct Normal_Transition_With_Action_Tag {};

    /*!
     * @brief Tag for a normal transition without action.
     *        Row<Origin, Event, Target, none, Guard>
    */
    struct Normal_Transition_With_Guard_Tag {};

    /*!
     * @brief Tag for a normal transition without action.
     *        Row<Origin, Event, Target, Action, Guard>
    */
    struct Normal_Transition_With_Action_And_Guard_Tag {};

    /*!
     * @brief Tag for an internal transition without guard.
     *        Row<Origin, Event, none, Action, none>
    */
    struct Internal_Transition_Tag {};

    /*!
     * @brief Tag for an internal transition without action or guard.
     *        Row<Origin, Event, none, Action, Guard>
    */
    struct Internal_Transition_With_Guard_Tag {};

    /*!
     * @brief Tag for an internal transition without action.
     *        Row<Origin, Event, none, none, Guard>
     *        This type of transition can be used to ignore events only when the guard is satisfied.
    */
    struct Empty_Transition_With_Guard_Tag {};

    /*!
     * @brief Tag for an internal transition without action.
     *        Row<Origin, Event, none, none, none>
     *        This type of transition can be used to ignore events.
    */
    struct Empty_Transition_Tag {};

} /* End of namespace MSM*/
