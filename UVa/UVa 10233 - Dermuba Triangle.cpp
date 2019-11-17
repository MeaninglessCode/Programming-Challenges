/*
I consulted https://blog.csdn.net/a15110103117/article/details/66474035
to better understand the problem. Google translate was used to read the
text.
*/

#include <iostream>
#include <iomanip>
#include <cmath>

#define double_pair std::pair<double, double>

double_pair get_pair(int n, long long l)
{
    if (n == 0)
        return double_pair(0, 0);

    double tmp = (l * l + (l + 1) * (l + 1) - 1) / 2;
    double x = (tmp == n)? 0: 0.5 * (n - tmp);

    tmp = 1 + 3 * (l - 1);
    tmp += ((int)(l * l - n) % 2 == 0)? 2: 1;
    double y = (std::sqrt(3) / 6) * tmp;

    return double_pair(x, y);
}

int main()
{
    int n;
    int m;

    while (std::cin >> n >> m && !std::cin.fail())
    {
        double_pair n_pair = get_pair(n, std::sqrt(n));
        double_pair m_pair = get_pair(m, std::sqrt(m));

        double x = n_pair.first - m_pair.first;
        double y = n_pair.second - m_pair.second;

        std::cout << std::fixed <<  std::setprecision(3) << std::sqrt(x * x + y * y) << "\n";
    }

    return 0;
}