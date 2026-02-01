#pragma once

#include <seoncore/ops/matmul.hpp>
#include <seoncore/matrix/dense.hpp>

namespace seoncore::ops
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

}; // namespace seoncore::ops
