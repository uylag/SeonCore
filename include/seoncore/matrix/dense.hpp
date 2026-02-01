#pragma once

#include <vector>
#include <seoncore/enums/major.hpp>
#include <seoncore/matrix/base.hpp>
#include <seoncore/views/vec.hpp>
#include <seoncore/views/transposed.hpp>

namespace seoncore::matrix
{

template <typename TN>
class DenseMatrix : public BaseMatrix<DenseMatrix<TN>, TN>
{
public:
    friend struct BaseMatrix<DenseMatrix<TN>, TN>;

    using self                  = DenseMatrix<TN>;
    using size_type             = std::size_t;
    using value_type            = TN;
    using type                  = TN;
    using reference             = TN&;
    using const_ref             = const TN&;
    using pointer               = TN*;
    using const_ptr             = const TN*;
    using vec_view              = seoncore::views::VectorView<TN>;
    using mut_vec_view          = seoncore::views::MutableVectorView<TN>;

    constexpr DenseMatrix() noexcept = default;
    constexpr ~DenseMatrix() noexcept = default;

    constexpr DenseMatrix(const DenseMatrix& other) noexcept
        : _data(other._data)
        , _rows(other._rows)
        , _cols(other._cols)
        , _sr(other._sr)
        , _sc(other._sc)
        , _major(other._major)
    {};

    constexpr DenseMatrix& operator=(const DenseMatrix& other) noexcept
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

    constexpr DenseMatrix(DenseMatrix&& other) noexcept
        : _data(std::move(other._data))
        , _rows(other._rows)
        , _cols(other._cols)
        , _sr(other._sr)
        , _sc(other._sc)
        , _major(other._major)
    {
        _null_st_params(other);
    };

    constexpr DenseMatrix& operator=(DenseMatrix&& other) noexcept
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

    constexpr bool operator==(const DenseMatrix<TN>& other) noexcept
    {
        return _data    == other._data &&
               _rows    == other._rows &&
               _cols    == other._cols &&
               _sr      == other._sr   &&
               _sc      == other._sc   &&
               _major   == other._major;
    };

    constexpr bool operator!=(const DenseMatrix<TN>& other) noexcept { return !(*this == other); };

    constexpr DenseMatrix(
            const_ref begin, 
            const_ref end, 
            size_type rows, 
            size_type cols,
            seoncore::enums::Major major = seoncore::enums::Major::Row) noexcept
        : _data(begin, end)
        , _rows(rows)
        , _cols(cols)
        , _major(major)
    {
        _init_strides();
    };

    constexpr DenseMatrix(
            const std::vector<TN>& raw_data,
            size_type rows,
            size_type cols,
            seoncore::enums::Major major = seoncore::enums::Major::Row) noexcept
        : _data(raw_data)
        , _rows(rows)
        , _cols(cols)
        , _major(major)
    {
        assert(raw_data.size() == rows * cols);
        _init_strides(); 
    };

    constexpr DenseMatrix(
            size_type rows,
            size_type cols,
            seoncore::enums::Major major = seoncore::enums::Major::Row) noexcept
        : _data(std::vector<TN>(rows * cols))
        , _rows(rows)
        , _cols(cols)
        , _major(major)
    {
        _init_strides();
    };

    constexpr DenseMatrix(
            const std::vector<std::vector<TN>>& data,
            seoncore::enums::Major major = seoncore::enums::Major::Row) noexcept
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

    constexpr DenseMatrix(
            const std::initializer_list<TN>& raw_ilist, 
            size_type rows, 
            size_type cols,
            seoncore::enums::Major major = seoncore::enums::Major::Row) noexcept
        : _rows(rows)
        , _cols(cols)
        , _major(major)
    {
        assert(raw_ilist.size() == rows * cols);

        for (auto& elem : raw_ilist)
            _data.push_back(elem);

        _init_strides();
    };

    constexpr DenseMatrix(
            const std::initializer_list<std::initializer_list<TN>>& ilist,
            seoncore::enums::Major major = seoncore::enums::Major::Row) noexcept
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

    constexpr void _init_strides() noexcept
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

    constexpr void recompute_strides_impl() noexcept
    {
        _init_strides();
    };

    constexpr void _null_st_params(DenseMatrix& a) noexcept
    {
        a._rows = 0;
        a._cols = 0;
        a._sr   = 0;
        a._sc   = 0;
    };

    constexpr size_type rows_impl() const noexcept { return _rows; };
    constexpr size_type cols_impl() const noexcept { return _cols; };

    constexpr pointer data_impl() { return _data.data(); }; 
    constexpr const_ptr data_impl() const { return static_cast<const_ptr>(_data.data()); };

    constexpr seoncore::enums::Major& major_impl() { return _major; };
    constexpr const seoncore::enums::Major& major_impl() const { return _major; };

    constexpr reference at_impl(size_type i, size_type j) noexcept { return _data[i * _sr + j * _sc]; };
    constexpr const_ref at_impl(size_type i, size_type j) const noexcept { return _data[i * _sr + j * _sc]; };

    constexpr mut_vec_view row_impl(size_type i) noexcept
    {
        return mut_vec_view(_data.data() + i * _sr, _cols, _sc);
    };

    constexpr vec_view row_impl(size_type i) const noexcept
    {
        return vec_view(_data.data() + i * _sr, _cols, _sc);
    };

    constexpr mut_vec_view col_impl(size_type j) noexcept
    {
        return mut_vec_view(_data.data() + j * _sc, _rows, _sr);
    };

    constexpr vec_view col_impl(size_type j) const noexcept
    {   
        return vec_view(_data.data() + j * _sc, _rows, _sr);
    };

    constexpr mut_vec_view flatten_impl() noexcept
    {
        return mut_vec_view(_data.data(), _rows * _cols, 1);
    };

    constexpr vec_view flatten_impl() const noexcept
    {
        return vec_view(_data.data(), _rows * _cols, 1);
    };

    constexpr seoncore::views::MutableTransposedView<self>
    transposed_impl() noexcept { return seoncore::views::MutableTransposedView<self>(*this); };

    constexpr seoncore::views::TransposedView<self>
    transposed_impl() const noexcept { return seoncore::views::TransposedView<self>(*this); };

}; // class DenseMatrix<TN>

}; // namespace seoncore::matrix

#include <seoncore/ops/dense_ops.hpp>
