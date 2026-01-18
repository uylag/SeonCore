#pragma once
#include <cstdint>

namespace seoncore::enums
{

/**
 * @brief Dense matrix majoring mode.
 */
enum class Major : int8_t
{
    /** @brief Row-major traversal/layout. */
    Row     = 0,
    /** @brief Column-major traversal/layout. */
    Column  = 1,
};

};
