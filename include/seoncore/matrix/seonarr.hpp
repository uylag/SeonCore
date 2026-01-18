#pragma once

#include <seoncore/enums/major.hpp>
#include <seoncore/enums/policy.hpp>
#include <seoncore/matrix/dense_matrix.hpp>
#include <variant>

namespace seoncore::matrix
{

template <
    typename TN,
    seoncore::enums::Major _Major = seoncore::enums::Major::Row,
    class _Policy = seoncore::policy::fixed_dense
>
class seonarr
{
public:
    /**
     * @brief Matrix container with selectable policy and major order.
     *
     * This is an owning wrapper over dense matrix variants.
     */

private:
    std::variant<
        DenseMatrix<TN, seoncore::enums::Major::Row>,
        DenseMatrix<TN, seoncore::enums::Major::Column>
    > _matrix;

}; // class seonarr<TN, _P>

}; // namespace seoncore::matrix
