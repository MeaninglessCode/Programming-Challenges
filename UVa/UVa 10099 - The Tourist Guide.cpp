/*
I consluted https://www.algorithmist.com/index.php/UVa_10099 to better
grasp the problem.
*/

#include <iostream>
#include <vector>
#include <algorithm>

struct bus_t
{
    bus_t(): src(-1), dest(-1), cap(-1) {}
    bus_t(int s, int d, int c): src(s), dest(d), cap(c) {}

    int src;
    int dest;
    int cap;
};

int get_group(const std::vector<int> &groups, int u)
{
    while (groups[u] != u)
        u = groups[u];

    return u;
}

int main()
{
    int case_num = 1;
    int N;
    int R;

    while (std::cin >> N >> R && !(N == 0 && R == 0))
    {
        std::vector<bus_t> buses;
        std::vector<int> g(N + 1);

        for (int i = 1; i <= N; ++i)
            g[i] = i;

        for (int i = 0; i < R; i++)
        {
            int s, d, c;
            std::cin >> s >> d >> c;
            c--;
            buses.push_back(bus_t(s, d, c));
        }

        std::sort(buses.begin(), buses.end(), [](const bus_t &b1, const bus_t &b2)
        {
            return b1.cap > b2.cap;
        });

        int S;
        int D;
        int T;

        std::cin >> S >> D >> T;

        for (int i = 0; i < R; i++)
        {
            bus_t &b = buses[i];
            int u = get_group(g, b.src);
            int v = get_group(g, b.dest);

            if (u != v)
            {
                g[v] = u;

                if (get_group(g, S) == get_group(g, D))
                {
                    std::cout << "Scenario #" << case_num << "\n";
                    case_num++;

                    int min_trips = (T + b.cap - 1) / b.cap;
                    std::cout << "Minimum Number of Trips = " << min_trips << "\n\n";

                    break;
                }
            }
        }
    }

    return 0;
}