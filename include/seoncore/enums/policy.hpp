#pragma once

namespace seoncore::policy
{

    /** @brief Policy tag: fixed dense storage. */
    struct fixed_dense   {};
    /** @brief Policy tag: fixed sparse storage. */
    struct fixed_sparse  {};
    /** @brief Policy tag: select storage automatically.
     *  Choose if you're sure what you doing.
     */
    struct auto_select   {};

};
