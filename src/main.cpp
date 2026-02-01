#include <seoncore/matrix/dense.hpp>
#include <seoncore/matrix/operators.hpp>
#include <iostream>

using namespace seoncore::matrix;
int main()
{
    DenseMatrix<long double> test1({
        {1.01, 2.04, 3.0506},
        {4.0003, 5.0102, 6.07},
        {7.0, 8.0089, 9.0314}
    });

    DenseMatrix<long double> test2({
        {4.06},
        {-3.05},
        {4.07}
    });

    DenseMatrix<long double> result = test1 * test2;

    test2 = test2.abs();

    for (std::size_t i = 0; i < test2.rows(); ++i)
    {
        for (std::size_t j = 0; j < test2.cols(); ++j)
            std::cout << test2(i, j);
        std::cout << '\n';
    };
    
};
