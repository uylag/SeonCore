#pragma once

#include <seoncore/enums/sparse_type.hpp>

namespace seoncore::views
{

template <
    typename TN,
    class _SpTy = seoncore::sparse::SparseType::CRS
>
class MatrixLike;

} // namespace seoncore::views
