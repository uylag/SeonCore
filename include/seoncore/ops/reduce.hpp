#pragma once

#include <algorithm>
#include <numeric>
#include <seoncore/concepts/matrix_like.hpp>
#include <seoncore/views/vec.hpp>

namespace seoncore::ops
{

template <class A>
requires seoncore::concepts::MatrixLike<A>
constexpr auto sum(const A& a) -> typename std::remove_cvref_t<A>::value_type
{
    using M = std::remove_cvref_t<A>;
    using TN = typename M::value_type;

    seoncore::views::VectorView<TN> tmp = a.flatten();
    return std::accumulate(tmp.begin(), tmp.end(), 0.0);
};

template <class A>
requires seoncore::concepts::MatrixLike<A>
constexpr auto min(const A& a) -> typename std::remove_cvref_t<A>::value_type
{
    using M = std::remove_cvref_t<A>;
    using TN = typename M::value_type;

    seoncore::views::VectorView<TN> tmp = a.flatten();
    return *std::min_element(tmp.begin(), tmp.end());
};

template <class A>
requires seoncore::concepts::MatrixLike<A>
constexpr auto max(const A& a) -> typename std::remove_cvref_t<A>::value_type
{
    using M = std::remove_cvref_t<A>;
    using TN = typename M::value_type;

    seoncore::views::VectorView<TN> tmp = a.flatten();
    return *std::max_element(tmp.begin(), tmp.end());
};


};
