#pragma once

#include <seoncore/iterators/iter_row.hpp>

namespace seoncore::views
{

template <typename TN>
class RowView
{
public:
    using pointer = TN*;
    using size_type = std::size_t;
    using iterator = seoncore::iterators::iter_row<TN, false>;

    RowView() = default;
    RowView(
            pointer data,
            size_type idx,
            size_type cols,
            size_type sr,
            size_type sc)
        : _data(data)
        , _idx(idx)
        , _cols(cols)
        , _sr(sr)
        , _sc(sc)
    {};

    iterator begin() const
    {
        return iterator(_data, _idx, _cols, _sr, _sc, 0);
    };

    iterator end() const
    {
        return iterator(_data, _idx, _cols, _sr, _sc, _cols);
    };

private:
    pointer _data;
    size_type _idx;
    size_type _cols;
    size_type _sr;
    size_type _sc;

}; // class RowView<TN>

template <typename TN>
class ConstRowView
{
public:
    using pointer = const TN*;
    using size_type = std::size_t;
    using iterator = seoncore::iterators::iter_row<TN, true>;

    ConstRowView() = default;
    ConstRowView(
            pointer data,
            size_type idx,
            size_type cols,
            size_type sr,
            size_type sc)
        : _data(data)
        , _idx(idx)
        , _cols(cols)
        , _sr(sr)
        , _sc(sc)
    {};

    iterator begin() const
    {
        return iterator(_data, _idx, _cols, _sr, _sc, 0);
    };

    iterator end() const
    {
        return iterator(_data, _idx, _cols, _sr, _sc, _cols);
    };

private:
    const TN* _data;
    size_type _idx;
    size_type _cols;
    size_type _sr;
    size_type _sc;

}; // class ConstRowView<TN>

}; // namespace seoncore::views
