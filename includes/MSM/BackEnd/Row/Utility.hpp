#pragma once

namespace MSM { namespace Back { namespace Utility {

template<class ...Rows>
void PrintRows(std::tuple<Rows...> transitionTable)
{
    ((
        std::cout << typeid(typename Rows::State).name() << ", " <<
                     typeid(typename Rows::Event).name() << ", " <<
                     typeid(typename Rows::Guard).name() << std::endl
    ), ...);
}


} /* End of namespace Utility */

} /* End of namespace Back */

} /* End of namespace MSM */
