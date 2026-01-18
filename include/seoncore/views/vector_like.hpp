#pragma once

#include <variant>
#include <seoncore/views/view_dvec.hpp>
#include <seoncore/views/view_svec.hpp>

namespace seoncore::views
{

template <typename TN>
class VectorLike
{
public:

    VectorLike() = default;
private:
    std::variant<
        DenseVectorView<TN>, 
        SparseCSRVectorView<TN>,
        SparseCSCVectorView<TN>
    > _view = DenseVectorView<TN>();
};

namespace like
{

template <typename TN>
struct VectorLikeDefault : VectorLike<TN> {};

};

};

