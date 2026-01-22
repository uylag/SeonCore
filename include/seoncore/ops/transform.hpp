#pragma once

#include <cstddef>
#include <cstdlib>
#include <type_traits>
#include <seoncore/concepts/like_concept.hpp>
#include <seoncore/views/matrix_like.hpp>
#include <seoncore/views/vector_like.hpp>
#include <seoncore/matrix/seonarr_fwd.hpp>
#include <seoncore/enums/policy.hpp>
#include <seoncore/enums/major.hpp>
#include <stdexcept>

namespace seoncore::ops
{

// TODO: abs, sign, clamp, etc.

template <
    typename TN,
    class _Val,
    class _Policy = seoncore::policy::fixed_dense
>
auto abs(const _Val& a) ->
seoncore::matrix::seonarr<TN, _Policy>
requires (
        seoncore::concepts::MatrixBased<_Val> ||
        seoncore::concepts::VectorBased<_Val> ||
        seoncore::concepts::IsDense<_Val>)
{
    seoncore::matrix::seonarr<TN, _Policy> tmp(a);

    for (std::size_t i = 0; i < a.rows(); ++i)
        for (std::size_t j = 0; j < a.cols(); ++j)
            tmp(i, j) = std::abs(a(i, j));

    return tmp;
}
}; // namespace seoncore::ops
