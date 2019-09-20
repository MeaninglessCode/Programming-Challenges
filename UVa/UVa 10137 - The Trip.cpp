#include <iostream>
#include <iomanip>
#include <vector>

int main()
{
    int num_students;

    while (std::cin >> num_students && num_students > 0)
    {
        std::vector<int> costs(num_students);

        int sum = 0;
        int sum_under = 0;
        int sum_over = 0;

        for (int i = 0; i < num_students; i++)
        {
            int dollars;
            int cents;
            char delim;

            std::cin >> dollars >> delim >> cents;

            costs[i] = dollars * 100 + cents;
            sum += costs[i];
        }

        int avg = sum / num_students;
        int avg_high = avg;

        if (sum % num_students != 0)
            avg_high++;

        for (const int &i : costs)
        {
            if (i > avg_high)
                sum_over += i - avg_high;
            else if (i < avg)
                sum_under += avg - i;
        }

        sum = std::max(sum_over, sum_under);

        int paid_dollars = sum / 100;
        int paid_cents = sum % 100;

        std::cout << "$" << paid_dollars << "." << std::setw(2) << std::setfill('0') << paid_cents << "\n";
    }

    return 0;
}