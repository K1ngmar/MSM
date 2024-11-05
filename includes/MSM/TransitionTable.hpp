#pragma once

#include "MSM/State.hpp"
#include "MSM/Utility/Utility.hpp"

#include <tuple>
#include <typeinfo>

namespace MSM {

// forward declaration
template<class TransitionTableType>
class StateMachine;

/*!
 * @brief -.
 *
 * @tparam Rows Parameter pack containing all possible states and transitions. All rows should be of type MSM::Row.
*/
template<typename ...Rows>
class TransitionTable
{
private:

	friend class StateMachine<TransitionTable<Rows...>>;

	using AllRowsInATuple = std::tuple<Rows...>;

	/*!
	 * @brief Gets all states with the State_Type_Initial_Tag and stores them in a tuple.
	*/
	using InitialStates = MSM::Utility::tuple_cat_t<
		std::conditional_t<
			std::is_same_v<typename Rows::OriginState::StateType, MSM::State_Type_Initial_Tag>,
			std::tuple<typename Rows::OriginState>,
			std::tuple<>
		>...
	>;

	template<class State, size_t N = 0>
	static size_t GetStateId()
	{
		if constexpr (std::is_same_v<typename std::tuple_element_t<N, AllRowsInATuple>::OriginState, State>)
		{
			return N;
		}
		if constexpr (N + 1 < std::tuple_size_v<AllRowsInATuple>)
		{
			return GetStateId<State, N + 1>();
		}
		else
		{
			throw std::runtime_error(std::string("Could not find id for state ") + typeid(State).name());
		}
	}

	template <class Event, size_t N = 0>
	static void ExecuteTransition(const size_t currentStateId, const Event& event)
	{
		using CurrentRow = std::tuple_element_t<N, AllRowsInATuple>;
		if (N == currentStateId)
		{
			CurrentRow::ExecuteTransition(event);
			return;
		}
		if constexpr (N + 1 < std::tuple_size_v<AllRowsInATuple>)
		{
			ExecuteTransition<Event, N + 1>(currentStateId, event);
		}
		else
		{
			throw std::runtime_error("Broken state machine, no state found for id: " + std::to_string(currentStateId));
		}
	}
};

} /* End of namespace MSM */
