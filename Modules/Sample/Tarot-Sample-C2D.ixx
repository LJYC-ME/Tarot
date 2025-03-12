module;
#include <tuple>
export module Tarot.Sample:C2D;

import Tarot.Internal;
import Tarot.Random;

namespace Tarot
{

    TAROT_API template<FloatNumber NumT = Float, UniformRNG RNG> auto
    SampleUnitSquare(RNG& _Ux, RNG& _Uy) -> Point2F<NumT>
    {
        return { _Ux.template Uniform<NumT>(), _Uy.template Uniform<NumT>() };
    }

    TAROT_API template<FloatNumber NumT = Float, UniformRNG RNG> auto
    SampleUnitHemisphere(RNG& _Utheta, RNG& _Uphi) -> Point3F<NumT>
    {
        NumT Theta  = std::acos(_Utheta.template Uniform<NumT>());
        NumT Phi    = 2.0 * Pi * _Uphi.template Uniform<NumT>();
        NumT X = std::sin(Phi) * std::cos(Theta);
        NumT Y = std::sin(Phi) * std::sin(Theta);
        NumT Z = std::cos(Theta);
        return { X, Y, Z };
    }

} // namespace Tarot