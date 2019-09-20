#include <iostream>
#include <vector>

constexpr char mine = '*';
constexpr char empty = '.';

int main()
{
    int n;
    int m;
    int field_num = 1;

    while (std::cin >> n >> m && n != 0 && m != 0)
    {
        // Added at your suggestion after I went to your office hours.
        if (field_num > 1)
            std::cout << "\n";

        std::vector<std::vector<char>> minefield(n + 2, std::vector<char>(m + 2, empty));

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                std::cin >> minefield[i][j];

        std::cout << "Field #" << field_num << ":\n";
        field_num++;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (minefield[i][j] == mine)
                    std::cout << mine;
                else
                {
                    int num_mines = 0;

                    for (int k = i - 1; k <= i + 1; k++)
                        for (int l = j - 1; l <= j + 1; l++)
                            if (minefield[k][l] == mine)
                                num_mines++;

                    std::cout << num_mines;
                }
            }

            std::cout << "\n";
        }
    }

    return 0;
}