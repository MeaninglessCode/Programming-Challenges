/*
I consulted https://topic.alibabacloud.com/a/uva-10271-chopsticks-dp_8_8_31544520.html
to better understand the problem.
*/

#include <iostream>
#include <vector>

int main()
{
    int T;
    std::cin >> T;

    while (T--)
    {
        int K, N;
        std::cin >> K >> N;

        // I was originally trying to size these arrays to be exactly as large as needed, but
        // I ended up making them the maximum size due to a runtime error and wanting to get this
        // finished.
        std::vector<int> min_cost(5001, 0);
        std::vector<int> seq_L(5001);
        std::vector<int> c(5001);

        K += 8;
        for (int i = N; i >= 1; i--)
            std::cin >> seq_L[i];

        for (int i = 2; i <= N; i++)
        {
            int tmp = seq_L[i] - seq_L[i - 1];
            c[i] = tmp * tmp;
        }

        for (int i = 1; i <= K; i++)
        {
            int m = 3 * i;
            for (int j = N; j >= m; j--)
            {
                min_cost[j] = min_cost[j - 2] + c[j];
            }
            for (int j = m + 1; j <= N; j++)
            {
                if (min_cost[j - 1] < min_cost[j])
                    min_cost[j] = min_cost[j - 1];
            }
        }

        std::cout << min_cost[N] << "\n";
    }

    return 0;
}