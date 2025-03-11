/*
 * Reference: https://pbr-book.org/4ed/Sampling_and_Reconstruction/Sampling_Interface
 */

module;
#include <limits>
#include <cmath>
export module Tarot.Internal;

namespace Tarot
{

#if defined(TAROT_PRECISION_DOUBLE)
    export using Float = double;
#else
    export using Float = float;
#endif

    TAROT_API constexpr Float
    OneMinusEpsilon = 1.0 - std::numeric_limits<Float>::epsilon();

    TAROT_API template <typename T>
    concept RealNumber = std::is_arithmetic_v<T>; // Accepts both integral and floating-point types

    TAROT_API constexpr auto
    MixBits(uint64_t _V) -> uint64_t
    {
        _V ^= (_V >> 31);
        _V *= 0x7fb5d329728ea185;
        _V ^= (_V >> 27);
        _V *= 0x81dadef4bc2dd44d;
        _V ^= (_V >> 33);
        return _V;
    }

} // namespace Tarot