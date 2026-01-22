#include <seoncore/views/view_dmat.hpp>
#include <seoncore/enums/major.hpp>
#include <seoncore/views/row_view.hpp>
#include <seoncore/views/col_view.hpp>
#include <seoncore/matrix/dense_matrix.hpp>
#include <seoncore/matrix/seonarr.hpp>
#include <seoncore/views/matrix_like.hpp>
#include <vector>
#include <iostream>

using namespace seoncore::views;
using namespace seoncore::enums;
using namespace seoncore::matrix;

int main()
{
    DenseMatrix<long double> d1({
        {-1, 2, -3},
        {4, -5, 6}
    });

    seonarr<long double> arr(d1);
   
    std::cout << arr.abs(); 

};
