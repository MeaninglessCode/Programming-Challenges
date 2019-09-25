#include <iostream>
#include <vector>
#include <sstream>

int main()
{
    std::string cur_line;

    while (std::getline(std::cin, cur_line))
    {
        std::stringstream ss(cur_line);
        std::vector<int> pancake;
        int n;
        int m;
        int flips = 0;

        while (ss >> n)
            pancake.push_back(n);
        n = pancake.size();

        std::vector<int> flip(n * 2);

        for (int i = 0; i < n; i++)
            std::cout << pancake[i] << ((i == n - 1)? "\n": " ");

        for (int i = 0; i < n; i++)
        {
            int p = n - i - 1;
            for (int j = 0; j < n - i; j++)
                if (pancake[p] < pancake[j])
                    p = j;

            if (p == n - i - 1)
                continue;
            else if (p)
            {
                flip[flips++] = n - p;
                for (int j = 0, k = p; j < k; j++, k--)
                    std::swap(pancake[j], pancake[k]);
            }

            flip[flips++] = i + 1;
            for (int j = 0, k = n - i - 1; j < k; j++, k--)
                std::swap(pancake[j], pancake[k]);
        }

        for (int i = 0; i < flips; i++)
            std::cout << flip[i] << " ";
        std::cout << "0\n";
    }

    return 0;
}