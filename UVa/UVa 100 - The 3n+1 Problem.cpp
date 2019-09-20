/*
In solving this problem, I ended up consulting the following website:
https://www.mathblog.dk/uva-100-3n-plus-1-problem/
I was able to get a better understanding through the more in-depth explanation
here.
*/

#include <iostream>

int get_cycle_length(int n)
{
    int length = 1;

    while (n != 1)
    {
        if ((n & 1) == 0)
            n  = n >> 1;
        else
            n = (n * 3) + 1;
        
        length++;
    }

    return length;
}

int main()
{
    int lower;
    int upper;

    while (std::cin >> lower >> upper)
    {
        int max_length = 0;

        int lower_tmp = lower;
        int upper_tmp = upper;

        if (lower > upper)
            std::swap(upper, lower);

        while (lower <= upper)
        {
            int length = get_cycle_length(lower);

            if (length > max_length)
                max_length = length;

            lower++;
        }

        std::cout << lower_tmp << " " << upper_tmp << " " << max_length << std::endl;
    }

    return 0;
}
