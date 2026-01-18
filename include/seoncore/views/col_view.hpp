#pragma once

#include <seoncore/iterators/iter_col.hpp>

namespace seoncore::views
{

template <typename TN>
class ColView
{
public:
    /**
     * @brief Mutable view of a single matrix column.
     */
    using pointer = TN*;
    using size_type = std::size_t;
    using iterator = seoncore::iterators::iter_col<TN, false>;

    ColView() = default;
    /**
     * @brief Construct a column view.
     * @param data Base pointer to matrix storage.
     * @param idx Logical column index.
     * @param rows Logical number of rows.
     * @param cols Logical number of columns.
     * @param sr Row stride.
     * @param sc Column stride.
     */
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

    /**
     * @brief Iterator to the first element in the column.
     * @return Column iterator at row 0.
     */
    iterator begin() const
    {
        return iterator(_data, _idx, _rows, _cols, _sr, _sc, 0);
    };

    /**
     * @brief Iterator past the last element in the column.
     * @return Column iterator at row count.
     */
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
    /**
     * @brief Read-only view of a single matrix column.
     */
    using pointer = const TN*;
    using size_type = std::size_t;
    using iterator = seoncore::iterators::iter_col<TN, true>;

    ConstColView() = default;
    /**
     * @brief Construct a const column view.
     * @param data Base pointer to matrix storage.
     * @param idx Logical column index.
     * @param rows Logical number of rows.
     * @param cols Logical number of columns.
     * @param sr Row stride.
     * @param sc Column stride.
     */
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

    /**
     * @brief Iterator to the first element in the column.
     * @return Const column iterator at row 0.
     */
    iterator begin() const
    {
        return iterator(_data, _idx, _rows, _cols, _sr, _sc, 0);
    };

    /**
     * @brief Iterator past the last element in the column.
     * @return Const column iterator at row count.
     */
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
