
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
	using OriginState = typename Row::OriginState;

	if constexpr (std::is_same_v<typename CurrentTransition::Event, Event>)
	{
		bool performTransition = true;
		if constexpr (requires { CurrentTransition::ExecuteGuard(event); })
		{
			performTransition = CurrentTransition::ExecuteGuard(event);
		}
		if (performTransition)
		{
			// TODO: only perform on exit when a target state is found.
			if constexpr (requires { OriginState::on_exit(event); })
			{
				// std::cout << "Performing on_exit of current state:" + std::string(typeid(OriginState).name()) + "\n";
				OriginState::on_exit(event);
			}
			if constexpr (requires { CurrentTransition::ExecuteAction(event); })
			{
				// std::cout << "Performing action:\n";
				CurrentTransition::ExecuteAction(event);
			}
			if constexpr (requires { CurrentTransition::TargetState::on_entry(event); })
			{
				// TODO also switch to new state when no on entry is found but state does exist.
				currentStateId = TransitionTableType::template GetStateId<typename CurrentTransition::TargetState>();
				// std::cout << "Performing on_entry of target state: " + std::string(typeid(typename CurrentTransition::TargetState).name()) + "\n";
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
			typeid(OriginState).name() + ", " + typeid(Event).name()
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