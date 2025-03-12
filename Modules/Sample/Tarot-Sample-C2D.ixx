module;
#include <tuple>
export module Tarot.Sample:C2D;

import Tarot.Internal;
import Tarot.Random;

namespace Tarot
{

    TAROT_API template<UniformRNG RNG> auto
    SampleUnitSquare(RNG& _Ux, RNG& _Uy) -> Point2F
    {
        return { _Ux.template Uniform<Float>(), _Uy.template Uniform<Float>() };
    }

    TAROT_API template<UniformRNG RNG> auto
    SampleUnitHemisphere(RNG& _Utheta, RNG& _Uphi) -> Point3F
    {
        Float Theta  = std::acos(_Utheta.template Uniform<Float>());
        Float Phi    = 2.0 * Pi * _Uphi.template Uniform<Float>();
        Float X = std::sin(Phi) * std::cos(Theta);
        Float Y = std::sin(Phi) * std::sin(Theta);
        Float Z = std::cos(Theta);

        return {X, Y, Z};
    }

} // namespace Tarot