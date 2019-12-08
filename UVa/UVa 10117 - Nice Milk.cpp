/*
I consulted https://blog.csdn.net/metaphysis/article/details/6979026
to better understand the problem. Google translate was used to read the
text and comments within the code. Additionally, I consulted the forum
posts at ttps://onlinejudge.org/board/viewtopic.php?t=17901 for an
additional helpful test case when I was testing. This additional case
helped me find and fix a bug in this program.
*/

#include <iostream>
#include <iomanip>
#include <cmath> 
#include <algorithm>
#include <vector>

constexpr double epsilon = 1e-10;

struct coord_t
{
    double x;
    double y;

    coord_t(double a = 0, double b = 0): x(a), y(b) {}

    bool operator<(const coord_t &other) const
    {
        if (std::abs(x - other.x) > epsilon)
            return x < other.x;
        if (std::abs(y - other.y) > epsilon)
            return y < other.y;
        return false;
    }

    bool operator>(const coord_t &other) const
    {
        return !(*this < other);
    }

    coord_t operator-(const coord_t &other) const
    {
        return coord_t(x - other.x, y - other.y);
    }

    coord_t operator+(const coord_t &other) const
    {
        return coord_t(x + other.x, y + other.y);
    }

    coord_t operator*(const double &a) const
    {
        return coord_t(x * a, y * a);
    }
};

double cross_product(const coord_t &orth, const coord_t &a, const coord_t &b)
{
    return (a.x - orth.x) * (b.y - orth.y) - (a.y - orth.y) * (b.x - orth.x);
}

double cross_product(const coord_t &a, const coord_t &b)
{
    return a.x * b.y - a.y * b.x;
}

struct segment_t
{
    coord_t start;
    coord_t end;
    double angle;
    int label;

    segment_t(const coord_t &s = coord_t(), const coord_t &e = coord_t(), const int &l = 0):
        start(s), end(e), label(l)
    {
        angle = atan2(end.y - start.y, end.x - start.x);
    };

    bool operator<(const segment_t &other) const
    {
        if (std::abs(angle - other.angle) > epsilon)
            return angle > other.angle;
        return cross_product(other.start, other.end, start) > -epsilon;
    }
};

coord_t calculate_intersect(segment_t a, segment_t b)
{
    return a.start + (a.end - a.start) * (cross_product(b.end - b.start, a.start - b.start) / cross_product(a.end - a.start, b.end - b.start));
}

std::vector<coord_t> calculate_half_plane_intersect(std::vector<segment_t> &s)
{
    int n = s.size();
    int m = 1;
    int f = 0;
    int b = -1;
    std::vector<segment_t> deq(n);

    std::sort(s.begin(), s.end());

    for (int i = 1; i < n; i++)
    {
        if (std::abs(s[i].angle - s[m - 1].angle) > epsilon)
            s[m++] = s[i];
    }

    n = m;
    deq[++b] = s[0];
    deq[++b] = s[1];

    for (int i = 2; i < n; i++)
    {
        while (f < b && cross_product(s[i].start, s[i].end, calculate_intersect(deq[b], deq[b - 1])) < epsilon)
            b--;

        while (f < b && cross_product(s[i].start, s[i].end, calculate_intersect(deq[f], deq[f + 1])) < epsilon)
            f++;

        deq[++b] = s[i];
    }

    while (f < b && cross_product(deq[f].start, deq[f].end, calculate_intersect(deq[b], deq[b - 1])) < epsilon)
        b--;

    while (f < b && cross_product(deq[b].start, deq[b].end, calculate_intersect(deq[f], deq[f + 1])) < epsilon)
        f++;

    std::vector<coord_t> ans;

    for (int i = f; i < b; i++)
        ans.push_back(calculate_intersect(deq[i], deq[i + 1]));

    if (b > f + 1)
        ans.push_back(calculate_intersect(deq[f], deq[b]));

    return ans;
}

double calculate_area(const std::vector<coord_t> &pts)
{
    int n = pts.size();
    if (n < 3)
        return 0.0;
    
    double ans = 0;
    for (int i = 0, j = n - 1; i < n; j = i++)
        ans += pts[i].x * pts[j].y - pts[i].y * pts[j].x;

    return std::abs(ans) / 2;
}

int main()
{
    int n, k, h;

    while (std::cin >> n >> k >> h && !(n == 0 && k == 0 && h == 0))
    {
        std::vector<int> perms(32);
        std::vector<coord_t> vertices(32);
        std::vector<coord_t> bread;
        std::vector<segment_t> segments(32);

        for (int i = 0; i < n; i++)
        {
            std::cin >> vertices[i].x >> vertices[i].y;
            bread.push_back(vertices[i]);
        }

        vertices[n] = vertices[0];
        bread.push_back(vertices[0]);

        for (int i = 0; i < n; i++)
        {
            coord_t a = vertices[i];
            coord_t b = vertices[i + 1];

            coord_t norm(b.y - a.y, a.x - b.x);

            double v = std::hypot(norm.x, norm.y);

            norm.x = norm.x / v * h;
            norm.y = norm.y / v * h;

            a = a - norm;
            b = b - norm;

            segments[i] = segment_t(a, b);
        }

        for (int i = 0; i < k; i++)
            perms[i] = 1;

        std::sort(perms.begin(), perms.begin() + n);

        double area = calculate_area(bread);
        double max_area = 0;

        do
        {
            std::vector<segment_t> segs;

            for (int i = 0; i < n; i++)
                segs.push_back((perms[i])? segments[i]: segment_t(bread[i], bread[i + 1]));

            std::vector<coord_t> convex = calculate_half_plane_intersect(segs);
            double new_area = calculate_area(convex);

            max_area = std::max(max_area, area - new_area);
        }
        while (std::next_permutation(perms.begin(), perms.begin() + n));

        std::cout << std::fixed << std::setprecision(2) << max_area << "\n";
    }

    return 0;
}