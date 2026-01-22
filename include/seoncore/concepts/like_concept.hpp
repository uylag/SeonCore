#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace seoncore::concepts
{

template <class _From, class... _To>
concept ConvertibleToAny = (std::convertible_to<_From, _To> || ...);

template <class _ToCheck>
concept MatrixBased = requires(const _ToCheck& x)
{
    typename std::remove_cvref_t<_ToCheck>::value_type;

    { x.rows() }    -> std::convertible_to<std::size_t>;
    { x.cols() }    -> std::convertible_to<std::size_t>;

    { x(0, 0) }     -> std::convertible_to<typename std::remove_cvref_t<_ToCheck>::value_type>; 
}; // concept MatrixBased<_ToCheck>

template <class _ToCheck>
concept VectorBased = requires(const _ToCheck& x)
{
    typename std::remove_cvref_t<_ToCheck>::value_type;

    { x.size() }    -> std::convertible_to<std::size_t>;
    { x[0] }        -> std::convertible_to<typename std::remove_cvref_t<_ToCheck>::value_type>;
}; // concept VectorBased<_ToCheck>

template <class _ToCheck>
concept IsDense = requires(const std::remove_cvref_t<_ToCheck>& x)
{
    typename std::remove_cvref_t<_ToCheck>::value_type;

    { x.rows() } -> std::convertible_to<std::size_t>;
    { x.cols() } -> std::convertible_to<std::size_t>;
    
    { x(0, 0) } -> std::convertible_to<typename std::remove_cvref_t<_ToCheck>::value_type>;

    { x.stride_row() } -> std::convertible_to<std::size_t>;
    { x.stride_col() } -> std::convertible_to<std::size_t>; 
}; // concept IsDense<_ToCheck>

template <class _ToCheck>
concept IsSparse = requires(const std::remove_cvref_t<_ToCheck>& x)
{
    typename std::remove_cvref_t<_ToCheck>::value_type;

    { x.rows() } -> std::convertible_to<std::size_t>;
    { x.cols() } -> std::convertible_to<std::size_t>;
    
    { x(0, 0) } -> std::convertible_to<typename std::remove_cvref_t<_ToCheck>::value_type>;

    { x.nnz() } -> std::convertible_to<std::size_t>;
}; // concept IsDense<_ToCheck>

}; // namespace seoncore::concepts
