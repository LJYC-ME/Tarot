/*
 * Reference: https://pbr-book.org/4ed/Sampling_and_Reconstruction/Sampling_Interface
 */

module;
#include <limits>
#include <cmath>
#include <vector>
#include <concepts>
#include <random>
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
    TAROT_API constexpr Float
    Pi = 3.14159265358979323846264338327950288;
    TAROT_API constexpr Float
    E  = 2.71828182845904523536028747135266250;
    TAROT_API template <typename T>
    concept IntegerNumber = std::is_integral_v<T>;
    TAROT_API template <typename T>
    concept FloatNumber = std::is_floating_point_v<T>;
    TAROT_API template <typename T>
    concept RealNumber = std::is_arithmetic_v<T>; // Accepts both integral and floating-point types
    TAROT_API using
    Point1F = Float;
    TAROT_API struct
    Point2F { union { Point1F Data[2]{0}; struct { Point1F X, Y; }; }; };
    TAROT_API struct
    Point3F { union { Point1F Data[3]{0}; struct { Point1F X, Y, Z; }; }; };
    TAROT_API using
    Point1I = int32_t;
    TAROT_API struct
    Point2I { union { Point1I Data[2]{0}; struct { Point1I X, Y; }; }; };
    TAROT_API struct
    Point3I { union { Point1I Data[3]{0}; struct { Point1I X, Y, Z; }; }; };
    TAROT_API using
    Point1U = uint32_t;
    TAROT_API struct
    Point2U { union { Point1U Data[2]{0}; struct { Point1U X, Y; }; }; };
    TAROT_API struct
    Point3U { union { Point1U Data[3]{0}; struct { Point1U X, Y, Z; }; }; };

    TAROT_API template <typename T>
    concept UniformRNG = requires(T _RNG)
    {
        { _RNG.template Uniform<Float>() } -> std::same_as<Float>;
    };

    TAROT_API template <FloatNumber T> bool
    IsNaN(T _Number) { return std::isnan(_Number); }
    TAROT_API template <IntegerNumber T> bool
    IsNaN(T _Number) { return false; }
    TAROT_API template <FloatNumber T> bool
    IsInfinite(T _Number) { return std::isinf(_Number); }
    TAROT_API template <IntegerNumber T> bool
    IsInfinite(T _Number) { return false; }
    TAROT_API template <FloatNumber T> bool
    IsFinite(T _Number) { return std::isfinite(_Number); }
    TAROT_API template <IntegerNumber T> bool
    IsFinite(T _Number) { return true; }

    TAROT_API template <RealNumber T> T
    FMA(T _a, T _b, T _c) { return std::fma(_a, _b, _c); }
    TAROT_API template <FloatNumber T> T
    GetNextFloat(T _Number) { return std::nextafter(_Number, +std::numeric_limits<T>::infinity()); }
    TAROT_API template <FloatNumber T> T
    GetPrevFloat(T _Number) { return std::nextafter(_Number, -std::numeric_limits<T>::infinity()); }

    TAROT_API inline auto
    GetRandomSeed() -> uint32_t
    {
        static std::random_device RandomDevice{};
        return RandomDevice();
    }

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