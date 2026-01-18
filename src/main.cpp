#include <seoncore/views/view_dmat.hpp>
#include <seoncore/enums/major.hpp>
#include <seoncore/views/row_view.hpp>
#include <seoncore/views/col_view.hpp>
#include <seoncore/matrix/dense_matrix.hpp>
#include <seoncore/views/matrix_like.hpp>
#include <vector>
#include <iostream>

using namespace seoncore::views;
using namespace seoncore::enums;

/**
 * @brief Demo entry point for basic matrix iteration.
 * @return Exit code.
 */
int main()
{
    std::vector<double> matrix = {
        1, 2, 3,
        4, 5, 6
    };

    std::size_t sr = 3;
    std::size_t sc = 1;
    
    seoncore::views::MatrixLike<double> mat_ml{ matrix.data(), 2, 3, sr, sc };

    for (auto it = mat_ml.begin(); it != mat_ml.end(); ++it)
        std::cout << *it << " ";
};
