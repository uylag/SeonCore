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
    using value_type            = TN;
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

    ~DenseMatrix()
    {
        _data.clear();
        _rows   = 0;
        _cols   = 0;
        _sr     = 0;
        _sc     = 0;
    };

    DenseMatrix(const DenseMatrix& other)
        : _data(other._data)
        , _rows(other._rows)
        , _cols(other._cols)
        , _sr(other._sr)
        , _sc(other._sc)
    {};

    DenseMatrix& operator=(const DenseMatrix& other)
    {
        if (*this != other)
        {
            _data = other._data; 
            _rows = other._rows; 
            _cols = other._cols; 
            _sr   = other._sr; 
            _sc   = other._sc; 
        };

        return *this;
    };

    DenseMatrix(DenseMatrix&& other) noexcept
        : _data(std::move(other._data))
        , _rows(other._rows)
        , _cols(other._cols)
        , _sr(other._sr)
        , _sc(other._sc)
    {
        _null_st_params(other);
    };

    DenseMatrix& operator=(DenseMatrix&& other) noexcept
    {
        if (*this != other)
        {
            _data   = std::move(other._data);
            _rows   = other._rows;
            _cols   = other._cols;
            _sr     = other._sr;
            _sc     = other._sc;
            _null_st_params(other);
        };

        return *this;
    };

    DenseMatrix(const_ref begin, const_ref end, size_type rows, size_type cols)
        : _data(begin, end)
        , _rows(rows)
        , _cols(cols)
    {
        _init_strides();
    };

    /**
     * @brief Construct a matrix from flat data.
     * @param data Flat storage in logical order.
     * @param rows Logical number of rows.
     * @param cols Logical number of columns.
     */
    DenseMatrix(
            const std::vector<TN>& raw_data,
            size_type rows,
            size_type cols)
        : _data(raw_data)
        , _rows(rows)
        , _cols(cols)
    {
        assert(raw_data.size() == rows * cols);
        _init_strides(); 
    };

    DenseMatrix(const std::vector<std::vector<TN>>& data)
    {
        assert(!data.empty());

        _rows = data.size();
        _cols = data[0].size();

        for (auto& row : data)
            for (auto& elem : row)
                _data.push_back(elem);

        _init_strides();
    };

    DenseMatrix(const std::initializer_list<TN>& raw_ilist, size_type rows, size_type cols)
        : _rows(rows)
        , _cols(cols)
    {
        assert(raw_ilist.size() == rows * cols);

        for (auto& elem : raw_ilist)
            _data.push_back(elem);

        _init_strides();
    };

    DenseMatrix(const std::initializer_list<std::initializer_list<TN>>& ilist)
    {
        // Initializing rows and cols
        _rows = ilist.size();

        for (auto& row : ilist)
        {
            _cols = row.size();
            break;
        };

        for (auto& row : ilist)
        {
            assert(_cols == row.size());

            for (auto& elem : row)
                _data.push_back(elem);
        };

        _init_strides();
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

    /**
     * @brief Row stride.
     * @return Offset between consecutive rows.
     */
    size_type stride_row() const
    {
        return _sr;
    };

    /**
     * @brief Column stride.
     * @return Offset between consecutive columns.
     */
    size_type stride_col() const
    {
        return _sc;
    };


    void _init_strides() noexcept
    {
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

    // Nulling size_type parameters
    void _null_st_params(DenseMatrix& a) noexcept
    {
        a._rows = 0;
        a._cols = 0;
        a._sr   = 0;
        a._sc   = 0;
    };

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

template <typename TN, seoncore::enums::Major _Major>
seoncore::views::MatrixLike<TN> DenseMatrix<TN, _Major>::get_view_impl() const
{
    return seoncore::views::MatrixLike<TN>(
                this->data(),
                this->rows(),
                this->cols(),
                this->stride_row(),
                this->stride_col()
            );
};

}; // namespace seoncore::matrix
