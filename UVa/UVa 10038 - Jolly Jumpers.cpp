#include <iostream>
#include <vector>

int main()
{
    int case_num = 1;
    int n;

    while (std::cin >> n)
    {
        std::vector<int> sequence(n);

        for (int i = 0; i < n; i++)
            scanf("%d", &sequence[i]);

        std::vector<bool> jumps(n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            int abs_diff = std::abs(sequence[i] - sequence[i + 1]);

            if (abs_diff < n && abs_diff > 0)
                jumps[abs_diff - 1] = true;
        }

        bool is_jolly = true;
        for (const bool &jolly_jump: jumps)
            if (!jolly_jump)
                is_jolly = false;

        std::cout << ((is_jolly)? "Jolly\n" : "Not jolly\n");
    }

    return 0;
}