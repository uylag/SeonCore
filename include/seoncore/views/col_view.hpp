#pragma once

#include <seoncore/iterators/iter_col.hpp>

namespace seoncore::views
{

template <typename TN>
class ColView
{
public:
    using pointer = TN*;
    using size_type = std::size_t;
    using iterator = seoncore::iterators::iter_col<TN, false>;

    ColView() = default;
    ColView(
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

private:
    pointer _data;
    size_type _idx;
    size_type _rows;
    size_type _cols;
    size_type _sr;
    size_type _sc;

}; // class ColView<TN>

template <typename TN>
class ConstColView
{
public:
    using pointer = const TN*;
    using size_type = std::size_t;
    using iterator = seoncore::iterators::iter_col<TN, true>;

    ConstColView() = default;
    ConstColView(
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

private:
    pointer _data;
    size_type _idx;
    size_type _rows;
    size_type _cols;
    size_type _sr;
    size_type _sc;

}; // class ConstColView<TN>

}; // namespace seoncore::views
