#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int num_cases;
    std::cin >> num_cases;

    while (num_cases--)
    {
        int n;
        std::cin >> n;

        std::vector<int> relatives(n);

        for (int i = 0; i < n; i++)
            std::cin >> relatives[i];

        std::sort(relatives.begin(), relatives.end(), [](const int &i, const int &j)
        {
            return i < j;
        });

        int median = relatives[n / 2];
        int ans = 0;

        for (const int &i: relatives)
            ans += std::abs(median - i);

        std::cout << ans << "\n";
    }

    return 0;
}