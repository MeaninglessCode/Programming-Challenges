/*
I consluted https://www.algorithmist.com/index.php/UVa_10004 to better
grasp the problem.
*/

#include <iostream>
#include <vector>

#define vec std::vector

void depth_first_search(vec<vec<int>> &g, int s, int c, vec<int> &color, bool &flag)
{
    if (color[s] != 0)
    {
        if (c != color[s])
            flag = false;
    }
    else
    {
        color[s] = c;

        for (int i = 0; i < g[s].size(); i++)
        {
            int new_color = (c == 1)? 2 : 1;
            depth_first_search(g, g[s][i], new_color, color, flag);
        }
    }
}

int main()
{
    int n;
    int e;

    while (std::cin >> n && !(n == 0))
    {
        std::cin >> e;
        vec<vec<int>> g(n);
        vec<int> color(n, 0);

        for (int i = 0; i < e; i++)
        {
            int a, b;
            std::cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        bool bicolorable = true;
        depth_first_search(g, 0, 1, color, bicolorable);

        std::cout << (bicolorable? "BICOLORABLE" : "NOT BICOLORABLE") << ".\n";
    }

    return 0;
}