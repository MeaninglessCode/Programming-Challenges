#include <iostream>
#include <map>

std::map<char, char> alphabet_shift = {
    // First row
    {'1', '`'},
    {'2', '1'},
    {'3', '2'},
    {'4', '3'},
    {'5', '4'},
    {'6', '5'},
    {'7', '6'},
    {'8', '7'},
    {'9', '8'},
    {'0', '9'},
    {'-', '0'},
    {'=', '-'},
    // Second row
    //{'Q', '\t'},
    {'W', 'Q'},
    {'E', 'W'},
    {'R', 'E'},
    {'T', 'R'},
    {'Y', 'T'},
    {'U', 'Y'},
    {'I', 'U'},
    {'O', 'I'},
    {'P', 'O'},
    {'[', 'P'},
    {']', '['},
    {'\\', ']'},
    // Third row
    {'S', 'A'},
    {'D', 'S'},
    {'F', 'D'},
    {'G', 'F'},
    {'H', 'G'},
    {'J', 'H'},
    {'K', 'J'},
    {'L', 'K'},
    {';', 'L'},
    {'\'', ';'},
    // Fourth row
    {'X', 'Z'},
    {'C', 'X'},
    {'V', 'C'},
    {'B', 'V'},
    {'N', 'B'},
    {'M', 'N'},
    {',', 'M'},
    {'.', ','},
    {'/', '.'},
    // Preserve space
    {' ', ' '}
};

int main()
{
    std::string cur_line;

    while (std::getline(std::cin, cur_line) && cur_line != "")
    {
        std::string shifted;

        for (const char &c: cur_line)
            shifted += alphabet_shift[c];

        std::cout << shifted << "\n";
    }

    return 0;
}