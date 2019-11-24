#include <iostream>
#include <iomanip>

struct coord_t
{
    coord_t() {};
    coord_t(double a, double b): x(a), y(b) {}

    double x;
    double y;
};

std::ostream& operator<<(std::ostream &o, const coord_t &c) { return o << "(" << c.x << "," << c.y << ")"; }

int main()
{
    int n;
    coord_t gopher;
    coord_t dog;

    while (std::cin >> n >> gopher.x >> gopher.y >> dog.x >> dog.y && !std::cin.fail())
    {
        bool can_escape = false;
        coord_t escape_hole;

        while (n--)
        {
            coord_t hole;
            std::cin >> hole.x >> hole.y;

            if (can_escape)
                continue;

            double gd = (gopher.x - hole.x) * (gopher.x - hole.x) + (gopher.y - hole.y) * (gopher.y - hole.y);
            double dd = (dog.x - hole.x) * (dog.x - hole.x) + (dog.y - hole.y) * (dog.y - hole.y);

            if (4 * gd <= dd)
            {
                can_escape = true;
                escape_hole = coord_t(hole.x, hole.y);
            }
        }

        if (!can_escape)
            std::cout << "The gopher cannot escape.\n";
        else
            std::cout << std::fixed << std::setprecision(3) <<
                "The gopher can escape through the hole at " << escape_hole << ".\n";
    }

    return 0;
}