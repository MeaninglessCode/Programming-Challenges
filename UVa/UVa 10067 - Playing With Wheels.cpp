#include <iostream>
#include <map>
#include <queue>

int get_offset(int a, int b)
{
    if ((a == 0 && b == 0) || (a == 2 && b == 1) || (a == 4 && b == 2) || (a == 6 && b == 3))
        return 1;
    else if ((a == 1 && b == 0) || (a == 3 && b == 1) || (a == 5 && b == 2) || (a == 7 && b == 3))
        return -1;
    else
        return 0;
}

int breadth_first_search(std::map<std::string, int> g, std::string s, std::string e)
{
    if (s == e)
        return 0;
    if (g[s] == -1)
        return -1;

    std::queue<std::string> q;
    std::queue<int> r;

    q.push(s);
    r.push(1);

    while (!q.empty())
    {
        std::string u = q.front();
        q.pop();

        int v = r.front();
        r.pop();

        for (int i = 0; i < 8; i++)
        {
            std::string w = u;

            for (int j = 0; j < 4; j++)
            {
                w[j] += get_offset(i, j);
                
                if (w[j] < '0')
                    w[j] = '9';
                else if (w[j] > '9')
                    w[j] = '0';
            }

            int j = g[w];

            if (j != 0)
                continue;
            if (w == e)
                return v;
            
            j = g[w] = v + 1;

            q.push(w);
            r.push(j);
        }
    }

    return -1;
}

int main()
{
    int num_cases;
    std::cin >> num_cases;

    while (num_cases--)
    {
        std::string s;
        std::string e;
        std::map<std::string, int> g;

        int v;
        int m;

        for (int i = 0; i < 4; i++)
        {
            std::cin >> v;
            s += v + 48;
        }

        for (int i = 0; i < 4; i++)
        {
            std::cin >> v;
            e += v + 48;
        }

        std::cin >> m;
        while (m--)
        {
            std::string t = "";

            for (int i = 0; i < 4; i++)
            {
                std::cin >> v;
                t += v + 48;
            }

            g[t] = -1;
        }

        g[s] = 1;
        std::cout << breadth_first_search(g, s, e) << "\n";
    }

    return 0;
}