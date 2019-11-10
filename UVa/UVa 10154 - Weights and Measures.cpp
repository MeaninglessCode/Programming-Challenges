/*
I consulted https://reponroy.wordpress.com/tag/10154-weights-and-measures/
to better understand the problem.
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define int_pair std::pair<int, int>
constexpr int INF = 20000000;

int main()
{
    std::vector<int_pair> turtles;

    int w, s;
    while (std::cin >> w >> s && !(std::cin.fail()))
        turtles.push_back(int_pair(w, s));

    std::sort(turtles.begin(), turtles.end(), [](const int_pair &a, const int_pair &b)
    {
        return a.second < b.second;
    });

    std::vector<int> dp(turtles.size(), INF);

    dp[dp.size()] = INF;
    dp[0] = 0;

    for (int i = 0; i < dp.size(); i++)
    {
        for (int j = dp.size(); j >= 1; j--)
            if (dp[j - 1] + turtles[i].first <= turtles[i].second)
                dp[j] = std::min(dp[j], dp[j - 1] + turtles[i].first);
    }

    for (int i = dp.size(); i>= 0; i --)
    {
        if (dp[i] != INF)
        {
            std::cout << i << "\n";
            break;
        }
    }

    return 0;
}