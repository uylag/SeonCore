#pragma once

#include <seoncore/iterators/iter_row.hpp>

namespace seoncore::views
{

template <typename TN>
class RowView
{
public:
    /**
     * @brief Mutable view of a single matrix row.
     */
    using pointer = TN*;
    using size_type = std::size_t;
    using iterator = seoncore::iterators::iter_row<TN, false>;

    RowView() = default;
    /**
     * @brief Construct a row view.
     * @param data Base pointer to matrix storage.
     * @param idx Logical row index.
     * @param cols Logical number of columns.
     * @param sr Row stride.
     * @param sc Column stride.
     */
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

    /**
     * @brief Iterator to the first element in the row.
     * @return Row iterator at column 0.
     */
    iterator begin() const
    {
        return iterator(_data, _idx, _cols, _sr, _sc, 0);
    };

    /**
     * @brief Iterator past the last element in the row.
     * @return Row iterator at column count.
     */
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
    /**
     * @brief Read-only view of a single matrix row.
     */
    using pointer = const TN*;
    using size_type = std::size_t;
    using iterator = seoncore::iterators::iter_row<TN, true>;

    ConstRowView() = default;
    /**
     * @brief Construct a const row view.
     * @param data Base pointer to matrix storage.
     * @param idx Logical row index.
     * @param cols Logical number of columns.
     * @param sr Row stride.
     * @param sc Column stride.
     */
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

    /**
     * @brief Iterator to the first element in the row.
     * @return Const row iterator at column 0.
     */
    iterator begin() const
    {
        return iterator(_data, _idx, _cols, _sr, _sc, 0);
    };

    /**
     * @brief Iterator past the last element in the row.
     * @return Const row iterator at column count.
     */
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
