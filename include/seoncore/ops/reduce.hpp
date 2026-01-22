#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <seoncore/concepts/like_concept.hpp>
#include <seoncore/views/matrix_like.hpp>
#include <seoncore/views/vector_like.hpp>
#include <seoncore/matrix/seonarr_fwd.hpp>
#include <seoncore/enums/policy.hpp>
#include <seoncore/enums/major.hpp>
#include <numeric>
#include <stdexcept>
#include <type_traits>

namespace seoncore::ops
{

// TODO: sum, max, min, norm_p, etc.



template <typename TN, class _Val>
auto sum(const _Val& a) -> TN
requires (
        seoncore::concepts::MatrixBased<_Val> ||
        seoncore::concepts::VectorBased<_Val>)
{
    return std::accumulate(a.begin(), a.end(), 0);
};

template <typename TN, class _Val>
auto max(const _Val& a) -> TN
requires (
        seoncore::concepts::MatrixBased<_Val> ||
        seoncore::concepts::VectorBased<_Val>)
{
     return *std::max_element(a.begin(), a.end());
};

template <typename TN, class _Val>
auto min(const _Val& a) -> TN
requires (
        seoncore::concepts::MatrixBased<_Val> ||
        seoncore::concepts::VectorBased<_Val>)
{
     return *std::min_element(a.begin(), a.end());
};

template <typename TN, class _Val>
auto norm_p(const _Val& a, std::size_t p) -> TN
requires (
        seoncore::concepts::MatrixBased<_Val> ||
        seoncore::concepts::VectorBased<_Val> ||
        seoncore::concepts::IsDense<_Val>)
{
    TN result = TN{0};

    if constexpr (seoncore::concepts::IsDense<_Val>)
    {
        seoncore::views::MatrixLike<TN> tmp = a.get_view();
        for (auto& elem : tmp)
            result += std::pow(elem, p);
    }
    else
    {
        for (auto& elem : a)
            result += std::pow(elem, p);
    };

    return std::pow(result, 1.0/p);
};

};
