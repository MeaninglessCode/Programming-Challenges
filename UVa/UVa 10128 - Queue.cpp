#include <iostream>
#include <vector>

#define vec std::vector
#define vll std::vector<long long>

int main()
{
    vec<vec<vll>> data(17, vec<vll>(17, vll(17, 0)));
    data[1][1][1] = 1;

    for (int i = 2; i <= 13; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            for (int k = 1; k <= i; k++)
            {
                data[i][j][k] = data[i - 1][j][k] * (i - 2);
                data[i][j][k] += data[i - 1][j - 1][k] + data[i - 1][j][k - 1];
            }
        }
    }

    int t;
    std::cin >> t;

    int n;
    int p;
    int r;

    while (t--)
    {
        std::cin >> n >> p >> r;
        std::cout << data[n][p][r] << "\n";
    }

    return 0;
}