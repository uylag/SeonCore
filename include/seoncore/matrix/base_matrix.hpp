#pragma once

#include <cstddef>
#include <utility>
#include <seoncore/iterators/iter_dense.hpp>
#include <seoncore/iterators/iter_sparse.hpp>
#include <seoncore/views/transposed_view.hpp>
#include <seoncore/views/row_view.hpp>
#include <seoncore/views/col_view.hpp>
#include <seoncore/views/matrix_like.hpp>
#include <seoncore/views/vector_like.hpp>
#include <seoncore/ops/blas.hpp>

namespace seoncore::matrix
{

template <
    typename TN,
    seoncore::enums::Major _Major,
    class _Policy
>
class seonarr;

template <class Derived, class TN>
struct BaseMatrix
{
    using D                 = Derived;
    using type              = TN;
    using reference         = TN&;
    using const_ref         = const TN&;
    using pointer           = TN*;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    using row_view          = seoncore::views::RowView<TN>;
    using col_view          = seoncore::views::ColView<TN>;
    using const_row_view    = seoncore::views::ConstRowView<TN>;
    using const_col_view    = seoncore::views::ConstColView<TN>;
    using trans_view        = seoncore::views::TransposedView<TN>;
    using const_trans_view  = seoncore::views::ConstTransposedView<TN>;
    using matrix_like       = seoncore::views::MatrixLike<TN>;
    using vector_like       = seoncore::views::VectorLike<TN>;
    
    D&       derived()       { return static_cast<D&>(*this); }
    D const& derived() const { return static_cast<D const&>(*this); }

    size_type rows() const 
    {
        return derived().rows_impl();
    };

    size_type cols() const
    {
        return derived().cols_impl();
    };

    TN& at(size_type i, size_type j)
    {
        return derived().at_impl(i, j);
    };

    const TN& at(size_type i, size_type j) const
    {
        return derived().at_impl(i, j);
    };

    pointer data()
    {
        return derived().data_impl();
    };

    const TN* data() const
    {
        return derived().data_impl();
    };

    size_type stride_row() const
    {
        return derived().stride_row_impl();
    };

    size_type stride_col() const
    {
        return derived().stride_col_impl();
    };

    std::pair<size_type, size_type> shape() const
    {
        return { rows(), cols() };
    };

    size_type size() const
    {
        return rows() * cols();
    };

    reference operator()(size_type i, size_type j)
    {
        return derived().at_impl(i, j);
    };

    const_ref operator()(size_type i, size_type j) const
    {
        return derived().at_impl(i, j);
    };

    row_view row(size_type i)
    {
        return derived().get_row_impl(i);
    };

    const_row_view row(size_type i) const
    {
        return derived().get_row_impl(i);
    };

    col_view col(size_type j)
    {
        return derived().get_col_impl(j);
    };

    const_col_view col(size_type j) const
    {
        return derived().get_col_impl(j);
    };

    void fill(const TN& value)
    {
        derived().fill_impl(value);
    };

    //D transpose() const
    //{
    //   return derived().transpose_impl();
    //};

    [[nodiscard]]
    trans_view transpose_view()
    {
        return derived().transpose_view_impl();
    };

    [[nodiscard]]
    const_trans_view transpose_view() const
    {
        return derived().transpose_view_impl();
    };

    [[nodiscard]]
    type sum() const
    {
        return derived().sum_impl();
    };

    type norm_p(size_type p) const
    {
        return derived().norm_p_impl(p);
    };

    [[nodiscard]]
    D abs() const
    {
        return derived().abs_impl();
    };

    type max() const 
    {
        return derived().max_impl();
    };

    type max_abs() const
    {
        auto tmp = abs();
        return tmp.max();
    };

    matrix_like get_view() const
    {
        return derived().get_view_impl();
    };

    type dot(const vector_like& other) const
    {
        return seoncore
               ::ops
               ::dot(get_view(), other);
    };

    type dot(const matrix_like& other) const
    {
        return seoncore
               ::ops
               ::dot(get_view(), other);
    };

    auto gemv(
        const vector_like& x,
        type alpha = 1,
        const vector_like& y =
            seoncore::views::like::VectorLikeDefault<TN>(),
        type beta = 0
    ) const -> seoncore::matrix::seonarr<
                    TN,
                    seoncore::enums::Major::Row,
                    seoncore::policy::auto_select
                >
    {
        return seoncore
               ::ops
               ::gemv(get_view(), x, alpha, y, beta);
    };

    auto gemm(
            const matrix_like& B,
            type alpha = 1,
            const matrix_like& C =
                seoncore::views::like::MatrixLikeDefault<TN>(),
            type beta = 0
        ) const -> seoncore::matrix::seonarr<
                        TN,
                        seoncore::enums::Major::Row,
                        seoncore::policy::auto_select
                    >
    {
        return seoncore
               ::ops
               ::gemm(get_view(), B, alpha, C, beta);
    };

};

} // namespace seoncore::matrix
