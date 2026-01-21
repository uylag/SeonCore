#pragma once

#include <seoncore/enums/major.hpp>
#include <vector>

namespace seoncore::matrix
{

template <
    typename TN,
    seoncore::enums::Major _Major = seoncore::enums::Major::Row
>
class SparseMatrix
{
public:
    using self = SparseMatrix<TN, _Major>;
    using size_type = std::size_t;

private:
    std::vector<size_type> _values;
    std::vector<size_type> _col_ptr;
    std::vector<size_type> _row_pos;
    size_type _rows;
    size_type _cols;
}; // class SparseMatrix<TN, _Major>

}; // namespace seoncore::matrix
