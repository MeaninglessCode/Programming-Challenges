/*
I consulted http://www.questtosolve.com/browse.php?pid=10044 to better
grasp the problem.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>

const std::string ERDOS_NAME = "Erdos,P.";

void breadth_first_search(std::map<std::string, int> &d, std::vector<std::vector<std::string>> &v)
{
    std::map<std::string, std::set<std::string>> connections;
    std::queue<std::string> q;

    q.push(ERDOS_NAME);
    d[ERDOS_NAME] = 0;

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            for (int k = j + 1; k < v[i].size(); k++)
            {
                connections[v[i][j]].insert(v[i][k]);
                connections[v[i][k]].insert(v[i][j]);
            }
        }
    }

    bool found = false;
    while (!q.empty())
    {
        std::string front = q.front();
        q.pop();

        int distance = d[front];
        for (std::set<std::string>::iterator it = connections[front].begin(); it != connections[front].end(); it++)
        {
            if (!d.count(*it))
            {
                q.push(*it);
                d[*it] = distance + 1;
            }
        }
    }
}

int main()
{
    int num_scenarios;
    int cur_scenario = 1;

    std::cin >> num_scenarios;

    while (num_scenarios--)
    {
        int num_papers;
        int num_authors;

        std::vector<std::vector<std::string>> v;
        std::string cur_line;
        std::string name;

        std::cin >> num_papers >> num_authors;
        std::getline(std::cin, cur_line);

        for (int i = 0; i < num_papers; i++)
        {
            std::getline(std::cin, cur_line);

            for (int j = 0; cur_line[j]; j++)
                if (cur_line[j] == ' ')
                    cur_line.erase(cur_line.begin() + j--);

            std::vector<std::string> vs;

            for (int j = 0, k = 0; ; j++)
            {
                if (cur_line[j] == ',' || cur_line[j] == ':')
                {
                    k++;

                    if (k == 2)
                    {
                        vs.push_back(name);
                        k = 0;
                        name.clear();

                        if (cur_line[j] == ':')
                            break;
                        continue;
                    }
                }

                name.insert(name.end(), cur_line[j]);
            }

            v.push_back(vs);
        }

        std::map<std::string, int> d;
        breadth_first_search(d, v);

        std::cout << "Scenario " << cur_scenario << "\n";
        cur_scenario++;

        for (int i = 0; i < num_authors; i++)
        {
            std::getline(std::cin, cur_line);
            name = cur_line;

            for (int j = 0; cur_line[j]; j++)
                if (cur_line[j] == ' ')
                    cur_line.erase(cur_line.begin() + j--);

            std::cout << name << " " << ((d.count(cur_line)? std::to_string(d[cur_line]): "infinity")) << "\n";
        }
    }

    return 0;
}