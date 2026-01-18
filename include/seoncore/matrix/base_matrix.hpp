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
    /**
     * @brief CRTP base providing matrix API over a derived type.
     */
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
    
    /**
     * @brief Mutable reference to the derived implementation.
     * @return Reference to the derived object.
     */
    D&       derived()       { return static_cast<D&>(*this); }
    /**
     * @brief Const reference to the derived implementation.
     * @return Const reference to the derived object.
     */
    D const& derived() const { return static_cast<D const&>(*this); }

    /**
     * @brief Get logical row count.
     * @return Number of rows.
     */
    size_type rows() const 
    {
        return derived().rows_impl();
    };

    /**
     * @brief Get logical column count.
     * @return Number of columns.
     */
    size_type cols() const
    {
        return derived().cols_impl();
    };

    /**
     * @brief Mutable element access by index.
     * @param i Row index.
     * @param j Column index.
     * @return Reference to element (i, j).
     */
    TN& at(size_type i, size_type j)
    {
        return derived().at_impl(i, j);
    };

    /**
     * @brief Const element access by index.
     * @param i Row index.
     * @param j Column index.
     * @return Const reference to element (i, j).
     */
    const TN& at(size_type i, size_type j) const
    {
        return derived().at_impl(i, j);
    };

    /**
     * @brief Mutable pointer to underlying data.
     * @return Pointer to contiguous storage.
     */
    pointer data()
    {
        return derived().data_impl();
    };

    /**
     * @brief Const pointer to underlying data.
     * @return Const pointer to contiguous storage.
     */
    const TN* data() const
    {
        return derived().data_impl();
    };

    /**
     * @brief Row stride.
     * @return Offset between consecutive rows.
     */
    size_type stride_row() const
    {
        return derived().stride_row_impl();
    };

    /**
     * @brief Column stride.
     * @return Offset between consecutive columns.
     */
    size_type stride_col() const
    {
        return derived().stride_col_impl();
    };

    /**
     * @brief Matrix shape.
     * @return Pair of (rows, cols).
     */
    std::pair<size_type, size_type> shape() const
    {
        return { rows(), cols() };
    };

    /**
     * @brief Matrix size (rows * cols).
     * @return Total element count.
     */
    size_type size() const
    {
        return rows() * cols();
    };

    /**
     * @brief Mutable element access operator.
     * @param i Row index.
     * @param j Column index.
     * @return Reference to element (i, j).
     */
    reference operator()(size_type i, size_type j)
    {
        return derived().at_impl(i, j);
    };

    /**
     * @brief Const element access operator.
     * @param i Row index.
     * @param j Column index.
     * @return Const reference to element (i, j).
     */
    const_ref operator()(size_type i, size_type j) const
    {
        return derived().at_impl(i, j);
    };

    /**
     * @brief Get a mutable row view.
     * @param i Row index.
     * @return Row view of row i.
     */
    row_view row(size_type i)
    {
        return derived().get_row_impl(i);
    };

    /**
     * @brief Get a const row view.
     * @param i Row index.
     * @return Const row view of row i.
     */
    const_row_view row(size_type i) const
    {
        return derived().get_row_impl(i);
    };

    /**
     * @brief Get a mutable column view.
     * @param j Column index.
     * @return Column view of column j.
     */
    col_view col(size_type j)
    {
        return derived().get_col_impl(j);
    };

    /**
     * @brief Get a const column view.
     * @param j Column index.
     * @return Const column view of column j.
     */
    const_col_view col(size_type j) const
    {
        return derived().get_col_impl(j);
    };

    /**
     * @brief Fill all elements with a value.
     * @param value Value to assign to every element.
     */
    void fill(const TN& value)
    {
        derived().fill_impl(value);
    };

    //D transpose() const
    //{
    //   return derived().transpose_impl();
    //};

    [[nodiscard]]
    /**
     * @brief Get a mutable transposed view.
     * @return Transposed view.
     */
    trans_view transpose_view()
    {
        return derived().transpose_view_impl();
    };

    [[nodiscard]]
    /**
     * @brief Get a const transposed view.
     * @return Const transposed view.
     */
    const_trans_view transpose_view() const
    {
        return derived().transpose_view_impl();
    };

    [[nodiscard]]
    /**
     * @brief Sum of all elements.
     * @return Sum of elements.
     */
    type sum() const
    {
        return derived().sum_impl();
    };

    /**
     * @brief p-norm of the matrix (implementation-defined).
     * @param p Norm order.
     * @return p-norm value.
     */
    type norm_p(size_type p) const
    {
        return derived().norm_p_impl(p);
    };

    [[nodiscard]]
    /**
     * @brief Element-wise absolute value.
     * @return New matrix with absolute values.
     */
    D abs() const
    {
        return derived().abs_impl();
    };

    /**
     * @brief Maximum element value.
     * @return Maximum element.
     */
    type max() const 
    {
        return derived().max_impl();
    };

    /**
     * @brief Maximum absolute element value.
     * @return Maximum absolute element.
     */
    type max_abs() const
    {
        auto tmp = abs();
        return tmp.max();
    };

    /**
     * @brief Get a matrix-like view wrapper.
     * @return MatrixLike wrapper.
     */
    matrix_like get_view() const
    {
        return derived().get_view_impl();
    };

    /**
     * @brief Dot product with a vector-like object.
     * @param other Vector-like operand.
     * @return Dot product result.
     */
    type dot(const vector_like& other) const
    {
        return seoncore
               ::ops
               ::dot(get_view(), other);
    };

    /**
     * @brief Dot product with a matrix-like object.
     * @param other Matrix-like operand.
     * @return Dot product result.
     */
    type dot(const matrix_like& other) const
    {
        return seoncore
               ::ops
               ::dot(get_view(), other);
    };

    /**
     * @brief General matrix-vector product.
     * @param x Input vector.
     * @param alpha Scalar multiplier for A*x.
     * @param y Optional vector to combine with.
     * @param beta Scalar multiplier for y.
     * @return Result vector in a seonarr container.
     */
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

    /**
     * @brief General matrix-matrix product.
     * @param B Right-hand matrix.
     * @param alpha Scalar multiplier for A*B.
     * @param C Optional matrix to combine with.
     * @param beta Scalar multiplier for C.
     * @return Result matrix in a seonarr container.
     */
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
