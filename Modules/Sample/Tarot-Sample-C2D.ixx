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

    TAROT_API template<RealNumber NumT = Float, SamplableRNG RNG> auto
    SampleHemisphere(RNG& _Utheta, RNG& _Uphi) -> std::tuple<NumT, NumT, NumT>
    {
        NumT Theta  = std::acos(_Utheta.template Uniform<NumT>());
        NumT Phi    = 2.0 * Pi * _Uphi.template Uniform<NumT>();
        NumT X = std::sin(Phi) * std::cos(Theta);
        NumT Y = std::sin(Phi) * std::sin(Theta);
        NumT Z = std::cos(Theta);
        return { X, Y, Z };
    }

} // namespace Tarot