module;
#include <algorithm>
#include <tuple>
export module Tarot.Sample:C1D;

import Tarot.Internal;
import Tarot.Random;

namespace Tarot
{

    TAROT_API template<UniformRNG RNG> auto
    SampleLinear(RNG& _U, Float _a, Float _b) -> Point1F
    {
        // f(x) = (1-x)a + (x)b, where x \in [0,1] and b > a >= 0.
        Assert(_a >= 0 && _b >= 0);

        Float Xi = _U.template Uniform<Float>();
        if (Xi == 0 && _a == 0) { return 0; }

        Float Sample = Xi * (_a + _b)
                      /
                      (_a + std::sqrt(std::lerp(_a*_a, _b*_b, Xi)));
        return std::min(Sample, OneMinusEpsilon); // round-off error may cause the result to be equal to 1
    }

    TAROT_API template<UniformRNG RNG> auto
    SampleTent(RNG& _U) -> Point2F
    {
        // f(x) = r - |x| when |x| < r, otherwise f(x) = 0.
        Assert(false);//WIP
        return {9, 9};
    }

} // namespace Tarot