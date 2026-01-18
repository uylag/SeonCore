#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <type_traits>

namespace seoncore::iterators
{

template <typename TN, bool IsConst>
class iter_row
{
public:
    /**
     * @brief Row iterator over a dense matrix buffer.
     *
     * Iterates a single logical row with explicit strides.
     */
    using size_type         = std::size_t;
    using iterator_category = std::forward_iterator_tag;
    using value_type        = TN;
    using difference_type   = std::ptrdiff_t;
    using pointer           = std::conditional_t<IsConst, const TN*, TN*>;
    using reference         = std::conditional_t<IsConst, const TN&, TN&>;

    /**
     * @brief Construct a row iterator at a given column position.
     * @param data Base pointer to matrix storage.
     * @param row_idx Logical row index to iterate.
     * @param cols Logical number of columns in the matrix.
     * @param sr Row stride (offset between consecutive rows).
     * @param sc Column stride (offset between consecutive columns).
     * @param idx_pos Current column position within the row.
     */
    iter_row(
            pointer data,
            size_type row_idx,
            size_type cols,
            size_type sr,
            size_type sc,
            size_type idx_pos)
        : _data(data)
        , _row_idx(row_idx)
        , _cols(cols)
        , _sr(sr)
        , _sc(sc)
        , _idx_pos(idx_pos)
    {};
      
    /**
     * @brief Dereference the current element.
     * @return Reference to the current element in the row.
     */
    reference operator*() const noexcept
    {
        return _data[_row_idx * _sr + _idx_pos * _sc];
    };

    /**
     * @brief Arrow access to the current element.
     * @return Pointer to the current element in the row.
     */
    pointer operator->() const noexcept
    {
        return std::addressof(operator*());
    };

    /**
     * @brief Pre-increment to the next column.
     * @return Reference to this iterator.
     */
    iter_row& operator++() noexcept
    {
        ++_idx_pos;
        return *this;
    };

    /**
     * @brief Post-increment to the next column.
     * @return Iterator snapshot before increment.
     */
    iter_row operator++(int) noexcept
    {
        iter_row tmp = *this;
        ++_idx_pos;
        return tmp;
    };

    /**
     * @brief Equality comparison.
     * @param other Iterator to compare against.
     * @return True when all iterator state matches.
     */
    bool operator==(const iter_row& other) const noexcept
    {
        return _data    == other._data
            && _row_idx == other._row_idx
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
    bool operator!=(const iter_row& other) const noexcept
    {
        return !(*this == other);
    };

private:
    pointer _data;
    size_type _row_idx;
    size_type _cols;
    size_type _sr;
    size_type _sc;
    size_type _idx_pos;
};

}; // namespace seoncore::iterators
