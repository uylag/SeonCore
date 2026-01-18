#pragma once

#include <cstddef>
#include <seoncore/enums/major.hpp>
#include <seoncore/iterators/iter_dense.hpp>

namespace seoncore::views
{

template <typename TN>
class DenseMatrixView
{
public:
    /**
     * @brief Mutable dense matrix view with explicit strides.
     */
    using size_type = std::size_t;
    using Major     = seoncore::enums::Major;
    using iterator  = seoncore::iterators::iter_dense<TN>;

    DenseMatrixView() = default;
    /**
     * @brief Construct a dense matrix view.
     * @param data Base pointer to matrix storage.
     * @param rows Logical number of rows.
     * @param cols Logical number of columns.
     * @param sr Row stride.
     * @param sc Column stride.
     */
    DenseMatrixView(
            TN* data,
            size_type rows,
            size_type cols,
            size_type sr,
            size_type sc)
        : _data(data)
        , _rows(rows)
        , _cols(cols)
        , _sr(sr)
        , _sc(sc)
    {};

    /**
     * @brief Iterator to the first element using a given traversal order.
     * @param major Traversal order (row-major or column-major).
     * @return Dense iterator at the first logical element.
     */
    iterator begin(Major major) const
    {
        return iterator(_data, _rows, _cols, _sr, _sc, major, 0);
    };

    /**
     * @brief Iterator past the last element using a given traversal order.
     * @param major Traversal order (row-major or column-major).
     * @return Dense iterator at the logical end.
     */
    iterator end(Major major) const
    {
        return iterator(_data, _rows, _cols, _sr, _sc, major, _rows * _cols);
    };
    
private:
    TN* _data           = nullptr;
    size_type _rows     = 0;
    size_type _cols     = 0;
    size_type _sr       = 0;
    size_type _sc       = 0;
};

template <typename TN>
class ConstDenseMatrixView
{
public:
    /**
     * @brief Read-only dense matrix view with explicit strides.
     */
    using size_type = std::size_t;
    using Major     = seoncore::enums::Major;
    using iterator  = seoncore::iterators::iter_dense<const TN>;

    ConstDenseMatrixView() = default;
    /**
     * @brief Construct a const dense matrix view.
     * @param data Base pointer to matrix storage.
     * @param rows Logical number of rows.
     * @param cols Logical number of columns.
     * @param sr Row stride.
     * @param sc Column stride.
     */
    ConstDenseMatrixView(
            const TN* data,
            size_type rows,
            size_type cols,
            size_type sr,
            size_type sc)
        : _data(data)
        , _rows(rows)
        , _cols(cols)
        , _sr(sr)
        , _sc(sc)
    {};

    /**
     * @brief Iterator to the first element using a given traversal order.
     * @param major Traversal order (row-major or column-major).
     * @return Dense iterator at the first logical element.
     */
    iterator begin(Major major) const
    {
        return iterator(_data, _rows, _cols, _sr, _sc, major, 0);
    };

    /**
     * @brief Iterator past the last element using a given traversal order.
     * @param major Traversal order (row-major or column-major).
     * @return Dense iterator at the logical end.
     */
    iterator end(Major major) const
    {
        return iterator(_data, _rows, _cols, _sr, _sc, major, _rows * _cols);
    };
    
private:
    const TN* _data     = nullptr;
    size_type _rows     = 0;
    size_type _cols     = 0;
    size_type _sr       = 0;
    size_type _sc       = 0;
};

};
