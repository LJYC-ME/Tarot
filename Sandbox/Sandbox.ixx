module;
#include <iostream>
//#include <random>
export module Sandbox;
import Tarot;
import Tarot.Internal;

export int main(int argc, char *argv[])
{

    std::cout << "Hello World!\n";

    Tarot::PCG rng;
    std::cout<< Tarot::GetNextFloat(.0f) << '\n';
    std::cout<< Tarot::GetPrevFloat(.0f) << '\n';
    std::vector<Tarot::Float> Vars{0.2, 0.1, 0.5, 0.2};
    Tarot::Index Sets[4]{0,0,0,0};
    for (int i = 0; i < 10000; ++i)
    Sets[Tarot::SampleDiscrete(Vars.data(), Vars.size(), rng)]++;
    for (int i = 0; i < 4; ++i) {
        std::cout << Sets[i]/10000.0 << '\n';
    }

    for (int i = 0; i < 10; i++) {
        auto V = Tarot::SampleUnitHemisphere(rng, rng);
        //std::cout << V.X << " " << V.Y << " " << V.Z << std::endl;
        //std::cout << x << ' ' << y << ' ' << z << '\n';
        //std::cout << Tarot::SampleLinear(rng, 20.0f, 30.0f) << '\n';
        //std::cout << Tarot::Random<float>() << '\n';
    }

    return 0;
}