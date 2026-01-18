#pragma once

#include <cstddef>
#include <type_traits>
#include <variant>
#include <seoncore/enums/major.hpp>
#include <seoncore/enums/sparse_type.hpp>
#include <seoncore/iterators/iter_dense.hpp>
#include <seoncore/iterators/iter_sparse.hpp>
#include <seoncore/iterators/iter_row.hpp>
#include <seoncore/iterators/iter_col.hpp>
#include <seoncore/views/view_dmat.hpp>
#include <seoncore/views/view_smat.hpp>
#include <seoncore/views/view_vec.hpp>

namespace seoncore::views
{

template <
    typename TN, 
    class /* sparse type */ _SpTy = seoncore::sparse::SparseType::CRS
>
class MatrixLike
{
public:
    /**
     * @brief Lightweight matrix view wrapper for dense or sparse storage.
     *
     * Holds non-owning pointers plus shape/stride metadata.
     */
    using value_type = TN;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using index_type = std::size_t;
    using const_ptr = const TN*;
    using Major = seoncore::enums::Major;

    using vec_view = seoncore::views::VectorView<TN>;

    using iterator = seoncore::iterators::iter_dense<const TN>;

    using iterator_row = seoncore::iterators::iter_row<TN, false>;
    using const_iter_row = seoncore::iterators::iter_row<TN, true>;
    using iterator_col = seoncore::iterators::iter_col<TN, false>;
    using const_iter_col = seoncore::iterators::iter_col<TN, true>;

    struct _DenseLike
    {
        /**
         * @brief Dense storage descriptor.
         * @param _data Base pointer to matrix storage.
         * @param _rows Logical number of rows.
         * @param _cols Logical number of columns.
         * @param _stride_row Row stride.
         * @param _stride_col Column stride.
         */
        const_ptr _data;
        size_type _rows;
        size_type _cols;
        size_type _stride_row;
        size_type _stride_col;
    };

    struct _CRSLike
    {
        /**
         * @brief Sparse CRS/CSR storage descriptor.
         * @param _values Nonzero values array.
         * @param _col_idx Column indices per nonzero.
         * @param _row_ptr Row pointer offsets.
         * @param _rows Logical number of rows.
         * @param _cols Logical number of columns.
         */
        const_ptr _values;
        const size_type* _col_idx;
        const size_type* _row_ptr;
        size_type _rows;
        size_type _cols;
    };

    struct _CSCLike
    {
        /**
         * @brief Sparse CSC storage descriptor.
         * @param _values Nonzero values array.
         * @param _row_idx Row indices per nonzero.
         * @param _col_ptr Column pointer offsets.
         * @param _rows Logical number of rows.
         * @param _cols Logical number of columns.
         */
        const_ptr _values;
        const size_type* _row_idx;
        const size_type* _col_ptr;
        size_type _rows;
        size_type _cols;
    };

    using storage_type = std::variant<
            std::monostate,
            _DenseLike,
            _CRSLike,
            _CSCLike
        >;

    MatrixLike() noexcept = default;

    /**
     * @brief Construct a dense matrix view.
     * @param data Base pointer to matrix storage.
     * @param rows Logical number of rows.
     * @param cols Logical number of columns.
     * @param stride_row Row stride.
     * @param stride_col Column stride.
     */
    MatrixLike(
        const_ptr data,
        size_type rows,
        size_type cols,
        size_type stride_row,
        size_type stride_col) noexcept
        : _storage(_DenseLike{ data, rows, cols, stride_row, stride_col })
    {};

    /**
     * @brief Construct a sparse matrix view.
     * @param values Nonzero values array.
     * @param idx Column (CRS) or row (CSC) index array.
     * @param ptr Row (CRS) or column (CSC) pointer array.
     * @param rows Logical number of rows.
     * @param cols Logical number of columns.
     */
    MatrixLike(
            const_ptr values,
            const size_type* idx,
            const size_type* ptr,
            size_type rows,
            size_type cols) noexcept
    {
        if constexpr (std::is_same_v<_SpTy, seoncore::sparse::SparseType::CRS>)
        {
            _storage = _CRSLike{ values, idx, ptr, rows, cols };
        }
        else if constexpr (std::is_same_v<_SpTy, seoncore::sparse::SparseType::CSC>)
        {
            _storage = _CSCLike{ values, idx, ptr, rows, cols };
        };
    };


    /**
     * @brief Check whether storage is dense.
     * @return True if dense storage is active.
     */
    bool is_dense() const noexcept { return std::holds_alternative<_DenseLike>(_storage); };
    /**
     * @brief Check whether storage is sparse.
     * @return True if sparse storage is active.
     */
    bool is_sparse() const noexcept 
    { 
        return std::holds_alternative<_CRSLike>(_storage)
            || std::holds_alternative<_CSCLike>(_storage); 
    };
    
    size_type rows() const noexcept
    {
        if (auto p = std::get_if<_DenseLike>(&_storage))
            return p->rows;
        if (auto p = std::get_if<_CRSLike>(&_storage))
            return p->rows;
        if (auto p = std::get_if<_CSCLike>(&_storage))
            return p->rows;

        return 0;
    };

    /**
     * @brief Get the number of columns.
     * @return Logical column count.
     */
    size_type cols() const noexcept
    {
        if (auto p = std::get_if<_DenseLike>(&_storage))
            return p->cols;
        if (auto p = std::get_if<_CRSLike>(&_storage))
            return p->cols;
        if (auto p = std::get_if<_CSCLike>(&_storage))
            return p->cols;

        return 0;
    };

    /**
     * @brief Get total element count (rows * cols).
     * @return Logical matrix size.
     */
    size_type size() const noexcept
    {
        return rows() * cols();
    };

    /**
     * @brief Iterator to the first element (dense only).
     * @param major Traversal order for dense iteration.
     * @return Dense iterator at the logical start.
     */
    iterator begin(Major major = Major::Row) const noexcept
    {
        if (auto p = std::get_if<_DenseLike>(&_storage))
        {
            return iterator(
                p->_data,
                p->_rows,
                p->_cols,
                p->_stride_row,
                p->_stride_col,
                major,
                0);
        }

        return iterator(nullptr, 0, 0, 0, 0, major, 0);
    };

    /**
     * @brief Iterator past the last element (dense only).
     * @param major Traversal order for dense iteration.
     * @return Dense iterator at the logical end.
     */
    iterator end(Major major = Major::Row) const noexcept
    {
        if (auto p = std::get_if<_DenseLike>(&_storage))
        {
            return iterator(
                p->_data,
                p->_rows,
                p->_cols,
                p->_stride_row,
                p->_stride_col,
                major,
                p->_rows * p->_cols);
        }

        return iterator(nullptr, 0, 0, 0, 0, major, 0);
    };

    /**
     * @brief Access a logical element by index.
     * @param i Logical row index.
     * @param j Logical column index.
     * @return Reference to the requested element (dense only).
     */
    const TN& operator()(index_type i, index_type j) const noexcept
    {
        if (auto p = std::get_if<_DenseLike>(&_storage))
            return p->_data[i * p->_stride_row + j * p->_stride_col];
        return TN{-1.23456789};
    };

private:
    storage_type _storage;
}; // MatrixLike<TN, _SpTy>

namespace like
{

template <typename TN>
struct MatrixLikeDefault : MatrixLike<TN>
{
    /**
     * @brief Default MatrixLike instance for optional parameters.
     */
};

}; // namespace seoncore::views::like

}; // namespace seoncore::views
