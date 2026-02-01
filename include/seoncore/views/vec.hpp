#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>
#include <seoncore/iterators/iter_stride.hpp>

namespace seoncore::views
{

template <typename TN, bool IsConst>
class BaseVectorView
{
public:
    using value_type        = TN;
    using reference         = std::conditional_t<IsConst, const TN&, TN&>;
    using pointer           = std::conditional_t<IsConst, const TN*, TN*>;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    using iterator          = seoncore::iterators::iter_stride<TN, IsConst>;

    constexpr BaseVectorView() noexcept
        : _data(nullptr)
        , _size(0)
        , _stride(0)
    {};

    constexpr BaseVectorView(
            pointer data,
            size_type size,
            size_type stride) noexcept
        : _data(data)
        , _size(size)
        , _stride(stride)
    {
        if (_size != 0)
        {
            assert(_data != nullptr);
            assert(_stride >= 1);
        };
    };

    [[nodiscard]]
    constexpr pointer data() const noexcept { return _data; };
    [[nodiscard]]
    constexpr size_type size() const noexcept { return _size; };
    [[nodiscard]]
    constexpr size_type stride() const noexcept { return _stride; };

    [[nodiscard]]
    constexpr bool empty() const noexcept { return _size == 0; };

    [[nodiscard]]
    constexpr bool contiguous() const noexcept { return _stride == 1; };

    [[nodiscard]]
    constexpr reference operator[](size_type i) const noexcept
    {
        assert(i < _size);
        return _data[i * _stride];
    };

    [[nodiscard]]
    constexpr reference at(size_type i) const noexcept
    {
        assert(i < _size);
        return _data[i * _stride];
    };

    [[nodiscard]]
    constexpr reference operator()(size_type i) const noexcept { return at(i); };

    [[nodiscard]]
    constexpr reference front() const noexcept
    {
        assert(_size > 0);
        return (*this)[0];
    };

    [[nodiscard]]
    constexpr reference back() const noexcept
    {
        assert(_size > 0);
        return (*this)[_size - 1];
    };

    [[nodiscard]]
    constexpr BaseVectorView slice(size_type pos, size_type count) const noexcept
    {
        assert(pos <= _size);
        assert(pos + count <= _size);
        return BaseVectorView(_data + pos * _stride, count, _stride);
    };

    [[nodiscard]]
    constexpr BaseVectorView with_stride(size_type stride) const noexcept
    {
        if (_size != 0) assert(stride >= 1);
        return BaseVectorView(_data, _size, stride);
    };

    [[nodiscard]]
    constexpr iterator begin() const noexcept
    {
        return iterator(_data, _stride, 0);
    };

    [[nodiscard]]
    constexpr iterator end() const noexcept
    {
        return iterator(_data, _stride, _size);
    };

private:
    pointer     _data;
    size_type   _size;
    size_type   _stride;
}; // class BaseVectorView<TN, IsConst>
   
template <typename TN>
using VectorView = BaseVectorView<TN, true>;

template <typename TN>
using MutableVectorView = BaseVectorView<TN, false>;

}; // namespace seoncore::views
