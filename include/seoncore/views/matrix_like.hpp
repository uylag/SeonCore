#pragma once

#include <variant>
#include <seoncore/views/view_dmat.hpp>
#include <seoncore/views/view_smat.hpp>

namespace seoncore::views
{

template <typename TN>
class MatrixLike
{
public:

    MatrixLike() = default;
private:
    std::variant<
        DenseMatrixView<TN>, 
        SparseCSRMatrixView<TN>,
        SparseCSCMatrixView<TN>
    > _view = DenseMatrixView<TN>();
};

namespace like
{

template <typename TN>
struct MatrixLikeDefault : MatrixLike<TN> {};

}; // namespace seoncore::views::like

}; // namespace seoncore::views
