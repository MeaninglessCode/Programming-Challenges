#include <iostream>
#include <cmath>

int main()
{
    unsigned int n;

    while (std::cin >> n && !(n == 0))
        std::cout << ((pow((int)sqrt(n), 2) == n)? "yes\n": "no\n");

    return 0;
}