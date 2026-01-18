#include <seoncore/views/view_dmat.hpp>
#include <seoncore/enums/major.hpp>
#include <seoncore/views/row_view.hpp>
#include <seoncore/views/col_view.hpp>
#include <seoncore/matrix/dense_matrix.hpp>
#include <vector>
#include <iostream>

using namespace seoncore::views;
using namespace seoncore::enums;

int main()
{
    std::vector<long long> matrix = {
        1, 2, 3,
        4, 5, 6
    };

    std::size_t sr = 3;
    std::size_t sc = 1;
    RowView<long long> matrix_rv(matrix.data(), 1, 3, sr, sc);
    ColView<long long> matrix_cv(matrix.data(), 1, 2, 3, sr, sc);

    for (auto it = matrix_rv.begin(); it != matrix_rv.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\n\n";

    for (auto it = matrix_cv.begin(); it != matrix_cv.end(); ++it)
        std::cout << *it << " ";

};
