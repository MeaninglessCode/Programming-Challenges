#include <iostream>
#include <vector>
#include <algorithm>

auto comparator = [](const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    if (a.first != b.first)
        return (b.first - a.first) <= 0;
    else
        return (a.second - b.second) <= 0;
};

int main()
{
    int M;
    int N;

    while(std::cin >> M >> N && !(M == 0 && N == 0))
    {
        std::vector<std::pair<int, int>> seq_m(M);
        std::vector<std::pair<int, int>> seq_n(N);
        std::vector<int> seq_i(M);
        std::vector<std::vector<int>> res(70, std::vector<int>(70));

        for (int i = 0; i < M; i++)
        {
            std::cin >> seq_m[i].first;
            seq_m[i].second = i;
            seq_i[i] = seq_m[i].first;
        }

        for (int i = 0; i < N; i++)
        {
            std::cin >> seq_n[i].first;
            seq_n[i].second = i;
        }

        std::sort(seq_m.begin(), seq_m.end(), comparator);

        int i;
        for (i = 0; i < M; i++)
        {
            std::sort(seq_n.begin(), seq_n.end(), comparator);

            int a = seq_m[i].first;
            int b = 0;
            bool flag = false;

            for (int j = 0; j < N; j++)
            {
                if (a != 0)
                {
                    if (seq_n[j].first == 0)
                        flag = true;
                    else
                    {
                        seq_n[j].first--;
                        res[seq_m[i].second][b] = seq_n[j].second;
                        
                        a--;
                        b++;
                    }
                }
            }

            if (flag || a)
                break;
        }

        if (i == M)
        {
            std::cout << "1\n";

            for (i = 0; i < M; i++)
            {
                std::sort(res[i].begin(), res[i].begin() + seq_i[i], [](const int &a, const int &b)
                {
                    return (a - b) <= 0;
                });

                for (int j = 0; j < seq_i[i]; j++)
                    std::cout << ((j != 0)? " " : "") << res[i][j] + 1;

                std::cout << "\n";
            }
        }
        else
            std::cout << "0\n";
    }

    return 0;
}