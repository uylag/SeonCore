#pragma once

#include <concepts>
#include <cstddef>

namespace seoncore::concepts
{

template <class M>
concept MatrixLike =
requires(M m, std::size_t i, std::size_t j)
{
    typename M::value_type;

    { m.rows() } -> std::convertible_to<std::size_t>;
    { m.cols() } -> std::convertible_to<std::size_t>;
    m(i, j);
};


}; // namespace seoncore::concepts
