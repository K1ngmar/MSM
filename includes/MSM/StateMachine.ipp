
namespace MSM {

template<class TransitionTableType>
void StateMachine<TransitionTableType>::Start()
{
	isStatemachineRunning = true;
    // Orthogonal states are not yet supported, so we just just first found initial state.
    using InitialState = std::tuple_element_t<0, typename TransitionTableType::InitialStates>;

    currentStateId = TransitionTableType::template GetStateId<InitialState>();
    ExecuteOnEntryIfDefined<InitialState>(InternalEvents::StateMachineStarting());
};

template<class TransitionTableType>
void StateMachine<TransitionTableType>::Stop()
{
	isStatemachineRunning = false;
	ExecuteOnExitOfCurrentStateIfDefined(InternalEvents::StateMachineStopping());
}

template<class TransitionTableType>
template <class Event, size_t N>
void StateMachine<TransitionTableType>::ExecuteOnExitOfCurrentStateIfDefined(const Event& event)
{
	using CurrentState = std::tuple_element_t<N, typename TransitionTable::AllRowsInATuple>::OriginState;
	if (N == currentStateId)
	{
		ExecuteOnExitIfDefined<CurrentState>(event);
		return;
	}
	if constexpr (N + 1 < std::tuple_size_v<typename TransitionTable::AllRowsInATuple>)
	{
		ExecuteOnExitOfCurrentStateIfDefined<Event, N + 1>(event);
	}
	else
	{
		isStatemachineRunning = false;
		throw std::runtime_error("Broken state machine, no state found for id: " + std::to_string(currentStateId));
	}
}

template<class TransitionTableType>
bool StateMachine<TransitionTableType>::IsStatemachineRunning() const
{
	return isStatemachineRunning;
}

template<class TransitionTableType>
template <class Event>
bool StateMachine<TransitionTableType>::ProcessEvent(const Event& event)
{
	if (!isStatemachineRunning) {
		return false;
	}
	ExecuteTransition(event);
	return true;
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

			if constexpr (isTransitioningToOtherState)
			{
				ExecuteOnExitIfDefined<CurrentState>(event);
			}

			if constexpr (TransitionHasAction<CurrentTransition>)
			{
				static_assert(requires { CurrentTransition::ExecuteAction(event); });
				CurrentTransition::ExecuteAction(event);
			}

			if constexpr (isTransitioningToOtherState)
			{
				static_assert(requires {sizeof(typename CurrentTransition::TargetState);} );
				currentStateId = TransitionTableType::template GetStateId<typename CurrentTransition::TargetState>();

				ExecuteOnEntryIfDefined<typename CurrentTransition::TargetState>(event);
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
		isStatemachineRunning = false;
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
		isStatemachineRunning = false;
		throw std::runtime_error("Broken state machine, no state found for id: " + std::to_string(currentStateId));
	}
}

} /* End of namespace MSM */