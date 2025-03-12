module;
#include <random>
#include <type_traits>
export module Tarot.Random;
export import :MT19937;
export import :PCG;

import Tarot.Internal;

namespace Tarot
{
    TAROT_API template <typename T>
    concept UniformRNG = requires(T _RNG)
    {
        { _RNG.template Uniform<Float>() } -> std::same_as<Float>;
    };

    static_assert(UniformRNG<MT19937>);
    static_assert(UniformRNG<PCG>);

    TAROT_API
    template<RealNumber T> T
    Random()
    {
        static MT19937 RNG{GetRandomSeed()};//{static_cast<uint32_t>(std::time(nullptr))};
        return RNG.Uniform<T>();
    }

} // namespace Tarot