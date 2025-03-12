module;
#include <concepts>
export module Tarot.Filter;
export import :C2D;

namespace Tarot
{

    TAROT_API template <typename T, typename PT>
    concept Filter = PhysicalPoint<PT> && requires(T _Filter, PT _Point)
    {
        { _Filter.Evaluate(_Point) } -> std::same_as<Float>;
        { _Filter.Integral() }       -> std::same_as<Float>;
    };

    static_assert(Filter<BoxFilter, Point2F>);

} // namespace Tarot