
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
void StateMachine<TransitionTableType>::
void ProcessEvent(const Event& e);

} /* End of namespace MSM */