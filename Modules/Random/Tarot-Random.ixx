module;
#include <random>
#include <type_traits>
export module Tarot.Random;
export import :MT19937;
export import :RNG;

import Tarot.Internal;

namespace Tarot
{
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