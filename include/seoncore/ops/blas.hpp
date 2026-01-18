#pragma once

#include <seoncore/views/matrix_like.hpp>
#include <seoncore/views/vector_like.hpp>
#include <seoncore/enums/policy.hpp>
#include <seoncore/enums/major.hpp>

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

template <typename TN>
auto dot(
        const seoncore::views::VectorLike<TN>& x, 
        const seoncore::views::VectorLike<TN>& y
    ) -> TN
{
    /**
     * @brief Dot product between two vector-like operands.
     * @param x Left-hand vector.
     * @param y Right-hand vector.
     * @return Dot product value.
     */
    return TN{0};
};

template <typename TN>
auto dot(
        const seoncore::views::MatrixLike<TN>& x, 
        const seoncore::views::MatrixLike<TN>& y
    ) -> TN
{
    /**
     * @brief Dot product between two matrix-like operands.
     * @param x Left-hand matrix.
     * @param y Right-hand matrix.
     * @return Dot product value.
     */
    return TN{0};
};

template <typename TN>
auto dot(
        const seoncore::views::MatrixLike<TN>& x, 
        const seoncore::views::VectorLike<TN>& y
    ) -> TN
{
    /**
     * @brief Dot product between matrix-like and vector-like operands.
     * @param x Left-hand matrix.
     * @param y Right-hand vector.
     * @return Dot product value.
     */
    return TN{0};
};

template <typename TN>
auto dot(
        const seoncore::views::VectorLike<TN>& x, 
        const seoncore::views::MatrixLike<TN>& y
    ) -> TN
{
    /**
     * @brief Dot product between vector-like and matrix-like operands.
     * @param x Left-hand vector.
     * @param y Right-hand matrix.
     * @return Dot product value.
     */
    return TN{0};
};

template <typename TN>
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
    /**
     * @brief General matrix-vector product (A * x).
     * @param A Input matrix.
     * @param x Input vector.
     * @param alpha Scalar multiplier for A * x.
     * @param y Optional vector to combine with.
     * @param beta Scalar multiplier for y.
     * @return Result vector in a seonarr container.
     */
//(A, x, alpha, y, beta);
    return seoncore::matrix::seonarr<
        TN, 
        seoncore::enums::Major::Row,
        seoncore::policy::auto_select
    >();
};

template <typename TN>
auto gemv(
        const seoncore::views::MatrixLike<TN>& A,
        const seoncore::views::MatrixLike<TN>& x,
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
    /**
     * @brief General matrix-matrix product with vector-like output.
     * @param A Input matrix.
     * @param x Input matrix.
     * @param alpha Scalar multiplier for A * x.
     * @param y Optional vector to combine with.
     * @param beta Scalar multiplier for y.
     * @return Result container in a seonarr.
     */
    //(A, x, alpha, y, beta);
    return seoncore::matrix::seonarr<
        TN, 
        seoncore::enums::Major::Row,
        seoncore::policy::auto_select
    >();
};

template <typename TN>
auto gemv(
        const seoncore::views::MatrixLike<TN>& A,
        const seoncore::views::VectorLike<TN>& x,
        TN alpha = 1,
        const seoncore::views::MatrixLike<TN>& y = 
            seoncore::views::like::MatrixLikeDefault<TN>(),
        TN beta = 0
    ) -> seoncore::matrix::seonarr<
                TN,
                seoncore::enums::Major::Row,
                seoncore::policy::auto_select
            >
{
    /**
     * @brief General matrix-vector product with matrix-like accumulator.
     * @param A Input matrix.
     * @param x Input vector.
     * @param alpha Scalar multiplier for A * x.
     * @param y Optional matrix to combine with.
     * @param beta Scalar multiplier for y.
     * @return Result container in a seonarr.
     */
    //(A, x, alpha, y, beta);
    return seoncore::matrix::seonarr<
        TN, 
        seoncore::enums::Major::Row,
        seoncore::policy::auto_select
    >();
};

template <typename TN>
auto gemv(
        const seoncore::views::MatrixLike<TN>& A,
        const seoncore::views::MatrixLike<TN>& x,
        TN alpha = 1,
        const seoncore::views::MatrixLike<TN>& y = 
            seoncore::views::like::MatrixLikeDefault<TN>(),
        TN beta = 0
    ) -> seoncore::matrix::seonarr<
                TN,
                seoncore::enums::Major::Row,
                seoncore::policy::auto_select
            >
{
    /**
     * @brief General matrix-matrix product with matrix-like accumulator.
     * @param A Input matrix.
     * @param x Input matrix.
     * @param alpha Scalar multiplier for A * x.
     * @param y Optional matrix to combine with.
     * @param beta Scalar multiplier for y.
     * @return Result container in a seonarr.
     */
    //(A, x, alpha, y, beta);
    return seoncore::matrix::seonarr<
        TN, 
        seoncore::enums::Major::Row,
        seoncore::policy::auto_select
    >();
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
        seoncore::policy::auto_select
    >();
};


};
