#pragma once

#include <cassert>
#include <memory>
#include <vector>
#include <seoncore/matrix/base_matrix.hpp>
#include <seoncore/views/vector_like.hpp>
#include <seoncore/views/matrix_like.hpp>
#include <seoncore/enums/major.hpp>
#include <seoncore/views/row_view.hpp>
#include <seoncore/views/col_view.hpp>
#include <seoncore/views/transposed_view.hpp>
#include <seoncore/enums/policy.hpp>

namespace seoncore::matrix
{

template <
        typename TN,
        seoncore::enums::Major _Major = seoncore::enums::Major::Row
    >
class DenseMatrix : public BaseMatrix<DenseMatrix<TN, _Major>, TN>
{
public:
    /**
     * @brief Owning dense matrix with fixed major order.
     *
     * Storage is contiguous, with strides derived from the major order.
     */
    friend BaseMatrix<DenseMatrix<TN, _Major>, TN>;

    using self                  = DenseMatrix<TN, _Major>;
    using size_type             = std::size_t; 
    using type                  = TN;
    using reference             = TN&;
    using const_ref             = const TN&;
    using pointer               = TN*;
    using matrix_like           = seoncore::views::MatrixLike<TN>;
    using vector_like           = seoncore::views::VectorLike<TN>;
    using major                 = seoncore::enums::Major;
    using row_view              = seoncore::views::RowView<TN>;
    using const_row_view        = seoncore::views::ConstRowView<TN>;
    using col_view              = seoncore::views::ColView<TN>;
    using const_col_view        = seoncore::views::ConstColView<TN>;
    using trans_view            = seoncore::views::TransposedView<TN>;
    using const_trans_view      = seoncore::views::ConstTransposedView<TN>;

    /**
     * @brief Construct an empty matrix.
     */
    DenseMatrix()
        : _rows(0)
        , _cols(0)
        , _sr(0)
        , _sc(0)
    {};

    /**
     * @brief Construct a matrix from flat data.
     * @param data Flat storage in logical order.
     * @param rows Logical number of rows.
     * @param cols Logical number of columns.
     */
    DenseMatrix(
            const std::vector<TN>& data,
            size_type rows,
            size_type cols)
        : _data(data)
        , _rows(rows)
        , _cols(cols)
    {
        assert(data.size() == rows * cols);
        
        if constexpr (_Major == seoncore::enums::Major::Row)
        {
            _sr = _cols;
            _sc = 1;
        }
        else
        {
            _sr = 1;
            _sc = _rows;
        };
    };

private:
    std::vector<TN> _data;
    size_type _rows;
    size_type _cols;
    size_type _sr; 
    size_type _sc;


    size_type rows_impl()       const noexcept { return _rows; };
    size_type cols_impl()       const noexcept { return _cols; };
    pointer   data_impl()             noexcept { return _data.data(); };
    const TN* data_impl()       const noexcept { return _data.data(); };
    size_type stride_row_impl() const noexcept { return _sr; };
    size_type stride_col_impl() const noexcept { return _sc; };

    /**
     * @brief Mutable element access by logical index.
     * @param i Row index.
     * @param j Column index.
     * @return Reference to element (i, j).
     */
    reference at_impl(size_type i, size_type j) noexcept       { return _data[i * _sr + j * _sc]; };
    /**
     * @brief Const element access by logical index.
     * @param i Row index.
     * @param j Column index.
     * @return Const reference to element (i, j).
     */
    const_ref at_impl(size_type i, size_type j) const noexcept { return _data[i * _sr + j * _sc]; };

    
    /**
     * @brief Get mutable row view.
     * @param i Row index.
     * @return Row view of row i.
     */
    row_view       get_row_impl(size_type i);
    /**
     * @brief Get const row view.
     * @param i Row index.
     * @return Const row view of row i.
     */
    const_row_view get_row_impl(size_type i) const;
    /**
     * @brief Get mutable column view.
     * @param j Column index.
     * @return Column view of column j.
     */
    col_view       get_col_impl(size_type j);
    /**
     * @brief Get const column view.
     * @param j Column index.
     * @return Const column view of column j.
     */
    const_col_view get_col_impl(size_type j) const;

    /**
     * @brief Fill all elements with a value.
     * @param value Value to assign.
     */
    void fill_impl(const TN& value);
    /**
     * @brief Get a mutable transposed view.
     * @return Transposed view.
     */
    trans_view transpose_view_impl();
    /**
     * @brief Get a const transposed view.
     * @return Const transposed view.
     */
    const_trans_view transpose_view_impl() const;

    /**
     * @brief Sum of all elements.
     * @return Sum value.
     */
    type        sum_impl()               const;
    /**
     * @brief p-norm of the matrix (implementation-defined).
     * @param p Norm order.
     * @return p-norm value.
     */
    type        norm_p_impl(size_type p) const;
    /**
     * @brief Element-wise absolute value.
     * @return New matrix with absolute values.
     */
    DenseMatrix abs_impl()               const;
    /**
     * @brief Maximum element value.
     * @return Maximum element.
     */
    type        max_impl()               const;
    /**
     * @brief Get a matrix-like view wrapper.
     * @return MatrixLike wrapper.
     */
    matrix_like get_view_impl()          const;

}; // class DenseMatrix<TN, _Major>

template <typename TN, seoncore::enums::Major _Major>
seoncore::views::RowView<TN> DenseMatrix<TN, _Major>::get_row_impl(std::size_t i)
{
    return seoncore::views::RowView(
        this->data(),
        i,
        this->cols(),
        this->stride_row(),
        this->stride_col());
};

template <typename TN, seoncore::enums::Major _Major>
seoncore::views::ConstRowView<TN> DenseMatrix<TN, _Major>::get_row_impl(std::size_t i) const
{
    return ConstRowView(
        this->data(),
        i,
        this->cols(),
        this->stride_row(),
        this->stride_col()); 
};

template <typename TN, seoncore::enums::Major _Major>
seoncore::views::ColView<TN> DenseMatrix<TN, _Major>::get_col_impl(std::size_t j)
{
    return seoncore::views::ColView(
        this->data(),
        j,
        this->rows(),
        this->cols(),
        this->stride_row(),
        this->stride_col());
};

template <typename TN, seoncore::enums::Major _Major>
seoncore::views::ConstColView<TN> DenseMatrix<TN, _Major>::get_col_impl(std::size_t j) const
{
    return seoncore::views::ConstColView(
        this->data(),
        j,
        this->rows(),
        this->cols(),
        this->stride_row(),
        this->stride_col()); 
};

template <typename TN, seoncore::enums::Major _Major>
void DenseMatrix<TN, _Major>::fill_impl(const TN& value)
{
    for (std::size_t i = 0; i < this->rows(); ++i)
        for (std::size_t j = 0; j < this->cols(); ++j)
            *this(i, j) = value;
};

}; // namespace seoncore::matrix
