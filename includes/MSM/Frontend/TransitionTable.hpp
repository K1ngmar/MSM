#pragma once

#include "MSM/Backend/Utility/Utility.hpp"

#include <tuple>

namespace MSM { namespace Front {

	/*!
	 * @brief In your frontend statemachine define `using TransitionTable = MSM::Front::StateMachine<Row....>` 
	 *		  To declare a statemachine.
	 *
	 * @tparam Rows Parameter pack containing all possible states and transitions. All rows should be of type MSM::Front::Row.
	*/
	template<typename ...Rows>
	struct TransitionTable
	{
		using AllRowsInATuple = MSM::Back::Utility::tuple_cat_t<std::tuple<Rows>...>;
	};

} /* End of namespace Front */

} /* End of namespace MSM */
