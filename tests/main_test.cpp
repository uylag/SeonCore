#include <cassert>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include <seoncore/matrix/dense_matrix.hpp>
#include <seoncore/matrix/seonarr.hpp>

namespace
{

void test_dense_matrix_basic()
{
    seoncore::matrix::DenseMatrix<int> m({
        {1, 2, 3},
        {4, 5, 6}
    });

    assert(m.rows() == 2);
    assert(m.cols() == 3);
    assert(m.size() == 6);
    assert(m(0, 0) == 1);
    assert(m(1, 2) == 6);

    m(0, 1) = 9;
    assert(m(0, 1) == 9);
}

void test_dense_matrix_row_col_views()
{
    seoncore::matrix::DenseMatrix<int> m({
        {1, 2, 3},
        {4, 5, 6}
    });

    std::vector<int> row_vals;
    for (auto v : m.row(1))
        row_vals.push_back(v);
    assert((row_vals == std::vector<int>{4, 5, 6}));

    std::vector<int> col_vals;
    for (auto v : m.col(1))
        col_vals.push_back(v);
    assert((col_vals == std::vector<int>{2, 5}));
}

void test_dense_matrix_fill_and_view()
{
    seoncore::matrix::DenseMatrix<int> m({
        {1, 2},
        {3, 4}
    });

    m.fill(7);
    for (std::size_t i = 0; i < m.rows(); ++i)
        for (std::size_t j = 0; j < m.cols(); ++j)
            assert(m(i, j) == 7);

    auto view = m.get_view();
    assert(view.rows() == 2);
    assert(view.cols() == 2);
    assert(view(1, 1) == 7);
}

void test_dense_matrix_reduce_and_dot()
{
    seoncore::matrix::DenseMatrix<double> a({
        {1.0, 2.0},
        {3.0, 4.0}
    });
    seoncore::matrix::DenseMatrix<double> b({
        {5.0, 6.0},
        {7.0, 8.0}
    });

    const double dot = a.dot(b);
    assert(std::abs(dot - (1.0 * 5.0 + 2.0 * 6.0 + 3.0 * 7.0 + 4.0 * 8.0)) < 1e-9);

    assert(std::abs(a.sum() - 10.0) < 1e-9);
    assert(std::abs(a.max() - 4.0) < 1e-9);
    assert(std::abs(a.min() - 1.0) < 1e-9);

    const double norm2 = a.norm_p(2);
    assert(std::abs(norm2 - std::sqrt(1.0 + 4.0 + 9.0 + 16.0)) < 1e-9);
}

void test_seonarr_basic_and_stream()
{
    seoncore::matrix::DenseMatrix<int> d({
        {1, 2},
        {3, 4}
    });

    seoncore::matrix::seonarr<int> a(d);
    assert(a.rows() == 2);
    assert(a.cols() == 2);

    a.fill(3);
    assert(a(0, 0) == 3);
    assert(a(1, 1) == 3);

    const int dot = a.dot(d);
    assert(dot == (3 * 1 + 3 * 2 + 3 * 3 + 3 * 4));

    std::ostringstream oss;
    oss << a;
    const std::string out = oss.str();
    assert(out.find("seonarr(2x2)") != std::string::npos);
}

} // namespace

int main()
{
    test_dense_matrix_basic();
    test_dense_matrix_row_col_views();
    test_dense_matrix_fill_and_view();
    test_dense_matrix_reduce_and_dot();
    test_seonarr_basic_and_stream();
    return 0;
}
