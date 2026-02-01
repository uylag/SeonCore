#pragma once

#include <seoncore/ops/matmul.hpp>
#include <seoncore/concepts/matrix_like.hpp>

namespace seoncore::matrix
{

template <class A, class B>
requires seoncore::concepts::MatrixLike<A> && seoncore::concepts::MatrixLike<B>
constexpr auto operator*(const A& a, const B& b)
{
    return seoncore::ops::matmul(a, b);
}

} // namespace seoncore::matrix

