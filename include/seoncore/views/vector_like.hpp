#pragma once

#include <variant>
#include <seoncore/views/view_vec.hpp>

namespace seoncore::views
{

template <typename TN>
class VectorLike
{
public:
    /**
     * @brief Lightweight vector view wrapper.
     *
     * Holds a non-owning view variant for vector-like operations.
     */

    VectorLike() = default;
private:
    std::variant<
        VectorView<TN>
    > _view = VectorView<TN>();
};

namespace like
{

template <typename TN>
struct VectorLikeDefault : VectorLike<TN>
{
    /**
     * @brief Default VectorLike instance for optional parameters.
     */
};

};

};
