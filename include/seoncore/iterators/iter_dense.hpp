#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <utility>
#include <seoncore/enums/major.hpp>

namespace seoncore::iterators
{

template <typename TN>
class iter_dense
{
public:
    /**
     * @brief Dense matrix iterator supporting row-major or column-major traversal.
     *
     * Iterates logical elements while honoring explicit strides.
     */
    using size_type         = std::size_t;
    using iterator_category = std::forward_iterator_tag;
    using value_type        = TN;
    using difference_type   = std::ptrdiff_t;
    using pointer           = TN*;
    using reference         = TN&;
    using Major             = seoncore::enums::Major;

    /**
     * @brief Construct an iterator over a dense buffer.
     * @param data Base pointer to matrix storage.
     * @param rows Logical number of rows.
     * @param cols Logical number of columns.
     * @param sr Row stride (offset between consecutive rows).
     * @param sc Column stride (offset between consecutive columns).
     * @param major Logical traversal order (row-major or column-major).
     * @param idx Linear traversal index.
     */
    iter_dense(
            pointer data, 
            size_type rows,
            size_type cols,
            size_type sr,
            size_type sc,
            Major major,
            size_type idx)
        : _data(data)
        , _rows(rows)
        , _cols(cols)
        , _sr(sr)
        , _sc(sc)
        , _idx(idx)
        , _major(major)
    {};

    /**
     * @brief Dereference the current element.
     * @return Reference to the current logical element.
     */
    reference operator*() const noexcept
    {
        auto [i, j] = _logical_position();
        return _data[_phys_idx(i, j)];
    };

    /**
     * @brief Arrow access to the current element.
     * @return Pointer to the current element.
     */
    pointer operator->() const noexcept
    {
        return std::addressof(operator*());
    };

    /**
     * @brief Pre-increment to the next logical element.
     * @return Reference to this iterator.
     */
    iter_dense& operator++() noexcept
    {
        ++_idx;
        return *this;
    };

    /**
     * @brief Post-increment to the next logical element.
     * @return Iterator snapshot before increment.
     */
    iter_dense operator++(int) noexcept
    {
        iter_dense tmp = *this;
        ++(*this);
        return tmp;
    };

    /**
     * @brief Equality comparison.
     * @param other Iterator to compare against.
     * @return True when all iterator state matches.
     */
    bool operator==(const iter_dense& other) const noexcept
    {
        return _data  == other._data
            && _rows  == other._rows
            && _cols  == other._cols
            && _sr    == other._sr
            && _sc    == other._sc
            && _idx   == other._idx
            && _major == other._major;
    };

    /**
     * @brief Inequality comparison.
     * @param other Iterator to compare against.
     * @return True when iterator state differs.
     */
    bool operator!=(const iter_dense& other) const noexcept
    {
        return !(*this == other);
    };

private:
    pointer         _data   = nullptr;
    size_type       _rows   = 0;
    size_type       _cols   = 0;
    size_type       _sr     = 0;
    size_type       _sc     = 0;
    size_type       _idx    = 0;
    Major           _major  = Major::Row;
       
    /**
     * @brief Convert linear index to logical (row, col) coordinates.
     * @return Pair of logical indices (row, col).
     */
    std::pair<size_type, size_type> _logical_position() const
    {
        if (_major == Major::Row)
        {
            size_type i = _idx / _cols;
            size_type j = _idx % _cols;
            return { i, j };
        }
        else 
        {
            size_type j = _idx / _rows;
            size_type i = _idx % _rows;
            return { i, j };
        };
    };

    /**
     * @brief Convert logical (row, col) to physical buffer index.
     * @param i Logical row index.
     * @param j Logical column index.
     * @return Physical index into the storage buffer.
     */
    size_type _phys_idx(size_type i, size_type j) const
    {
        return i * _sr + j * _sc;
    };
};

}; // namespace seoncore::iterators
