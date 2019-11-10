#include <iostream>
#include <limits>
#include <vector>

int main()
{
    int l;

    while(std::cin >> l && !(l == 0))
    {
        int n;
        std::cin >> n;

        std::vector<int> A(n + 2, 0);
        std::vector<std::vector<int>> cuts(n + 2, std::vector<int>(n + 2));

        for(int i = 1; i <= n; i++)
            std::cin >> A[i];

        n++;
        A[n] = l;

        for (int i = 2; i <= n; i++)
        {
            for (int j = 0, k = i + j; k <= n; j++, k++)
            {
                int min = std::numeric_limits<int>::max();

                for (int m = j + 1; m < k; m++)
                {
                    int tmp = cuts[j][m] + cuts[m][k] + A[k] - A[j];
                    if (min > tmp)
                        min = tmp;
                }

                cuts[j][k] = min;
            }
        }

        std::cout << "The minimum cutting is " << cuts[0][n] << ".\n";
    }

    return 0;
}