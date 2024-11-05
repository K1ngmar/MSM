#pragma once

namespace MSM { namespace Utility { namespace Traits {

template<class T, class Event>
concept HasOnEntry = requires(T a, const Event& e) {
    a.on_entry(e);
};

} /* End of namespace Traits */

} /* End of namespace Utility */

} /* End of namespace MSM */
