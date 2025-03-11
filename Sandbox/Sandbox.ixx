module;
#include <iostream>
//#include <random>
export module Sandbox;
import Tarot;
import Tarot.Internal;

export int main(int argc, char *argv[])
{

    std::cout << "Hello World!\n";

    Tarot::PCG rng1, rng2;
    rng1.SetSequence(std::time(0), std::time(0));

    for (int i = 0; i < 10; i++) {
        auto [x, y, z] = Tarot::SampleUnitHemisphere(rng1, rng2);
        //std::cout << x << ' ' << y << ' ' << z << '\n';
        std::cout << Tarot::SampleSegment(rng1, 20.0f, 30.0f) << '\n';
        //std::cout << Tarot::Random<float>() << '\n';
    }

    return 0;
}