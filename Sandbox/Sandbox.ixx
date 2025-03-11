module;
#include <iostream>
export module Sandbox;
import Tarot;
import Tarot.Internal;

struct Foo
{
};

export int main(int argc, char *argv[])
{
    std::cout << "Hello World!\n";

    auto PCG = Tarot::PCG{};
    for (int i = 0; i < 10; i++)
    std::cout << PCG.Uniform<int>() << std::endl;
    auto MT = Tarot::MT19937{};

std::cout << '\n';

    for (int i = 0; i < 10; i++)
        std::cout << MT.Uniform() << std::endl;
    return 0;
}