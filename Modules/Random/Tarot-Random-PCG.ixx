/*
 * Reference: https://pbr-book.org/4ed/Utilities/Mathematical_Infrastructure#RNG
 */

module;
#include <cassert>
#include <algorithm>
#include <__random/random_device.h>
export module Tarot.Random:RNG;

import Tarot.Internal;

namespace Tarot
{

    TAROT_API class PCG
    {
        static constexpr auto PCG32DefaultState  = 0x853c49e6748fea9bULL;
        static constexpr auto PCG32DefaultStream = 0xda3e39cb94b95bdbULL;
        static constexpr auto PCG32Multiplier    = 0x5851f42d4c957f2dULL;

    public:
        template<RealNumber T = Float>
        T Uniform();

        void SetSequence(uint64_t _SequenceIndex, uint32_t _Seed);

        PCG(uint64_t _SequenceIndex = GetRandomSeed(), uint32_t _Seed = GetRandomSeed()) { SetSequence(_SequenceIndex, _Seed); }

    private:
        uint64_t State  {PCG32DefaultState};
        uint64_t Stream {PCG32DefaultStream};
    };

    template<> uint32_t PCG::
    Uniform<uint32_t>()
    {
        uint64_t oldstate = State;
        State = oldstate * PCG32Multiplier + PCG32DefaultStream;
        auto xorshifted = static_cast<uint32_t>(((oldstate >> 18u) ^ oldstate) >> 27u);
        auto rot        = static_cast<uint32_t>(oldstate >> 59u);
        return (xorshifted >> rot) | (xorshifted << ((~rot + 1u) & 31));
    };

    template<> uint64_t PCG::
    Uniform<uint64_t>()
    {
        uint64_t v0 = Uniform<uint32_t>();
        uint64_t v1 = Uniform<uint32_t>();
        return (v0 << 32) | v1;
    };

    template<> int32_t PCG::
    Uniform<int32_t>()
    {
        // https://stackoverflow.com/a/13208789
        uint32_t v = Uniform<uint32_t>();
        if (v <= (uint32_t)std::numeric_limits<int32_t>::max())
            return int32_t(v);
        assert(v >= (uint32_t)std::numeric_limits<int32_t>::min());
        return int32_t(v - std::numeric_limits<int32_t>::min()) +
               std::numeric_limits<int32_t>::min();
    };

    template<> int64_t PCG::
    Uniform<int64_t>()
    {
        // https://stackoverflow.com/a/13208789
        uint64_t v = Uniform<uint64_t>();
        if (v <= (uint64_t)std::numeric_limits<int64_t>::max())
            // Safe to type convert directly.
                return int64_t(v);
        assert(v >= (uint64_t)std::numeric_limits<int64_t>::min());
        return int64_t(v - std::numeric_limits<int64_t>::min()) +
               std::numeric_limits<int64_t>::min();
    };

    template<> float PCG::
    Uniform<float>()
    {
        return std::min<float>(OneMinusEpsilon, Uniform<uint32_t>() * 0x1p-32f);
    };

    template<> double PCG::
    Uniform<double>()
    {
        return std::min<double>(OneMinusEpsilon, Uniform<uint64_t>() * 0x1p-64);
    };

    void PCG::
    SetSequence(uint64_t _SequenceIndex/* = GetRandomSeed() */,
                uint32_t _Seed         /* = GetRandomSeed() */)
    {
        // _SequenceIndex = _SequenceIndex? _SequenceIndex : GetRandomSeed();
        // _Seed = _Seed? _Seed : GetRandomSeed();

        State = 0u;
        Stream = (_SequenceIndex << 1u) | 1u;
        Uniform<uint32_t>();
        State += _Seed;
        Uniform<uint32_t>();
    }

} // namespace Tarot