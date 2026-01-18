#pragma once

#include <iterator>
#include <memory>
#include <seoncore/enums/major.hpp>

namespace seoncore::iterators
{

template <typename TN>
class iter_dense
{
public:
    using size_type         = std::size_t;
    using iterator_category = std::forward_iterator_tag;
    using value_type        = TN;
    using difference_type   = std::ptrdiff_t;
    using pointer           = TN*;
    using reference         = TN&;
    using Major             = seoncore::enums::Major;

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
        , _major(major)
        , _idx(idx)
    {};

    reference operator*() const noexcept
    {
        auto [i, j] = _logical_position();
        return _data[_phys_idx(i, j)];
    };

    pointer operator->() const noexcept
    {
        return std::addressof(operator*());
    };

    iter_dense& operator++() noexcept
    {
        ++_idx;
        return *this;
    };

    iter_dense operator++(int) noexcept
    {
        iter_dense tmp = *this;
        ++(*this);
        return tmp;
    };

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

    size_type _phys_idx(size_type i, size_type j) const
    {
        return i * _sr + j * _sc;
    };
};

}; // namespace seoncore::iterators
