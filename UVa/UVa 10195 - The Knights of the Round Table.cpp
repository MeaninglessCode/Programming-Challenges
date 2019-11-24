#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    double a, b, c;

    while (std::cin >> a >> b >> c && !std::cin.fail())
    {
        if (a == 0 || b == 0 || c == 0)
            std::cout << "The radius of the round table is: 0.000\n";
        else
        {
            double d = (a + b + c) / 2;
            std::cout << std::fixed << std::setprecision(3) << "The radius of the round table is: "
                << (std::sqrt(d * (d - a) * (d - b) * (d - c))) / d << "\n";
        }
    }

    return 0;
}