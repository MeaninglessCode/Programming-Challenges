#include <iostream>
#include <vector>

void sieve_of_eratosthenes(const int &num_primes, std::vector<bool> &is_prime)
{
    for (int i = 2; i < num_primes; i++)
        if (!is_prime[i])
            for (int j = 2; i * j < num_primes; j++)
                is_prime[i * j] = true;
}

bool is_carmichael(const int &n)
{
    for (int i = 2; i <= n - 1; i++)
    {
        long x = i;
        long r = 1;
        long j = n;

        while (j)
        {
            if (j & 1)
            {
                r *= x;
                r %= n;
            }

            x = x * x;
            x %= n;

            j >>= 1;
        }

        if (r != i)
            return false;
    }

    return true;
}

int main()
{
    constexpr int num_primes = 65001;
    std::vector<bool> is_prime(num_primes, false);
    sieve_of_eratosthenes(num_primes, is_prime);

    int n;
    while (std::cin >> n && !(n == 0))
    {
        if (is_prime[n] && (is_carmichael(n) == 1))
            std::cout << "The number " << n << " is a Carmichael number.\n";
        else
            std::cout << n << " is normal.\n";
    }

    return 0;
}