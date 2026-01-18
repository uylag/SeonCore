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
    using size_type         = std::size_t;
    using iterator_category = std::forward_iterator_tag;
    using value_type        = TN;
    using difference_type   = std::ptrdiff_t;
    using pointer           = std::conditional_t<IsConst, const TN*, TN*>;
    using reference         = std::conditional_t<IsConst, const TN&, TN&>;

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
        iter_col tmp = *this;
        ++_idx_pos;
        return tmp;
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

}; // class iter_col<TN>

}; // namespace seoncore::iterators
