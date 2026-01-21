#pragma once

#include <cstddef>
#include <cstdlib>
#include <seoncore/concepts/like_concept.hpp>
#include <seoncore/views/matrix_like.hpp>
#include <seoncore/views/vector_like.hpp>
#include <seoncore/enums/policy.hpp>
#include <seoncore/enums/major.hpp>
#include <stdexcept>

namespace seoncore::matrix
{
template <
    typename TN,
    seoncore::enums::Major _Major,
    class _Policy
>
class seonarr; // class seonarr<TN, _Major, _Policy>
}; // namespace seoncore::matrix

namespace seoncore::ops
{

// TODO: abs, sign, clamp, etc.


template <typename TN, class _Val, seoncore::enums::Major _Major, class _Policy>
auto abs(const _Val& a) ->
seoncore::matrix::seonarr<TN, _Major, _Policy>
requires (
        seoncore::concepts::MatrixBased<_Val> ||
        seoncore::concepts::VectorBased<_Val> ||
        seoncore::concepts::IsMatrix<_Val>)
{
    seoncore::matrix::seonarr<TN, _Major, _Policy> tmp(a);

    for (std::size_t i = 0; i < a.rows(); ++i)
        for (std::size_t j = 0; j < a.cols(); ++j)
            tmp(i, j) = std::abs(a(i, j));

    return tmp;
}
}; // namespace seoncore::ops
