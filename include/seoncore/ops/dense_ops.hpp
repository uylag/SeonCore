#pragma once

#include <seoncore/ops/matmul.hpp>
#include <seoncore/ops/transform.hpp>
#include <seoncore/views/vec.hpp>
#include <seoncore/matrix/dense.hpp>

namespace seoncore::matrix
{

template <typename TN>
constexpr auto tag_invoke(
    seoncore::tags::matmul_t,
    const seoncore::matrix::DenseMatrix<TN>& A,
    const seoncore::matrix::DenseMatrix<TN>& B)
{
    assert(A.cols() == B.rows());

    seoncore::matrix::DenseMatrix<TN> C(A.rows(), B.cols());

    for (std::size_t i = 0; i < A.rows(); ++i)
    {
        for (std::size_t k = 0; k < A.cols(); ++k)
        {
            const TN aik = A(i, k);
            for (std::size_t j = 0; j < B.cols(); ++j)
                C(i, j) += aik * B(k, j);
        };
    };
    return C;
};

template <typename TN>
constexpr auto tag_invoke(
    seoncore::tags::abs_t,
    const seoncore::matrix::DenseMatrix<TN>& A)
{
    seoncore::matrix::DenseMatrix<TN> tmp(A);
    seoncore::views::MutableVectorView<TN> tmpv = tmp.flatten();
    for (auto& elem : tmpv)
        if (elem < TN{0}) elem *= -1;

    return tmp;
};

}; // namespace seoncore::matrix
