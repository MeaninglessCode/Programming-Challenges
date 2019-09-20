#include <iostream>
#include <vector>
#include <map>

const std::string key = "the quick brown fox jumps over the lazy dog";

std::pair<std::map<char, char>, bool> get_char_mapping(const std::string &s)
{
    std::map<char, char> char_map;
    std::map<char, char> tmp_map;

    if (s.length() != key.length())
        return std::pair<std::map<char, char>, bool>(char_map, false);

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            if (key[i] != ' ')
                return std::pair<std::map<char, char>, bool>(char_map, false);
        }
        else if (char_map.count(s[i]) > 0)
        {
            if (char_map[s[i]] != key[i])
                return std::pair<std::map<char, char>, bool>(char_map, false);
        }
        else if (tmp_map.count(key[i]) > 0)
        {
            if (tmp_map[key[i]] != s[i])
                return std::pair<std::map<char, char>, bool>(char_map, false);
        }
        else
        {
            char_map[s[i]] = key[i];
            tmp_map[key[i]] = s[i];
        }
    }

    char_map.insert(std::pair<char, char>(' ', ' '));
    return std::pair<std::map<char, char>, bool>(char_map, true);
}

int main()
{
    int n;
    std::cin >> n;

    std::string cur_line;
    std::getline(std::cin, cur_line);
    std::getline(std::cin, cur_line);

    for (int i = 0 ; i < n; i++)
    {
        if (i > 0)
            std::cout << "\n";

        std::pair<std::map<char, char>, bool> result;
        std::vector<std::string> input;

        while (std::getline(std::cin, cur_line) && cur_line != "")
        {
            input.push_back(cur_line);

            if (!result.second)
                result = get_char_mapping(cur_line);
        }

        if (!result.second)
            std::cout << "No solution.\n";
        else
        {
            std::string decoded;

            for (const std::string &s: input)
            {
                for (const char &c: s)
                    decoded += result.first[c];

                decoded += '\n';
            }

            std::cout << decoded;
        }
    }

    return 0;
}