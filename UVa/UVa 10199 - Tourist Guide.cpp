#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <limits>

#define vec std::vector
#define str std::string
#define str_set std::set<str>

int depth_first_search(const vec<vec<int>> &G, str_set &cameras, const vec<str> &names, vec<int> &depth,
    vec<int> &visited, int nd, int cur_depth, int p, int root)
{
    depth[nd] = cur_depth;
    visited[nd] = 1;

    int a = std::numeric_limits<int>::max();
    int b = 0;
    bool flag = false;

    for (int i = 0; i < G[nd].size(); i++)
    {
        if (visited[G[nd][i]] == 0)
        {
            int tmp = depth_first_search(G, cameras, names, depth, visited, G[nd][i], cur_depth + 1, nd, root);

            if (tmp >= cur_depth)
                flag = true;

            b++;
            a = std::min(a, tmp);
        }
        else
        {
            if (G[nd][i] != p)
                a = std::min(a, depth[G[nd][i]]);
        }
    }
    if ((nd == root && b > 1) || (nd != root && flag))
        cameras.insert(names[nd]);

    return a;
}

int main()
{
    int case_num = 1;
    int N;

    while (std::cin >> N && !(N == 0))
    {
        vec<vec<int>> G(N + 5);
        std::map<str, int> routes;
        str_set cameras;

        vec<str> names(N + 5);
        vec<int> visited(N + 5);
        vec<int> depth(N + 5);

        for (int i = 0; i < N; i++)
        {
            std::cin >> names[i];
            routes[names[i]] = i;
            visited[i] = depth[i] = 0;
        }

        int M;
        std::cin >> M;

        while (M--)
        {
            str tmp;

            std::cin >> tmp;
            int a = routes[tmp];

            std::cin >> tmp;
            G[a].push_back(routes[tmp]);
            G[routes[tmp]].push_back(a);
        }

        for (int i = 0; i < N; i++)
        {
            if (visited[i] == 0)
                depth_first_search(G, cameras, names, depth, visited, i, 1, -1, i);
        }

        if (case_num > 1)
            std::cout << "\n";

        std::cout << "City map #" << case_num << ": " << cameras.size() << " camera(s) found\n";
        case_num++;

        for (const str &s: cameras)
            std::cout << s << "\n";
    }

    return 0;
}