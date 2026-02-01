#pragma once

#include <type_traits>
#include <seoncore/matrix/dense_fwd.hpp>
#include <seoncore/concepts/matrix_like.hpp>
#include <cassert>
#include <cstddef>
#include <utility>
#include <concepts>

namespace seoncore::tags
{
struct matmul_t
{
    template <class A, class B>
    constexpr auto operator()(A&& a, B&& b) const
        noexcept(noexcept(tag_invoke(*this, std::forward<A>(a), std::forward<B>(b))))
        -> decltype(tag_invoke(*this, std::forward<A>(a), std::forward<B>(b)))
    {
        return tag_invoke(*this, std::forward<A>(a), std::forward<B>(b));
    }
};

inline constexpr matmul_t matmul{};

}; // namespace seoncore::tags

namespace seoncore::ops
{

template <class A, class B>
concept has_tagged_matmul =
requires(A&& a, B&& b)
{
    tag_invoke(seoncore::tags::matmul, std::forward<A>(a), std::forward<B>(b));
};

template <seoncore::concepts::MatrixLike A, seoncore::concepts::MatrixLike B>
constexpr auto matmul_fallback(const A& a, const B& b)
{
    using value_type = std::remove_cvref_t<decltype(a(0,0) * b(0,0))>;

    assert(a.cols() == b.rows());

    seoncore::matrix::DenseMatrix<value_type> c(a.rows(), b.cols());

    for (std::size_t i = 0; i < a.rows(); ++i)
    {
        for (std::size_t j = 0; j < b.cols(); ++j)
        {
            value_type acc{};
            for (std::size_t k = 0; k < a.cols(); ++k)
                acc += a(i, k) * b(k, j);

            c(i, j) = acc;
        };
    };
    return c;
};

template <seoncore::concepts::MatrixLike A, seoncore::concepts::MatrixLike B>
constexpr auto matmul(const A& a, const B& b)
{
    if constexpr (has_tagged_matmul<const A&, const B&>)
    {
        return tag_invoke(seoncore::tags::matmul, a, b);
    }
    else
    {
        return matmul_fallback(a, b);
    };
};

}; // namespace seoncore::ops
