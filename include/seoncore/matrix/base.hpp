#pragma once

#include <cstddef>
#include <utility>
#include <seoncore/enums/major.hpp>
#include <seoncore/views/vec.hpp>
#include <seoncore/views/transposed_fwd.hpp>
#include <seoncore/concepts/matrix_like.hpp>
#include <seoncore/ops/reduce.hpp>
#include <seoncore/ops/transform.hpp>

namespace seoncore::matrix
{

template <class Derived, typename TN>
struct BaseMatrix
{
public:
    using value_type        = TN;
    using reference         = TN&;
    using const_ref         = const TN&;
    using pointer           = TN*;
    using const_ptr         = const TN*;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    
    constexpr Derived&       derived() { return static_cast<Derived&>(*this); };
    constexpr Derived const& derived() const { return static_cast<Derived const&>(*this); };

    constexpr size_type rows() const noexcept { return derived().rows_impl(); };
    constexpr size_type cols() const noexcept { return derived().cols_impl(); };

    constexpr std::pair<size_type, size_type> shape() const { return { rows(), cols() }; };

    constexpr reference at(size_type i, size_type j) { return derived().at_impl(i, j); };
    constexpr const_ref at(size_type i, size_type j) const { return derived().at_impl(i, j); };

    constexpr pointer data()         { return derived().data_impl(); };
    constexpr const_ptr data() const { return derived().data_impl(); };

    constexpr enums::Major& major()             { return derived().major_impl(); };
    constexpr const enums::Major& major() const { return derived().major_impl(); };

    constexpr void set_major(const enums::Major& _maj) 
    { 
        derived().major() = _maj; 
        derived().recompute_strides_impl();
    };

    constexpr size_type size() const { return rows() * cols(); };

    constexpr reference operator()(size_type i, size_type j)       { return at(i, j); };
    constexpr const_ref operator()(size_type i, size_type j) const { return at(i, j); };

    constexpr seoncore::views::MutableVectorView<TN> row(size_type i) noexcept { return derived().row_impl(i); }; 
    constexpr seoncore::views::VectorView<TN> row(size_type i) const noexcept { return derived().row_impl(i); }; 

    constexpr seoncore::views::MutableVectorView<TN> col(size_type j) noexcept { return derived().col_impl(j); }; 
    constexpr seoncore::views::VectorView<TN> col(size_type j) const noexcept { return derived().col_impl(j); }; 

    constexpr seoncore::views::MutableVectorView<TN> flatten() noexcept { return derived().flatten_impl(); };
    constexpr seoncore::views::VectorView<TN>        flatten() const noexcept { return derived().flatten_impl(); };

    constexpr auto 
    transposed() noexcept { return derived().transposed_impl(); };
    constexpr auto 
    transposed() const noexcept { return derived().transposed_impl(); };

    constexpr TN sum() const noexcept 
    {
        return seoncore::ops::sum(derived());
    };

    constexpr TN min() const noexcept
    {
        return seoncore::ops::min(derived());
    };

    constexpr TN max() const noexcept
    {
        return seoncore::ops::max(derived());
    };

    [[nodiscard]]
    constexpr auto abs() const noexcept
    {
        return seoncore::ops::abs(derived());
    };

}; // class BaseMatrix<Derived, TN>

}; // namespace seoncore::matrix
