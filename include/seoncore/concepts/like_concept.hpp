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
concept IsMatrix = requires(const std::remove_cvref_t<_ToCheck>& x)
{
    typename std::remove_cvref_t<_ToCheck>::value_type;

    { x.rows() } -> std::convertible_to<std::size_t>;
    { x.cols() } -> std::convertible_to<std::size_t>;
    
    { x(0, 0) } -> std::convertible_to<typename std::remove_cvref_t<_ToCheck>::value_type>;

    requires ConvertibleToAny<
        decltype(x.norm_p(std::size_t{2})),
        typename std::remove_cvref_t<_ToCheck>::value_type,
        double, long double, int, long long
    >;
};

}; // namespace seoncore::concepts
