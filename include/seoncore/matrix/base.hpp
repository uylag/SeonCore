#pragma once

#include <cstddef>
#include <utility>
#include <seoncore/enums/major.hpp>
#include <seoncore/views/row.hpp>
#include <seoncore/views/col.hpp>

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
    
    Derived&       derived() { return static_cast<Derived&>(*this); };
    Derived const& derived() const { return static_cast<Derived const&>(*this); };

    size_type rows() const noexcept { return derived().rows_impl(); };
    size_type cols() const noexcept { return derived().cols_impl(); };

    std::pair<size_type, size_type> shape() const { return { rows(), cols() }; };

    reference at(size_type i, size_type j) { return derived().at_impl(i, j); };
    const_ref at(size_type i, size_type j) const { return derived().at_impl(i, j); };

    pointer data()         { return derived().data_impl(); };
    const_ptr data() const { return derived().data_impl(); };

    enums::Major& major()             { return derived().major_impl(); };
    const enums::Major& major() const { return derived().major_impl(); };

    void set_major(const enums::Major& _maj) { derived().major() = _maj; };

    size_type size() const { return rows() * cols(); };

    reference operator()(size_type i, size_type j)       { return at(i, j); };
    const_ref operator()(size_type i, size_type j) const { return at(i, j); };

    seoncore::views::MutableRowView<TN> row(size_type i) noexcept { return derived().row_impl(i); };
    const seoncore::views::RowView<TN> row(size_type i) const noexcept { return derived().row_impl(i); };

    seoncore::views::MutableColView<TN> col(size_type j) noexcept { return derived().col_impl(j); };
    const seoncore::views::ColView<TN> col(size_type j) const noexcept { return derived().col_impl(j); };

    // TODO: flatten (using Vector<TN> type), transpose (using TransposedView<TN> type)

    
       

private:


};

};
