#pragma once

namespace MSM {

    /*!
     * @brief Tag for a normal transition without action or guard.
     *        Transition<Event, Target, none, none>
    */
    struct Normal_Transition_Tag {};

    /*!
     * @brief Tag for a normal transition without guard.
     *        Transition<Event, Target, Action, none>
    */
    struct Normal_Transition_With_Action_Tag {};

    /*!
     * @brief Tag for a normal transition without action.
     *        Transition<Event, Target, none, Guard>
    */
    struct Normal_Transition_With_Guard_Tag {};

    /*!
     * @brief Tag for a normal transition without action.
     *        Transition<Event, Target, Action, Guard>
    */
    struct Normal_Transition_With_Action_And_Guard_Tag {};

    /*!
     * @brief Tag for an internal transition without guard.
     *        Transition<Event, none, Action, none>
    */
    struct Internal_Transition_Tag {};

    /*!
     * @brief Tag for an internal transition without action or guard.
     *        Transition<Event, none, Action, Guard>
    */
    struct Internal_Transition_With_Guard_Tag {};

    /*!
     * @brief Tag for an empty transition without action.
     *        Transition<Event, none, none, Guard>
     *        This type of transition can be used to ignore events only when the guard is satisfied.
    */
    struct Empty_Transition_With_Guard_Tag {};

    /*!
     * @brief Tag for an empty transition without action.
     *        Transition<Event, none, none, none>
     *        This type of transition can be used to ignore events.
    */
    struct Empty_Transition_Tag {};

    /*!
     * @brief Checks whether the transition has a guard.
    */
    template <typename T>
    concept TransitionHasGuard =
        std::is_same_v<typename T::TransitionType_Tag, Normal_Transition_With_Guard_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Normal_Transition_With_Action_And_Guard_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Internal_Transition_With_Guard_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Empty_Transition_With_Guard_Tag>;

    /*!
     * @brief Checks whether the transition has an action.
    */
    template <typename T>
    concept TransitionHasAction =
        std::is_same_v<typename T::TransitionType_Tag, Normal_Transition_With_Action_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Normal_Transition_With_Action_And_Guard_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Internal_Transition_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Internal_Transition_With_Guard_Tag>;

    /*!
     * @brief Checks wether the transition has a target state.
    */
    template <typename T>
    concept IsNormalTransition =
        std::is_same_v<typename T::TransitionType_Tag, Normal_Transition_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Normal_Transition_With_Action_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Normal_Transition_With_Guard_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Normal_Transition_With_Action_And_Guard_Tag>;

    /*!
     * @brief Checks wether the transition has no target state but does have an action.
    */
    template <typename T>
    concept IsInternalTransition =
        std::is_same_v<typename T::TransitionType_Tag, Internal_Transition_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Internal_Transition_With_Guard_Tag>;

    /*!
     * @brief Checks wether the transition has no target state and no action.
    */
    template <typename T>
    concept IsEmptyTransition =
        std::is_same_v<typename T::TransitionType_Tag, Empty_Transition_With_Guard_Tag> ||
        std::is_same_v<typename T::TransitionType_Tag, Empty_Transition_Tag>;


} /* End of namespace MSM*/
