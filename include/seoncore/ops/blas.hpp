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
    return TN{0};
};

template <typename TN>
auto dot(
        const seoncore::views::MatrixLike<TN>& x, 
        const seoncore::views::MatrixLike<TN>& y
    ) -> TN
{
    return TN{0};
};

template <typename TN>
auto dot(
        const seoncore::views::MatrixLike<TN>& x, 
        const seoncore::views::VectorLike<TN>& y
    ) -> TN
{
    return TN{0};
};

template <typename TN>
auto dot(
        const seoncore::views::VectorLike<TN>& x, 
        const seoncore::views::MatrixLike<TN>& y
    ) -> TN
{
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
    //(A, B, alpha, C, beta);
    return seoncore::matrix::seonarr<
        TN, 
        seoncore::enums::Major::Row,
        seoncore::policy::auto_select
    >();
};


};
