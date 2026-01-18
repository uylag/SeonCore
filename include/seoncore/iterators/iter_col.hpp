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
    /**
     * @brief Column iterator over a dense matrix buffer.
     *
     * Iterates a single logical column with explicit strides.
     */
    using size_type         = std::size_t;
    using iterator_category = std::forward_iterator_tag;
    using value_type        = TN;
    using difference_type   = std::ptrdiff_t;
    using pointer           = std::conditional_t<IsConst, const TN*, TN*>;
    using reference         = std::conditional_t<IsConst, const TN&, TN&>;

    /**
     * @brief Construct a column iterator at a given row position.
     * @param data Base pointer to matrix storage.
     * @param col_idx Logical column index to iterate.
     * @param rows Logical number of rows in the matrix.
     * @param cols Logical number of columns in the matrix.
     * @param sr Row stride (offset between consecutive rows).
     * @param sc Column stride (offset between consecutive columns).
     * @param idx_pos Current row position within the column.
     */
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
      
    /**
     * @brief Dereference the current element.
     * @return Reference to the current element in the column.
     */
    reference operator*() const noexcept
    {
        return _data[_idx_pos * _sr + _col_idx * _sc];
    };

    /**
     * @brief Arrow access to the current element.
     * @return Pointer to the current element in the column.
     */
    pointer operator->() const noexcept
    {
        return std::addressof(operator*());
    };

    /**
     * @brief Pre-increment to the next row.
     * @return Reference to this iterator.
     */
    iter_col& operator++() noexcept
    {
        ++_idx_pos;
        return *this;
    };

    /**
     * @brief Post-increment to the next row.
     * @return Iterator snapshot before increment.
     */
    iter_col operator++(int) noexcept
    {
        iter_col tmp = *this;
        ++_idx_pos;
        return tmp;
    };

    /**
     * @brief Equality comparison.
     * @param other Iterator to compare against.
     * @return True when all iterator state matches.
     */
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
   
    /**
     * @brief Inequality comparison.
     * @param other Iterator to compare against.
     * @return True when iterator state differs.
     */
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

}; // class iter_col<TN>

}; // namespace seoncore::iterators
