#pragma once

#include "seoncore/enums/sparse_type.hpp"
#include <seoncore/matrix/seonarr_fwd.hpp>
#include <seoncore/views/matrix_like.hpp>
#include <seoncore/enums/major.hpp>
#include <seoncore/enums/policy.hpp>
#include <seoncore/concepts/like_concept.hpp>
#include <seoncore/matrix/dense_matrix.hpp>
#include <seoncore/matrix/base_matrix.hpp>
#include <seoncore/views/row_view.hpp>
#include <seoncore/views/col_view.hpp>
#include <stdexcept>
#include <type_traits>
#include <iostream>
#include <utility>
#include <variant>
#include <vector>

namespace seoncore::matrix
{

template <
    typename TN,
    class _Policy,
    class _SpTy
>
class seonarr : public BaseMatrix<seonarr<TN, _Policy, _SpTy>, TN>
{
public:
    friend BaseMatrix<seonarr<TN, _Policy, _SpTy>, TN>;

    using size_type       = std::size_t;
    using index_type      = std::size_t;
    using value_type      = TN;
    using reference       = TN&;
    using const_ref       = const TN&;
    using pointer         = TN*;
    using const_ptr       = const TN*;
    using row_view        = seoncore::views::RowView<TN>;
    using const_row_view  = seoncore::views::ConstRowView<TN>;
    using col_view        = seoncore::views::ColView<TN>;
    using const_col_view  = seoncore::views::ConstColView<TN>;
    using matrix_like     = seoncore::views::MatrixLike<TN, _SpTy>;

    seonarr() noexcept
    {
        if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_dense>)
            _matrix = DenseMatrix<TN>();
        _major = seoncore::enums::Major::Row;
    };

    ~seonarr() noexcept = default;

    seonarr(const seonarr& other) 
        : _matrix(other._matrix)
        , _major(other._major)
    {};

    seonarr& operator=(const seonarr& other) 
    {
        if (this == &other) return *this;
        
        _matrix = other._matrix;
        _major = other._major;

        return *this;
    };

    seonarr(seonarr&& other) noexcept
        : _matrix(std::move(other._matrix))
        , _major(other._major)
    {};

    seonarr& operator=(seonarr&& other) noexcept
    {
        if (this == &other) return *this;

        _matrix = std::move(other._matrix);
        _major = other._major;

        return *this;
    };

    seonarr(const DenseMatrix<TN>& dense)
        : _matrix(dense)
        , _major(dense.major())
    {};

    seonarr(const matrix_like& ml)
        : _major(seoncore::enums::Major::Row)
    {
        if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_dense>)
        {
            _matrix = DenseMatrix<TN>(ml);
            _major = std::visit([](auto const& m) { return m.major(); }, _matrix);
        }
        else if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_sparse>) 
        {
            if constexpr (std::is_same_v<_SpTy, seoncore::sparse::SparseType::CRS>)
            {

            }
            else if constexpr (std::is_same_v<_SpTy, seoncore::sparse::SparseType::CSC>) 
            {
            
            }
            else throw std::logic_error("seonarr(MatrixLike): given policy is wrong.");
        }
        else throw std::logic_error("seonarr(MatrixLike): given policy is wrong.");
    };

    seonarr(
            std::vector<TN> raw_data,
            size_type rows,
            size_type cols
           )
        : _major(seoncore::enums::Major::Row)
    {
        _ensure_dense(raw_data, rows, cols);
    };

    void fill(const TN& value) 
    {
        if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_dense>)
            std::visit(
                [value](auto& m) 
                {
                    m.fill(value); 
                }, 
                _matrix
        );

        else
        {
            std::cerr << "fill(value): can't fill sparse matrix.";
            return;
        };
    };

    size_type stride_row() const
    {
        if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_dense>)
            return std::visit([](auto const& m) { return m.stride_row(); }, _matrix);

        else return 0;
    };

    size_type stride_col() const
    {
        if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_dense>)
            return std::visit([](auto const& m) { return m.stride_col(); }, _matrix);

        else return 0;
    };


private:
    std::variant<
        DenseMatrix<TN>
            >         _matrix;
    seoncore::enums::Major _major;

    seoncore::enums::Major major_impl() const { return _major; };

    void _ensure_dense(const std::vector<TN>& raw_data, size_type rows, size_type cols);
    void _ensure_dense(const std::vector<std::vector<TN>>& data);

    template <typename U, class P, class S>
    friend std::ostream& operator<<(std::ostream&, const seonarr<U, P, S>&);

    size_type rows_impl() const noexcept
    {
        return std::visit([](auto const& m) { return m.rows(); }, this->_matrix);
    };

    size_type cols_impl() const noexcept
    {
        return std::visit([](auto const& m) { return m.cols(); }, this->_matrix);
    };

    reference at_impl(index_type i, index_type j)
    {
        return std::visit(
                [i, j](auto& m) -> reference 
                { 
                    return m.at(i, j); 
                }, 
                _matrix
            );
    };

    const_ref at_impl(index_type i, index_type j) const
    {
        return std::visit(
                [i, j](auto& m) -> const_ref 
                { 
                    return m.at(i, j); 
                }, 
                _matrix
            );
    };

    row_view get_row_impl(index_type i) { return std::visit([i](auto const& m) { return m.row(i); }, _matrix); };
    col_view get_col_impl(index_type j) { return std::visit([j](auto const& m) { return m.col(j); }, _matrix); };
    
    const_row_view get_row_impl(index_type i) const { return std::visit([i](auto const& m) { return m.row(i); }, _matrix); };
    const_col_view get_col_impl(index_type j) const { return std::visit([j](auto const& m) { return m.col(j); }, _matrix); };

    matrix_like get_view_impl() const
    {
        return std::visit([](auto const& m) { return m.get_view(); }, _matrix);
    };

}; // class seonarr<TN, _Policy, _SpTy>

template <
    typename TN, 
    class _Policy,
    class _SpTy
>
void seonarr<TN, _Policy, _SpTy>::_ensure_dense(
        const std::vector<TN>& raw_data, 
        std::size_t rows, 
        std::size_t cols)
{
    if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_sparse>)
        throw std::logic_error("seonarr constructor error: parameters don't match chosen policy.");
    
    this->_matrix = DenseMatrix<TN>(raw_data, rows, cols);
};

template <
    typename TN, 
    class _Policy,
    class _SpTy
>
void seonarr<TN, _Policy, _SpTy>::_ensure_dense(const std::vector<std::vector<TN>>& data)
{
    if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_sparse>)
        throw std::logic_error("seonarr constructor error: parameters don't match chosen policy.");
    
    this->_matrix = DenseMatrix<TN>(data);
};

template <
    typename TN,
    class _Policy,
    class _SpTy
>
std::ostream& operator<<(std::ostream& os, const seonarr<TN, _Policy, _SpTy>& A)
{
    os << "seonarr(" << A.rows() << 'x' << A.cols() << ")\n";

    for (std::size_t i = 0; i < A.rows(); ++i)
    {
        for (std::size_t j = 0; j < A.cols(); ++j)
            os << A(i, j) << (j + 1 == A.cols() ? "" : " ");

        os << '\n';
    };

    return os;
};

}; // namespace seoncore::matrix
