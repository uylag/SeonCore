#pragma once

#include <type_traits>
#include <seoncore/views/vec.hpp>
#include <seoncore/matrix/base.hpp>
#include <utility>

namespace seoncore::views
{

template <class _Base, bool IsConst>
class BaseTransposedView : 
    public seoncore::matrix::BaseMatrix<
        BaseTransposedView<_Base, IsConst>,
        typename _Base::value_type
    >
{
public:

    friend struct matrix::BaseMatrix<BaseTransposedView<_Base, IsConst>, typename _Base::value_type>;

    using matrix_type       = _Base;
    using value_type        = typename matrix_type::value_type;

    using reference         = std::conditional_t<
        IsConst, 
        typename matrix_type::const_ref, 
        typename matrix_type::reference
    >;

    using pointer           = std::conditional_t<
        IsConst, 
        typename matrix_type::const_ptr, 
        typename matrix_type::pointer
    >;

    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;

    using vec_view          = std::conditional_t<
        IsConst, 
        seoncore::views::VectorView<value_type>, 
        seoncore::views::MutableVectorView<value_type>
    >;

    using mat_ref           = std::conditional_t<
        IsConst, 
        const matrix_type&, 
        matrix_type&
    >;

    constexpr explicit BaseTransposedView(mat_ref m) noexcept
        : _m(m)
    {};

    constexpr bool operator==(const BaseTransposedView& other) noexcept
    {
        return _m == other._m;
    };

    constexpr bool operator!=(const BaseTransposedView& other) noexcept { return !(*this == other); };

    constexpr mat_ref base() noexcept { return _m; };

private:
    mat_ref _m;

    constexpr size_type rows_impl() const noexcept { return _m.cols(); };
    constexpr size_type cols_impl() const noexcept { return _m.rows(); };

    constexpr reference at_impl(size_type i, size_type j) noexcept
    {
        return _m.at(j, i);
    };

    constexpr reference at_impl(size_type i, size_type j) const noexcept
    {
        return _m.at(j, i);
    };

    constexpr vec_view row_impl(size_type i) noexcept
    {
        return _m.col(i);
    };

    constexpr vec_view col_impl(size_type j) noexcept
    {
        return _m.row(j);
    };

    constexpr mat_ref transposed_impl() noexcept { return _m; };
    constexpr const matrix_type& transposed_impl() const noexcept { return _m; };

}; // class BaseTransposedView<TN, IsConst>

template <class _Base>
using TransposedView = BaseTransposedView<_Base, true>;

template <class _Base>
using MutableTransposedView = BaseTransposedView<_Base, false>;

}; // namespace seoncore::views
