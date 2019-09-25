#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

int main()
{
    int num_cases;
    std::cin >> num_cases;
    bool first_case = true;

    while (num_cases--)
    {
        if (!first_case)
            std::cout << "\n";
        else
            first_case = false;

        int n;
        std::cin >> n;

        std::vector<int> times(n);

        for (int i = 0; i < n; i++)
            std::cin >> times[i];

        std::sort(times.begin(), times.end(), [](const int &i, const int &j)
        {
            return i < j;
        });

        int s = 0;
        int i;

        std::stringstream output;
        for (i = n - 1; i >= 3; i -= 2)
        {
            int a = times[0] + (times[1] *  2) + times[i];
            int b = (times[0] * 2) + times[i - 1] + times[i];

            if (a < b)
            {
                output << std::to_string(times[0]) + " " + std::to_string(times[1]) + "\n";
                output << std::to_string(times[0]) + "\n";
                output << std::to_string(times[i - 1]) + " " + std::to_string(times[i]) + "\n";
                output << std::to_string(times[1]) + "\n";

                s += a;
            }
            else
            {
                output << std::to_string(times[0]) + " " + std::to_string(times[i - 1]) + "\n";
                output << std::to_string(times[0]) + "\n";
                output << std::to_string(times[0]) + " " + std::to_string(times[i]) + "\n";
                output << std::to_string(times[0]) + "\n";

                s += b;
            }
        }

        if (i == 2)
        {
            output << std::to_string(times[0]) + " " + std::to_string(times[1]) + "\n";
            output << std::to_string(times[0]) + "\n";
            output << std::to_string(times[0]) + " " + std::to_string(times[2]) + "\n";

            s += times[0] + times[1] + times[2];
        }
        else if (i == 1)
        {
            output << std::to_string(times[0]) + " " + std::to_string(times[1]) + "\n";

            s += times[1];
        }
        else if (i == 0)
        {
            output << std::to_string(times[0]) + "\n";

            s += times[0];
        }

        std::cout << s << "\n";
        std::cout << output.str();
    }

    return 0;
}