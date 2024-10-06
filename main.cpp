
#include <string>
#include <iostream>
#include <tuple>

template<size_t I, typename FunctionType, class ...Rows>
inline typename std::enable_if<I == sizeof...(Rows), void>::type
for_each_row(FunctionType) // empty implementation
{
    std::cout << "empty implementation" << std::endl;
}

template<size_t I = 0, typename FunctionType, class OriginState, class Event, class DestinationState, class TransitionFunction, class Guard, typename... TupleTypes>
inline typename std::enable_if<I < sizeof...(TupleTypes), void>::type
for_each_row(const std::tuple<OriginState, Event, DestinationState, TransitionFunction, Guard>& row, FunctionType f)
{
    std::cout << "implementation" << std::endl;
	f(row);
	for_each_row<I + 1, FunctionType, TupleTypes...>(row, f);
}


/*!
 * @brief Backend for a Meta State Machine.
 * When you intheirit this class make sure you:
 * -
*/
template<class ...Rows>
struct MSM
{
	template <class Event>
	void ProcessEvent(const Event& event)
	{
        std::cout << "Processing event" << std::endl;
        int currentState;
		TransitionState(currentState, event);
	}

    template <class T>
    void SetStateActive(const T& newState)
    {
        std::cout << "activated state: " << typeid(newState).name() << std::endl;
    }

    template <class T>
    void SetStateInactive(const T& stateToInactivate)
    {
        std::cout << "activated state: " << typeid(stateToInactivate).name() << std::endl;
    }

	template<class CurrentState, class Event>
	void TransitionState(const CurrentState& currentState, const Event& incommingEvent)
	{
        std::cout << "Transitioning state" << std::endl;
		for_each_row([&]<typename ...RowData>(const std::tuple<RowData...>& row, Rows...)
		{
			const auto& [originState, event, destinationState, transitionFunction, guard] = row;
		
            std::cout << "Checking transitions" << std::endl;
			if constexpr (currentState == originState && incommingEvent == event)
			{
                std::cout << "checking guard" << std::endl;
				if (guard())
				{
					SetStateActive(destinationState);
					transitionFunction();
					SetStateInactive(originState);
                    return;
				}
			}
		});
        throw std::runtime_error("Transition not implemented!!!");
	}

};

namespace Guards
{
    struct None
    {
        bool operator()()
        {
            std::cout << "executing guard" << std::endl;
            return true;
        }
    };
}

bool GuardFunc()
{
    return true;
}

int main()
{
    MSM<
        std::tuple<int, float, double, char, Guards::None>,
        std::tuple<int, std::string, double, char, Guards::None>,
        std::tuple<std::string, int, char, float, Guards::None>
    > stateMachine;

    float event;
    stateMachine.ProcessEvent(event);

    return 0;
}
