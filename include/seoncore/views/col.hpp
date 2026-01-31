#pragma once

#include <cstddef>
#include <type_traits>
#include <seoncore/iterators/iter_col.hpp>

namespace seoncore::views
{

template <typename TN, bool IsConst>
class ColViewBase
{
public:
    using pointer = std::conditional_t<IsConst, const TN*, TN*>;
    using reference = std::conditional_t<IsConst, const TN&, TN&>;
    using value_type = TN;
    using iterator = seoncore::iterators::iter_col<TN, IsConst>;
    using size_type = std::size_t;

    explicit ColViewBase() {};

    ColViewBase(
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
        return iterator(_data, _idx, _rows, _cols, _sr, _sc, _rows);
    };

    size_type size() const noexcept
    {
        return _rows;
    };

    reference operator()(size_type i) noexcept
    {
        return _data[i * _sr + _idx * _sc];
    };

    reference operator[](size_type i) noexcept { return (*this)(i); };

private:
    pointer     _data   = nullptr;
    size_type   _idx    = 0;
    size_type   _rows   = 0;
    size_type   _cols   = 0;
    size_type   _sr     = 0;
    size_type   _sc     = 0;

}; // class ColViewBase<TN, IsConst>

template <typename TN>
using ColView = ColViewBase<TN, true>;

template <typename TN>
using MutableColView = ColViewBase<TN, false>;

}; // namespace seoncore::views

