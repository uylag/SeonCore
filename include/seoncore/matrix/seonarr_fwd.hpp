#pragma once

#include <seoncore/enums/sparse_type.hpp>
#include <seoncore/enums/policy.hpp>

namespace seoncore::matrix
{

template <
    typename TN,
    class _Policy = seoncore::policy::fixed_dense,
    class _SpTy = seoncore::sparse::SparseType::CRS
>
class seonarr;

} // namespace seoncore::matrix
