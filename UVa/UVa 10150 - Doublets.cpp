#include <iostream>
#include <vector>
#include <queue>
#include <map>

bool is_doublet(const std::string &a, const std::string &b)
{
    int diff = 0;

    for (int i = 0; i < a.length(); i++)
    {
        diff += ((a[i] == b[i])? 0 : 1);

        if (diff > 1)
            return false;
    }
    
    return (diff == 1);
}

int breadth_first_search(const int &s, const int &e, const std::vector<std::string> &dictionary, std::vector<int> &parent)
{
    std::queue<int> q;
    std::vector<std::pair<std::vector<int>, bool>> adjacency_list(dictionary.size());

    int p;
    int new_p;

    q.push(s);
    parent[s] = -9;

    while (q.size())
    {
        p = q.front();
        q.pop();

        if (p == e)
            return e;
        else if (adjacency_list[p].second)
        {
            for (int i = 0; i < adjacency_list[p].first.size(); i++)
            {
                if (parent[new_p = adjacency_list[p].first[i]] == -1)
                {
                    parent[new_p] = p;
                    q.push(new_p);
                }
            }
        }
        else
        {
            for (int i = 0; i < dictionary.size(); i++)
                if (dictionary[p].size() == dictionary[i].size() && is_doublet(dictionary[p], dictionary[i]))
                    adjacency_list[p].first.insert(adjacency_list[p].first.end(), i);

            adjacency_list[p].second = true;

            for (int i = 0; i < adjacency_list[p].first.size(); i++)
            {
                if (parent[new_p = adjacency_list[p].first[i]] == -1)
                {
                    parent[new_p] = p;
                    q.push(new_p);
                }
            }
        }
    }

    return -1;
}

int main()
{
    std::map<std::string, int> word_to_int;
    std::vector<std::string> dictionary;
    std::string cur_line;

    int bfs_result = 0;
    while (std::getline(std::cin, cur_line) && cur_line != "")
    {
        word_to_int[cur_line] = bfs_result++;
        dictionary.push_back(cur_line);
    }

    int case_num = 1;
    while (std::getline(std::cin, cur_line))
    {
        int split = cur_line.find(' ');
        std::string first = cur_line.substr(0, split);
        std::string second = cur_line.substr(split + 1, cur_line.length());

        std::vector<int> parent(dictionary.size(), -1);

        if (case_num > 1)
            std::cout << "\n";

        bool word_to_int_match = first.length() == second.length() && word_to_int.find(first) != word_to_int.end()
            && word_to_int.find(second) != word_to_int.end();

        if (word_to_int_match && (bfs_result = breadth_first_search(word_to_int[second], word_to_int[first], dictionary, parent)) != -1)
        {
            do
                std::cout << dictionary[bfs_result] << "\n";
            while ((bfs_result = parent[bfs_result]) != -9);
        }
        else
            std::cout << "No solution.\n";

        case_num++;
    }

    return 0;
}