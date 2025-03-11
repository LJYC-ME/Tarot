/*
 * Reference: https://pbr-book.org/4ed/Utilities/Mathematical_Infrastructure#RNG
 */

module;
#include <random>
export module Tarot.Random:MT19937;

import Tarot.Internal;

namespace Tarot
{

    export class MT19937 // Mersenne Twister
    {
    public:
        template<RealNumber T = Float>
        T Uniform();

        MT19937(uint32_t _Seed = 0) : RNG{_Seed} {};

    private:
        std::mt19937 RNG;
    };

    template<> uint32_t MT19937::
    Uniform<uint32_t>()
    {
        static std::uniform_int_distribution<uint32_t> UniformUInt32Dist;
        return UniformUInt32Dist(RNG);
    }

    template<> uint64_t MT19937::
    Uniform<uint64_t>()
    {
        static std::uniform_int_distribution<uint64_t> UniformUInt64Dist;
        return UniformUInt64Dist(RNG);
    }

    template<> int32_t MT19937::
    Uniform<int32_t>()
    {
        static std::uniform_int_distribution<int32_t> UniformInt32Dist;
        return UniformInt32Dist(RNG);
    }

    template<> int64_t MT19937::
    Uniform<int64_t>()
    {
        static std::uniform_int_distribution<int64_t> UniformInt64Dist;
        return UniformInt64Dist(RNG);
    }

    template<> float MT19937::
    Uniform<float>()
    {
        static std::uniform_real_distribution<float> UniformFloatDist(0.0, 1 - std::numeric_limits<float>::epsilon());
        return UniformFloatDist(RNG);
    }

    template<> double MT19937::
    Uniform<double>()
    {
        static std::uniform_real_distribution<double> UniformDoubleDist(0.0, 1 - std::numeric_limits<double>::epsilon());
        return UniformDoubleDist(RNG);
    }

} // namespace Tarot