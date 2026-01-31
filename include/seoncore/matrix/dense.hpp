#pragma once

#include <vector>
#include <seoncore/enums/major.hpp>
#include <seoncore/matrix/base.hpp>
#include <seoncore/views/row.hpp>
#include <seoncore/views/col.hpp>

namespace seoncore::matrix
{

template <typename TN>
class DenseMatrix : BaseMatrix<DenseMatrix<TN>, TN>
{
public:
    friend BaseMatrix<DenseMatrix, TN>;

    using size_type             = std::size_t;
    using value_type            = TN;
    using type                  = TN;
    using reference             = TN&;
    using const_ref             = const TN&;
    using pointer               = TN*;
    using const_ptr             = const TN*;
    using row_view              = seoncore::views::RowView<TN>;
    using mut_row_view          = seoncore::views::MutableRowView<TN>;
    using col_view              = seoncore::views::ColView<TN>;
    using mut_col_view          = seoncore::views::MutableColView<TN>;

    DenseMatrix() noexcept = default;
    ~DenseMatrix() noexcept = default;

    DenseMatrix(const DenseMatrix& other)
        : _data(other._data)
        , _rows(other._rows)
        , _cols(other._cols)
        , _sr(other._sr)
        , _sc(other._sc)
        , _major(other._major)
    {};

    DenseMatrix& operator=(const DenseMatrix& other)
    {
        if (this == &other) return *this;

        _data   = other._data; 
        _rows   = other._rows; 
        _cols   = other._cols; 
        _sr     = other._sr; 
        _sc     = other._sc;
        _major  = other._major;

        return *this;
    };

    DenseMatrix(DenseMatrix&& other) noexcept
        : _data(std::move(other._data))
        , _rows(other._rows)
        , _cols(other._cols)
        , _sr(other._sr)
        , _sc(other._sc)
        , _major(other._major)
    {
        _null_st_params(other);
    };

    DenseMatrix& operator=(DenseMatrix&& other) noexcept
    {
        if (this == &other) return *this;
        
        _data   = std::move(other._data);
        _rows   = other._rows;
        _cols   = other._cols;
        _sr     = other._sr;
        _sc     = other._sc;
        _major  = other._major;
        _null_st_params(other);
        
        return *this;
    };

    bool operator==(const DenseMatrix<TN>& other)
    {
        return _data    == other._data &&
               _rows    == other._rows &&
               _cols    == other._cols &&
               _sr      == other._sr   &&
               _sc      == other._sc   &&
               _major   == other._major;
    };

    bool operator!=(const DenseMatrix<TN>& other) { return !(*this == other); };

    DenseMatrix(
            const_ref begin, 
            const_ref end, 
            size_type rows, 
            size_type cols,
            seoncore::enums::Major major = seoncore::enums::Major::Row)
        : _data(begin, end)
        , _rows(rows)
        , _cols(cols)
        , _major(major)
    {
        _init_strides();
    };

    DenseMatrix(
            const std::vector<TN>& raw_data,
            size_type rows,
            size_type cols,
            seoncore::enums::Major major = seoncore::enums::Major::Row)
        : _data(raw_data)
        , _rows(rows)
        , _cols(cols)
        , _major(major)
    {
        assert(raw_data.size() == rows * cols);
        _init_strides(); 
    };

    DenseMatrix(
            size_type rows,
            size_type cols,
            seoncore::enums::Major major = seoncore::enums::Major::Row)
        : _data(std::vector<TN>(rows * cols))
        , _rows(rows)
        , _cols(cols)
        , _major(major)
    {
        _init_strides();
    };

    DenseMatrix(
            const std::vector<std::vector<TN>>& data,
            seoncore::enums::Major major = seoncore::enums::Major::Row)
        : _major(major)
    {
        assert(!data.empty());

        _rows = data.size();
        _cols = data[0].size();

        for (auto& row : data)
            for (auto& elem : row)
                _data.push_back(elem);

        _init_strides();
    };

    DenseMatrix(
            const std::initializer_list<TN>& raw_ilist, 
            size_type rows, 
            size_type cols,
            seoncore::enums::Major major = seoncore::enums::Major::Row)
        : _rows(rows)
        , _cols(cols)
        , _major(major)
    {
        assert(raw_ilist.size() == rows * cols);

        for (auto& elem : raw_ilist)
            _data.push_back(elem);

        _init_strides();
    };

    DenseMatrix(
            const std::initializer_list<std::initializer_list<TN>>& ilist,
            seoncore::enums::Major major = seoncore::enums::Major::Row)
        : _major(major)
    {
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
    std::vector<TN>         _data;
    size_type               _rows;
    size_type               _cols;
    size_type               _sr;
    size_type               _sc;
    seoncore::enums::Major  _major;

    void _init_strides() noexcept
    {
        if (_major == seoncore::enums::Major::Row)
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

    void _null_st_params(DenseMatrix& a) noexcept
    {
        a._rows = 0;
        a._cols = 0;
        a._sr   = 0;
        a._sc   = 0;
    };

    size_type rows_impl() const noexcept { return _rows; };
    size_type cols_impl() const noexcept { return _cols; };

    pointer data_impl() { return _data.data(); }; 
    const_ptr data_impl() const { return static_cast<const_ptr>(_data.data()); };

    seoncore::enums::Major& major_impl() { return _major; };
    const seoncore::enums::Major& major_impl() const { return _major; };

    reference at_impl(size_type i, size_type j) noexcept { return _data[i * _sr + j * _sc]; };
    const_ref at_impl(size_type i, size_type j) const noexcept { return _data[i * _sr + j * _sc]; };

    mut_row_view row_impl(size_type idx) noexcept
    {   
        return mut_row_view(_data.data(), idx, _rows, _cols, _sr, _sc);
    };

    row_view row_impl(size_type idx) const noexcept
    {
        return row_view(_data.data(), idx, _rows, _cols, _sr, _sc);
    };

    mut_col_view col_impl(size_type jdx) noexcept
    {   
        return mut_col_view(_data.data(), jdx, _cols, _cols, _sr, _sc);
    };

    col_view col_impl(size_type jdx) const noexcept
    {
        return col_view(_data.data(), jdx, _cols, _cols, _sr, _sc);
    };


}; // class DenseMatrix<TN>

}; // namespace seoncore::matrix
