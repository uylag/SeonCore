#pragma once

#include <cstddef>
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
    seoncore::enums::Major,
    class _Policy
>
class seonarr;

};

namespace seoncore::ops
{

/**
 * @brief Dot product between two matrix-like operands.
 * @param x Left-hand matrix.
 * @param y Right-hand matrix.
 * @return Dot product value.
 */
template <typename TN, class _LeftVal, class _RightVal>
auto dot(
        const _LeftVal& x, 
        const _RightVal& y
    ) -> TN
{
    static_assert(
        (seoncore::concepts::MatrixBased<_LeftVal> && seoncore::concepts::MatrixBased<_RightVal>) ||
        (seoncore::concepts::MatrixBased<_LeftVal> && seoncore::concepts::VectorBased<_RightVal>) ||
        (seoncore::concepts::VectorBased<_LeftVal> && seoncore::concepts::MatrixBased<_RightVal>) ||
        (seoncore::concepts::VectorBased<_LeftVal> && seoncore::concepts::VectorBased<_RightVal>),
        "dot(x, y): arguments must be both MatrixLike or VectorLike."
    );

    TN result = TN{0};

    if constexpr (seoncore::concepts::MatrixBased<_LeftVal>)
    {
        const std::size_t x_rows = x.rows();
        const std::size_t x_cols = x.cols();

        if constexpr (seoncore::concepts::MatrixBased<_RightVal>)
        {
            const std::size_t y_rows = y.rows();
            const std::size_t y_cols = y.cols();

            if (x_rows != y_rows || x_cols != y_cols)
            {
                throw std::runtime_error("dot(x, y): rows and cols for both MatrixLike must be equal.");
            };

            for (std::size_t i = 0; i < x_rows; ++i)
                for (std::size_t j = 0; j < x_cols; ++j)
                    result += ( x(i, j) * y(i, j) );
        }
        else if constexpr (seoncore::concepts::VectorBased<_RightVal>)
        {
            const std::size_t y_size = y.size();

            if (x_rows * x_cols != y_size)
            {
                throw std::runtime_error("dot(x, y): rows and cols of x (MatrixLike) must be equal y size (VectorLike).");
            };

            _LeftVal y_matrix = y.to_matrix();

            for (std::size_t i = 0; i < x_rows; ++i)
                for (std::size_t j = 0; j < x_cols; ++j)
                    result += ( x(i, j) * y_matrix(i, j) );
        };
    }
    else if constexpr (seoncore::concepts::VectorBased<_LeftVal>)
    {
        if constexpr (seoncore::concepts::MatrixBased<_RightVal>)
        {

        }
        else if constexpr (seoncore::concepts::VectorBased<_RightVal>)
        {

        };
    };

    return result;
};

/**
 * @brief General matrix-vector product (A * x).
 * @param A Input matrix.
 * @param x Input vector.
 * @param alpha Scalar multiplier for A * x.
 * @param y Optional vector to combine with.
 * @param beta Scalar multiplier for y.
 * @return Result vector in a seonarr container.
 */
template <typename TN, class _FirstVal, class _SecondVal, class _OptVal>
auto gemv(
        const seoncore::views::MatrixLike<TN>& A,
        const seoncore::views::VectorLike<TN>& x,
        TN alpha = 1,
        const seoncore::views::VectorLike<TN>& y = 
            seoncore::views::like::VectorLikeDefault<TN>(),
        TN beta = 0
    ) -> seoncore::matrix::seonarr<
                TN,
                seoncore::enums::Major::Row,
                seoncore::policy::auto_select
            >
{
};

template <typename TN>
auto gemm(
        const seoncore::views::MatrixLike<TN>& A,
        const seoncore::views::MatrixLike<TN>& B,
        TN alpha = 1,
        const seoncore::views::MatrixLike<TN>& C = 
            seoncore::views::like::MatrixLikeDefault<TN>(),
        TN beta = 0
    ) -> seoncore::matrix::seonarr<
                TN,
                seoncore::enums::Major::Row,
                seoncore::policy::auto_select
            >
{
    /**
     * @brief General matrix-matrix product (A * B).
     * @param A Left-hand matrix.
     * @param B Right-hand matrix.
     * @param alpha Scalar multiplier for A * B.
     * @param C Optional matrix to combine with.
     * @param beta Scalar multiplier for C.
     * @return Result matrix in a seonarr container.
     */
    //(A, B, alpha, C, beta);
    return seoncore::matrix::seonarr<
        TN, 
        seoncore::enums::Major::Row,
        seoncore::policy::fixed_dense
    >();
};

// TODO: Hadamard(A, B) = A_ij * B_ij

};
