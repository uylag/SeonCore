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

    DenseMatrix()
        : _rows(0)
        , _cols(0)
        , _sr(0)
        , _sc(0)
    {};

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

    reference at_impl(size_type i, size_type j) noexcept       { return _data[i * _sr + j * _sc]; };
    const_ref at_impl(size_type i, size_type j) const noexcept { return _data[i * _sr + j * _sc]; };

    
    row_view       get_row_impl(size_type i);
    const_row_view get_row_impl(size_type i) const;
    col_view       get_col_impl(size_type j);
    const_col_view get_col_impl(size_type j) const;

    void fill_impl(const TN& value);
    trans_view transpose_view_impl();
    const_trans_view transpose_view_impl() const;

    type        sum_impl()               const;
    type        norm_p_impl(size_type p) const;
    DenseMatrix abs_impl()               const;
    type        max_impl()               const;
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
