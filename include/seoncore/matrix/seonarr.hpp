#pragma once

#include <seoncore/enums/major.hpp>
#include <seoncore/enums/policy.hpp>
#include <seoncore/matrix/dense_matrix.hpp>
#include <seoncore/matrix/base_matrix.hpp>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace seoncore::matrix
{

template <
    typename TN,
    seoncore::enums::Major _Major = seoncore::enums::Major::Row,
    class _Policy = seoncore::policy::fixed_dense
>
class seonarr : public BaseMatrix<seonarr<TN, _Major, _Policy>, TN>
{
public:
    using size_type       = std::size_t;
    using index_type      = std::size_t;
    using value_type      = TN;
    using reference       = TN&;
    using pointer         = TN*;
    using const_ptr       = const TN*;

    seonarr() noexcept
    {
        if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_dense>)
            _matrix = DenseMatrix<TN, _Major>();
    };

    ~seonarr() noexcept = default;

    seonarr(const seonarr& other) 
        : _matrix(other._matrix)
    {};

    seonarr& operator=(const seonarr& other) 
    {
        if (this == &other) return *this;
        
        _matrix = other._matrix;

        return *this;
    };

    seonarr(seonarr&& other) noexcept
        : _matrix(std::move(other._matrix))
    {
    };

    seonarr& operator=(seonarr&& other) noexcept
    {
        if (this == &other) return *this;

        _matrix = std::move(other._matrix);

        other._rows = 0;
        other._cols = 0;

        return *this;
    };

    seonarr(const DenseMatrix<TN, _Major>& dense)
        : _matrix(dense)
    {};

    seonarr(
            std::vector<TN> raw_data,
            size_type rows,
            size_type cols
           )
    {
        _ensure_dense(raw_data, rows, cols);
    };


private:
    std::variant<
        DenseMatrix<TN, seoncore::enums::Major::Row>,
        DenseMatrix<TN, seoncore::enums::Major::Column>
            >         _matrix;

    void _ensure_dense(const std::vector<TN>& raw_data, size_type rows, size_type cols);
    void _ensure_dense(const std::vector<std::vector<TN>>& data);

    size_type rows_impl() const noexcept
    {
        return std::visit([](auto const& m) { return m.rows(); }, this->_matrix);
    };

    size_type cols_impl() const noexcept
    {
        return std::visit([](auto const& m) { return m.cols(); }, this->_matrix);
    };


}; // class seonarr<TN, _Major, _Policy>

template <
    typename TN, 
    seoncore::enums::Major _Major, 
    class _Policy 
>
void seonarr<TN, _Major, _Policy>::_ensure_dense(
        const std::vector<TN>& raw_data, 
        std::size_t rows, 
        std::size_t cols)
{
    if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_sparse>)
        throw std::logic_error("seonarr constructor error: parameters don't match chosen policy.");
    
    this->_matrix = DenseMatrix<TN, _Major>(raw_data, rows, cols);
    
    //this->_rows = std::visit([](auto const& m) { return m.rows(); }, this->_matrix);
    //this->_cols = std::visit([](auto const& m) { return m.cols(); }, this->_matrix);
};

template <
    typename TN, 
    seoncore::enums::Major _Major, 
    class _Policy 
>
void seonarr<TN, _Major, _Policy>::_ensure_dense(const std::vector<std::vector<TN>>& data)
{
    if constexpr (std::is_same_v<_Policy, seoncore::policy::fixed_sparse>)
        throw std::logic_error("seonarr constructor error: parameters don't match chosen policy.");
    
    this->_matrix = DenseMatrix<TN, _Major>(data);
};

}; // namespace seoncore::matrix
