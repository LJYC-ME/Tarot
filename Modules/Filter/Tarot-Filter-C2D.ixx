module;
#include <cmath>
export module Tarot.Filter:C2D;

import Tarot.Internal;
import Tarot.Random;

namespace Tarot
{

    TAROT_API class BoxFilter
    {
    public:
        auto Evaluate(Point2F _P)                   const -> Float   { return (std::abs(_P.X) <= Radius.X && std::abs(_P.Y) <= Radius.Y) ? 1.0 : 0.0; }
        auto Integral()                             const -> Float   { return 2 * Radius.X *  2 * Radius.Y; }

        template<UniformRNG U>
        auto Sample(U& _Ux, U& _Uy, Float* Weight_) const -> Point2F
        {   *Weight_ = 1.0;
            return { std::lerp(-Radius.X,+Radius.X, _Ux.template Uniform<Float>()),
                     std::lerp(-Radius.Y,+Radius.Y, _Uy.template Uniform<Float>())};
        }

        auto GetRadius() const -> const Point2F& { return Radius; }

    private:
        Point2F Radius{0.0, 0.0};
    };

} // namespace Tarot