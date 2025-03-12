module;
#include <numeric>
export module Tarot.Sample:D1D;

import Tarot.Internal;
import Tarot.Random;

namespace Tarot
{

    TAROT_API template<FloatNumber NumT = Float, UniformRNG RNG> auto
    SampleDiscrete(const Float _Weights[], Index _WeightCounts, RNG& _U) -> Index
    {
        if (_WeightCounts == 0)
        {
            return InvalidIndex;
        }

        Float WeightSum = std::accumulate(_Weights, _Weights + _WeightCounts, 0.0);

        Assert(WeightSum <= 1.0);

        Float U = _U.template Uniform<Float>();
        Float Interval = U * WeightSum;
        if (Interval  == WeightSum)
        { Interval = GetPrevFloat(Interval); }

        Index Offset = 0;
        Float Sum = 0.0;
        while (Sum + _Weights[Offset] <= Interval)
        { Sum += _Weights[Offset++]; }

        return Offset;
    }

} // namespace Tarot