#include <iostream>

#include "solver.h"

int main()
{
    float a = 0;
    float b = 0;
    float c = 0;

    std::cin >> a >> b >> c;

    float x1 = 0;
    float x2 = 0;

    try
    {
        solve(a, b, c, x1, x2);

        std::cout << "x1 = " << x1 << std::endl;
        std::cout << "x2 = " << x2 << std::endl;
    }
    catch (const std::logic_error& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
