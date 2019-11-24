/*
I consulted https://blog.csdn.net/mobius_strip/article/details/49047887
to better understand the problem. Google translate was used to read the
text. Without consulting this website, I would have spent a much longer
time trying to discover the 1e-8 part of the calculation. That is
assuming I would have ever found out in the first place, however.
*/

#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    double L, W;

    while (std::cin >> L >> W && !std::cin.fail())
    {
        double max = (W + L - std::sqrt(L * L + W * W - L * W)) / 6;
        double min = std::min(W, L) / 2 + 1e-8;

        std::cout << std::fixed << std::setprecision(3) << max << " 0.000 " << min << "\n";
    }

    return 0;
}