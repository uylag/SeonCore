#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <type_traits>

namespace seoncore::iterators
{

template <typename TN, bool IsConst>
class iter_col
{
public:
    using size_type             = std::size_t;
    using difference_type       = std::ptrdiff_t;
    using iterator_category     = std::random_access_iterator_tag;
    using value_type            = TN;
    using reference             = std::conditional_t<IsConst, const TN&, TN&>;
    using pointer               = std::conditional_t<IsConst, const TN*, TN*>;

    iter_col(
            pointer data,
            size_type col_idx,
            size_type rows,
            size_type cols,
            size_type sr,
            size_type sc,
            size_type idx_pos)
        : _data(data)
        , _col_idx(col_idx)
        , _rows(rows)
        , _cols(cols)
        , _sr(sr)
        , _sc(sc)
        , _idx_pos(idx_pos)
    {};

    reference operator*() const noexcept
    {
        return _data[_idx_pos * _sr + _col_idx * _sc];
    };

    pointer operator->() const noexcept
    {
        return std::addressof(operator*());
    };

    iter_col& operator++() noexcept
    {
        ++_idx_pos;
        return *this;
    };

    iter_col operator++(int) noexcept
    {
        iter_col tmp;
        ++_idx_pos;
        return tmp;
    };

    iter_col& operator--() noexcept
    {
        --_idx_pos;
        return *this;
    };

    iter_col operator--(int) noexcept
    {
        iter_col tmp;
        --_idx_pos;
        return tmp;
    };

        iter_col& operator+=(difference_type n) noexcept
    {
        _idx_pos += static_cast<size_type>(n);
        return *this;
    };

    iter_col& operator-=(difference_type n) noexcept
    {
        _idx_pos -= static_cast<size_type>(n);
        return *this;
    };

    iter_col operator+(difference_type n) const noexcept
    {
        iter_col tmp = *this;
        tmp += n;
        return tmp;
    };

    iter_col operator-(difference_type n) const noexcept
    {
        iter_col tmp = *this;
        tmp -= n;
        return tmp;
    };

    difference_type operator-(const iter_col& other) const noexcept
    {
        return static_cast<difference_type>(_idx_pos) - static_cast<difference_type>(other._idx_pos);
    };

    reference operator[](difference_type n) const noexcept
    {
        return *(*this + n);
    };

    bool operator==(const iter_col& other) const noexcept
    {
        return _data    == other._data
            && _col_idx == other._col_idx
            && _rows    == other._rows
            && _cols    == other._cols
            && _sr      == other._sr
            && _sc      == other._sc
            && _idx_pos == other._idx_pos;
    };

    bool operator!=(const iter_col& other) const noexcept
    {
        return !(*this == other);
    };

private:
    pointer _data;
    size_type _col_idx;
    size_type _rows;
    size_type _cols;
    size_type _sr;
    size_type _sc;
    size_type _idx_pos;
};

};

