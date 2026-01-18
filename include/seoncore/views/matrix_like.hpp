#pragma once

#include <seoncore/views/view_vec.hpp>
#include <cstddef>
#include <variant>
#include <seoncore/enums/sparse_type.hpp>
#include <seoncore/iterators/iter_dense.hpp>
#include <seoncore/iterators/iter_sparse.hpp>
#include <seoncore/iterators/iter_row.hpp>
#include <seoncore/iterators/iter_col.hpp>
#include <seoncore/views/view_dmat.hpp>
#include <seoncore/views/view_smat.hpp>

namespace seoncore::views
{

template <
    typename TN, 
    class /* sparse type */ _SpTy = seoncore::sparse::SparseType::CRS
>
class MatrixLike
{
public:
    using value_type = TN;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using index_type = std::size_t;
    using const_ptr = const TN*;

    using mat_view = std::variant<
            seoncore::views::DenseMatrixView<TN>,
            seoncore::views::SparseCRSMatrixView<TN>,
            seoncore::views::SparseCSCMatrixView<TN>
        >;

    using vec_view = seoncore::views::VectorView<TN>;

    using iterator = std::variant<
            seoncore::iterators::iter_dense<TN>,
            seoncore::iterators::iter_sparse<TN>
        >;

    using iterator_row = seoncore::iterators::iter_row<TN, false>;
    using const_iter_row = seoncore::iterators::iter_row<TN, true>;
    using iterator_col = seoncore::iterators::iter_col<TN, false>;
    using const_iter_col = seoncore::iterators::iter_col<TN, true>;

    struct _DenseLike
    {
        const_ptr _data;
        size_type _rows;
        size_type _cols;
        size_type _stride_row;
        size_type _stride_col;
    };

    struct _CRSLike
    {
        const_ptr _values;
        const size_type* _col_idx;
        const size_type* _row_ptr;
        size_type _rows;
        size_type _cols;
    };

    struct _CSCLike
    {
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

    MatrixLike(
            const_ptr data,
            size_type rows,
            size_type cols,
            size_type stride_row,
            size_type stride_col) noexcept
    {
        MatrixLike ml;
        ml._storage = _DenseLike{ data, rows, cols, stride_row, stride_col };
        return ml;
    };

    MatrixLike(
            const_ptr values,
            const size_type* idx,
            const size_type* ptr,
            size_type rows,
            size_type cols,
            seoncore::sparse::SparseType type) noexcept
    {
        MatrixLike ml;

        if constexpr (std::is_same_v<_SpTy, seoncore::sparse::SparseType::CRS>)
        {
            ml._storage = _CRSLike{ values, idx, ptr, rows, cols };
        }
        else if constexpr (std::is_same_v<_SpTy, seoncore::sparse::SparseType::CSC>)
        {
            ml._storage = _CSCLike{ values, idx, ptr, rows, cols };
        };

        return ml;
    };


    bool is_dense() const noexcept { return std::holds_alternative<_DenseLike>(_storage); };
    bool is_sparse() const noexcept { return std::holds_alternative<_CRSLike>(_storage); };
    
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

    size_type size() const noexcept
    {
        return rows() * cols();
    };

    iterator begin() noexcept
    {
        mat_view mv;

        if (auto p = std::get_if<_DenseLike>(&_storage))
        {
            mv = seoncore::views::DenseMatrixView<TN>(
                p->_data,
                p->_rows,
                p->_cols,
                p->_stride_row,
                p->_stride_col
            );
        }

        return mv.begin();
    };

    iterator end() noexcept
    {
        mat_view mv;

        if (auto p = std::get_if<_DenseLike>(&_storage))
        {
            mv = seoncore::views::DenseMatrixView<TN>(
                p->_data,
                p->_rows,
                p->_cols,
                p->_stride_row,
                p->_stride_col
            );
        }

        return mv.end();
    };



private:
    storage_type _storage;
}; // MatrixLike<TN, _SpTy>

namespace like
{

template <typename TN>
struct MatrixLikeDefault : MatrixLike<TN> {};

}; // namespace seoncore::views::like

}; // namespace seoncore::views
