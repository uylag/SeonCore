#pragma once

#include <seoncore/matrix/dense_fwd.hpp>
#include <cstddef>
#include <utility>
#include <type_traits>
#include <concepts>
#include <iostream>
#include <seoncore/ops/tag_invoke.hpp>
#include <seoncore/concepts/matrix_like.hpp>

namespace seoncore::tags
{

struct abs_t
{

template <class A>
constexpr auto operator()(A&& a) const 
    noexcept(noexcept(tag_invoke(*this, std::forward<A>(a))))
    -> decltype(tag_invoke(*this, std::forward<A>(a)))
{
    return tag_invoke(*this, std::forward<A>(a));
};

}; // struct abs_t

inline constexpr abs_t abs{};

}; // namespace seoncore::tags


namespace seoncore::ops
{

template <class A>
concept has_tagged_abs = 
requires(A&& a)
{
    tag_invoke(seoncore::tags::abs_t{}, std::forward<A>(a));
};

template <seoncore::concepts::MatrixLike A>
constexpr auto abs_fallback(const A& a) 
{
    using value_type = std::remove_cvref_t<decltype(a(0, 0))>;

    // TODO: fallback in dense matrix, do abstract matrix `seonarr`
    seoncore::matrix::DenseMatrix<value_type> tmp(a.rows(), a.cols());

    for (std::size_t i = 0; i < a.rows(); ++i)
        for (std::size_t j = 0; j < a.cols(); ++j)
        {
            tmp(i, j) = (a(i, j) < value_type{0}) ? (a(i, j) * -1) : a(i, j);
        }

    return tmp;
};

template <seoncore::concepts::MatrixLike A>
constexpr auto abs(const A& a)
{
    if constexpr (has_tagged_abs<const A&>)
    {
        // TODO: delete this "for tests" log
        std::cout << "Abs tag invoked.\n";
        return tag_invoke(seoncore::tags::abs_t{}, a);
    }
    else
    {
        std::cout << "Abs fallback invoked.\n";
        return abs_fallback(a);
    };
};

};
