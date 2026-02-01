#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>

namespace seoncore::iterators
{

template <typename TN, bool IsConst>
class iter_stride
{
public:
    using value_type      = TN;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    using pointer   = std::conditional_t<IsConst, const TN*, TN*>;
    using reference = std::conditional_t<IsConst, const TN&, TN&>;

    constexpr iter_stride(pointer data, size_type stride, size_type pos) noexcept
        : _data(data), _stride(stride), _pos(pos)
    {};

    constexpr reference operator*() const noexcept
    {
        return _data[_pos * _stride];
    };

    constexpr iter_stride& operator++() noexcept
    {
        ++_pos;
        return *this;
    };

    constexpr pointer operator->() const noexcept
    {
        return std::addressof(operator*());
    };

    constexpr iter_stride operator++(int) noexcept
    {
        iter_stride tmp;
        ++_pos;
        return tmp;
    };

    constexpr iter_stride& operator--() noexcept
    {
        --_pos;
        return *this;
    };

    constexpr iter_stride operator--(int) noexcept
    {
        iter_stride tmp;
        --_pos;
        return tmp;
    };

    constexpr iter_stride& operator+=(difference_type n) noexcept
    {
        _pos += static_cast<size_type>(n);
        return *this;
    };

    constexpr iter_stride& operator-=(difference_type n) noexcept
    {
        _pos -= static_cast<size_type>(n);
        return *this;
    };

    constexpr iter_stride operator+(difference_type n) const noexcept
    {
        iter_stride tmp = *this;
        tmp += n;
        return tmp;
    };

    constexpr iter_stride operator-(difference_type n) const noexcept
    {
        iter_stride tmp = *this;
        tmp -= n;
        return tmp;
    };

    constexpr difference_type operator-(const iter_stride& other) const noexcept
    {
        return static_cast<difference_type>(_pos) - static_cast<difference_type>(other._pos);
    };

    constexpr reference operator[](difference_type n) const noexcept
    {
        return *(*this + n);
    };

    constexpr bool operator==(const iter_stride& other) const noexcept
    {
        return _data    == other._data
            && _stride  == other._stride
            && _pos     == other._pos;
    };

    constexpr bool operator!=(const iter_stride& other) const noexcept
    {
        return !(*this == other);
    };

private:
    pointer   _data;
    size_type _stride;
    size_type _pos;
}; // class iter_stride<TN, IsConst>

}; // namespace seoncore::iterators

