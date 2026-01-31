#pragma once

#include <cstddef>
#include <type_traits>
#include <seoncore/iterators/iter_row.hpp>

namespace seoncore::views
{

template <typename TN, bool IsConst>
class RowViewBase
{
public:
    using pointer = std::conditional_t<IsConst, const TN*, TN*>;
    using reference = std::conditional_t<IsConst, const TN&, TN&>;
    using value_type = TN;
    using iterator = seoncore::iterators::iter_row<TN, IsConst>;
    using size_type = std::size_t;

    explicit RowViewBase() {};

    RowViewBase(
            pointer data,
            size_type idx,
            size_type rows,
            size_type cols,
            size_type sr,
            size_type sc)
        : _data(data)
        , _idx(idx)
        , _rows(rows)
        , _cols(cols)
        , _sr(sr)
        , _sc(sc)
    {};

    iterator begin() const
    {
        return iterator(_data, _idx, _rows, _cols, _sr, _sc, 0);
    };

    iterator end() const
    {
        return iterator(_data, _idx, _rows, _cols, _sr, _sc, _cols);
    };

    size_type size() const noexcept
    {
        return _cols;
    };

    reference operator()(size_type j) noexcept
    {
        return _data[_idx * _sr + j * _sc];
    };

    reference operator[](size_type j) noexcept { return (*this)(j); };

private:
    pointer     _data;
    size_type   _idx;
    size_type   _rows;
    size_type   _cols;
    size_type   _sr;
    size_type   _sc;

}; // class RowViewBase<TN, IsConst>

template <typename TN>
using RowView = RowViewBase<TN, true>;

template <typename TN>
using MutableRowView = RowViewBase<TN, false>;

}; // namespace seoncore::views
