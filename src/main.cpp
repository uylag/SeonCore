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
using namespace seoncore::matrix;

int main()
{
    DenseMatrix<long double> d1({
        {1, 2, 3},
        {4, 5, 6}
    });

    std::cout << "Norm_p: " << d1.norm_p(2) << '\n';
    std::cout << "Sum: " << d1.sum() << '\n';
    std::cout << "Max: " << d1.max() << '\n';
    std::cout << "Min: " << d1.min() << '\n';
};
