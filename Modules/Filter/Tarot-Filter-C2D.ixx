module;
#include <cmath>
export module Tarot.Filter:C2D;

import Tarot.Internal;

namespace Tarot
{

    TAROT_API class BoxFilter
    {
    public:
        auto GetRadius() const -> const Point2F& { return Radius; }
        auto Evaluate(Point2F _P) const -> Float { return (std::abs(_P.X) <= Radius.X && std::abs(_P.Y) <= Radius.Y) ? 1.0 : 0.0; }
        auto Integral() const -> Float { return 2 * Radius.X *  2 * Radius.Y; }

    private:
        Point2F Radius{0.0, 0.0};
    };

} // namespace Tarot