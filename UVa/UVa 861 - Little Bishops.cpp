#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n;
    int k;

    while (std::cin >> n >> k && !(n == 0 && k == 0))
    {
        if (k == 0 || n == 1)
        {
            std::cout << "1\n";
            continue;
        }

        std::vector<int> x1(20);
        std::vector<int> x2(20);

        int y1[20][20]{};
        int y2[20][20]{};

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if ((i + j) % 2)
                    x1[(i + j) / 2]++;
                else
                    x2[(i + j) / 2]++;
            }
        }

        std::sort(x1.begin(), x1.begin() + n - 1);
        std::sort(x2.begin(), x2.begin() + n);

        y1[0][0] = 1;
        y1[0][1] = x1[0];

        y2[0][0] = 1;
        y2[0][1] = x2[0];

        for (int i = 1; i < n - 1; i++)
        {
            y1[i][0] = 1;
            for (int j = 1; j <= x1[i]; j++)
                y1[i][j] = y1[i - 1][j] + y1[i - 1][j - 1] * (x1[i] - (j -1));
        }

        for (int i = 1; i < n; i++)
        {
            y2[i][0] = 1;
            for (int j = 1; j <= x2[i]; j++)
                y2[i][j] = y2[i - 1][j] + y2[i - 1][j - 1] * (x2[i] - (j - 1));
        }

        int res = 0;
        for (int i = 0; i <= k; i++)
            res += y1[n - 2][i] * y2[n - 1][k - i];

        std::cout << res << "\n";
    }

    return 0;
}