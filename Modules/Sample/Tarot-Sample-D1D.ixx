module;
export module Tarot.Sample:D1D;

import Tarot.Internal;
import Tarot.Random;

namespace Tarot
{

    TAROT_API template<FloatNumber NumT = Float, UniformRNG RNG> auto
    SampleDiscrete(RNG& _U, NumT _a, NumT _b) -> Point1F
    {
        return 1;
    }

} // namespace Tarot