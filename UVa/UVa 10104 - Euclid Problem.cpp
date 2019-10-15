#include <iostream>

int main()
{
    int A;
    int B;

    while (std::cin >> A >> B)
    {
        bool flag = false;

        int x_1 = 1, x_2 = 0;
        int y_1 = 0, y_2 = 1;

        while(A % B)
        {
            int tmp = A / B;

            if (flag)
            {
                x_2 -= tmp * x_1;
                y_2 -= tmp * y_1;
            }
            else
            {
                x_1 -= tmp * x_2;
                y_1 -= tmp * y_2;
            }

            std::swap(A, B);
            B %= A;
            flag = !flag;
        }

        if (flag)
            std::cout << x_1 << " " << y_1;
        else
            std::cout << x_2 << " " << y_2;
        
        std::cout << " " << B << "\n";
    }

    return 0;
}