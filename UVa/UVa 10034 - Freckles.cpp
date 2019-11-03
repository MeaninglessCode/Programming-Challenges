#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>

typedef struct
{
    int u;
    int v;
    double w;
} edge_t;

int get_parent(const std::vector<int> &g, int i)
{
    while (i != g[i])
        i = g[g[i]];

    return i;
}

int main()
{
    int num_cases;
    std::cin >> num_cases;
    std::cout << std::fixed << std::setprecision(2);

    while(num_cases--)
    {
        int n;
        std::cin >> n;

        std::vector<int> g(n);
        std::vector<edge_t> x(n * n);
        std::vector<std::pair<double, double>> dist(n);

        for (int i = 0; i < n; i++)
        {
            std::cin >> dist[i].first;
            std::cin >> dist[i].second;
        }

        int k = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                x[k].u = i;
                x[k].v = j;

                double a = dist[i].first - dist[j].first;
                double b = dist[i].second - dist[j].second;

                x[k].w= std::sqrt((a * a) + (b * b));
                k++;
            }
        }

        std::sort(x.begin(), x.begin() + k, [](const edge_t &a, const edge_t &b)
        {
            return a.w < b.w;
        });

        for (int i = 0; i < n; i++)
            g[i] = i;

        int d = 0;
        double mst = 0;

        for (int i = 0; i < k && d < n - 1; i++)
        {
            if (get_parent(g, x[i].u) != get_parent(g, x[i].v))
            {
                d++;
                g[get_parent(g, x[i].u)] = get_parent(g, x[i].v);
                mst = mst + x[i].w;
            }
        }

        std::cout << mst << "\n";

        if (num_cases)
            std::cout << "\n";
    }

    return 0;
}