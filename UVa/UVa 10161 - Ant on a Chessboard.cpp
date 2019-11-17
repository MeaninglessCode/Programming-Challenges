#include <iostream>

int main()
{
    int N;

    while (std::cin >> N && !(N == 0))
    {
        int i = 1;
        int j = 2;
        int k = 1;

        while (true)
        {
            if (abs(i - N) < k)
                break;

            i += j;
            j += 2;
            k++;
        }

        std::pair<int, int> res(k, k);
        
        if (k & 1)
            (N > i)? res.first -= (N - i): res.second -= (i - N);
        else
            (N > i)? res.second -= (N - i): res.first -= (i - N);

        std::cout << res.first << " " << res.second << "\n";
    }

    return 0;
}