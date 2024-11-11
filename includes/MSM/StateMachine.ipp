
namespace MSM {

template<class TransitionTableType>
void StateMachine<TransitionTableType>::Start()
{
    // Orthogonal states are not yet supported, so we just just first found initial state.
    using InitialState = std::tuple_element_t<0, typename TransitionTableType::InitialStates>;

    currentStateId = TransitionTableType::template GetStateId<InitialState>();
    InitialState i;
    StateMachineStarting startingEvent;
    MSM::ExecuteOnEntry(i, startingEvent);
};

template<class TransitionTableType>
template <class Event>
void StateMachine<TransitionTableType>::ProcessEvent(const Event& event)
{
    ExecuteTransition(event);
}

template<class TransitionTableType>
template <size_t RowIndex, size_t N, class Event>
void StateMachine<TransitionTableType>::ExecuteTransitionInRow(const Event& event)
{
	using Row = std::tuple_element_t<RowIndex, typename TransitionTable::AllRowsInATuple>;
	using CurrentTransition = std::tuple_element_t<N, typename Row::Transitions>;
	using CurrentState = typename Row::OriginState;

	if constexpr (std::is_same_v<typename CurrentTransition::Event, Event>)
	{
		bool performTransition = true;
		// If there is no guard we always want to perform this transition.
		if constexpr (TransitionHasGuard<CurrentTransition>)
		{
			static_assert(requires { CurrentTransition::ExecuteGuard(event); });
			performTransition = CurrentTransition::ExecuteGuard(event);
		}
		if (performTransition)
		{
			if constexpr (IsEmptyTransition<CurrentTransition>)
			{
				return;
			}

			constexpr auto isTransitioningToOtherState = IsNormalTransition<CurrentTransition>;

			if constexpr (requires { CurrentState::on_exit(event); } && isTransitioningToOtherState)
			{
				CurrentState::on_exit(event);
			}

			if constexpr (TransitionHasAction<CurrentTransition>)
			{
				static_assert(requires { CurrentTransition::ExecuteAction(event); });
				CurrentTransition::ExecuteAction(event);
			}

			if constexpr (isTransitioningToOtherState)
			{
				currentStateId = TransitionTableType::template GetStateId<typename CurrentTransition::TargetState>();
			}

			if constexpr (requires { CurrentTransition::TargetState::on_entry(event); } && isTransitioningToOtherState)
			{
				CurrentTransition::TargetState::on_entry(event);
			}
			return;
		}
	}
	if constexpr (N + 1 < std::tuple_size_v<typename Row::Transitions>)
	{
		ExecuteTransitionInRow<RowIndex, N + 1>(event);
	}
	else
	{
		throw std::runtime_error(
			std::string("Broken state machine, no transition implemented: ") +
			typeid(CurrentState).name() + ", " + typeid(Event).name()
		);
	}
}

template<class TransitionTableType>
template <class Event, size_t N>
void StateMachine<TransitionTableType>::ExecuteTransition(const Event& event)
{
	using CurrentRow = std::tuple_element_t<N, typename TransitionTable::AllRowsInATuple>;
	if (N == currentStateId)
	{
		ExecuteTransitionInRow<N>(event);
		return;
	}
	if constexpr (N + 1 < std::tuple_size_v<typename TransitionTable::AllRowsInATuple>)
	{
		ExecuteTransition<Event, N + 1>(event);
	}
	else
	{
		throw std::runtime_error("Broken state machine, no state found for id: " + std::to_string(currentStateId));
	}
}

} /* End of namespace MSM */