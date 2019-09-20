#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

constexpr char unmatched = '*';
constexpr char char_offset = 97;

bool map_word(std::vector<char> &mapping, const std::string &entry, const std::string &target)
{
    std::vector<char> original_mapping(mapping);

    for (int i = 0; i < entry.length(); i++)
    {
        bool is_mapped = std::find(mapping.begin(), mapping.end(), entry[i]) != mapping.end();
        int index = target[i] - char_offset;

        if (mapping[index] == unmatched && !is_mapped || mapping[index] == entry[i])
            mapping[index] = entry[i];
        else
        {
            mapping.assign(original_mapping.begin(), original_mapping.end());
            return false;
        }
    }

    return true;
}

bool build_map(const std::vector<std::string> &dictionary, std::vector<char> &mapping, std::vector<std::string> &words, int index)
{
    if (index == words.size())
        return true;

    std::vector<char> original_mapping(mapping);

    for (const std::string &s: dictionary)
    {
        if (words[index].length() == s.length())
        {   
            if (map_word(mapping, s, words[index]))
            {
                if (build_map(dictionary, mapping, words, index + 1))
                    return true;

                mapping.assign(original_mapping.begin(), original_mapping.end());
            }
        }
    }

    return false;
}

std::string decrypt_string(const std::vector<std::string> &dictionary, const std::string &input)
{
    std::stringstream ss(input);
    std::vector<std::string> words{std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>()};

    std::vector<std::string> sorted_words(words);
    std::sort(sorted_words.begin(), sorted_words.end(), [](const std::string &a, const std::string &b)
    {
        return a.length() > b.length();
    });

    std::vector<char> char_mapping(26, unmatched);

    build_map(dictionary, char_mapping, sorted_words, 0);
    
    std::string decrypted;

    for (const std::string &s: words)
    {
        for (const char &c: s)
            decrypted += char_mapping[c - char_offset];
        decrypted += " ";
    }

    decrypted.pop_back();
    return decrypted;
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::string> dictionary(n);
    for (int i = 0; i < n; i++)
        std::cin >> dictionary[i];

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string current_line;
    while (std::getline(std::cin, current_line))
        std::cout << decrypt_string(dictionary, current_line) << "\n";

    return 0;
}