#pragma once

#include <seoncore/matrix/base_matrix.hpp>
#include <seoncore/enums/major.hpp>
#include <vector>

namespace seoncore::matrix
{

template <
    typename TN
>
class SparseMatrix : public BaseMatrix<SparseMatrix<TN>, TN>
{
public:
    using self = SparseMatrix<TN>;
    using size_type = std::size_t;

private:
    std::vector<size_type> _values;
    std::vector<size_type> _col_ptr;
    std::vector<size_type> _row_pos;
    size_type _rows;
    size_type _cols;

    size_type nnz() const { return _values.size(); };
}; // class SparseMatrix<TN>

}; // namespace seoncore::matrix
