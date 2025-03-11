module;
#include <cassert>
#include <algorithm>
#include <tuple>
export module Tarot.Sample:C1D;

import Tarot.Internal;
import Tarot.Random;

namespace Tarot
{

    TAROT_API template<FloatNumber NumT = Float, SamplableRNG RNG> auto
    SampleLinear(RNG& _U, NumT _a, NumT _b) -> NumT
    {
        // f(x) = (1-x)a + (x)b, where x \in [0,1] and b > a >= 0.
        assert(_a >= 0 && _b >= 0);

        NumT Xi = _U.template Uniform<NumT>();
        if (Xi == 0 && _a == 0) { return 0; }

        NumT Sample = Xi * (_a + _b)
                      /
                      (_a + std::sqrt(std::lerp(_a*_a, _b*_b, Xi)));
        return std::min(Sample, OneMinusEpsilon); // round-off error may cause the result to be equal to 1
    }

    TAROT_API template<FloatNumber NumT = Float, SamplableRNG RNG> auto
    SampleTent(RNG& _U) -> std::tuple<NumT, NumT>
    {
        // f(x) = r - |x| when |x| < r, otherwise f(x) = 0.
        assert(false);//WIP
        return {9, 9};
    }

} // namespace Tarot