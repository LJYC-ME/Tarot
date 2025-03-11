module;
#include <tuple>
export module Tarot.Sample:C2D;

import Tarot.Internal;
import Tarot.Random;

namespace Tarot
{

    TAROT_API template<RealNumber NumT = Float, SamplableRNG RNG> auto
    SampleSquare(RNG& _Ux, RNG& _Uy) -> std::tuple<NumT, NumT>
    {
        return { _Ux.template Uniform<NumT>(), _Uy.template Uniform<NumT>() };
    }

} // namespace Tarot