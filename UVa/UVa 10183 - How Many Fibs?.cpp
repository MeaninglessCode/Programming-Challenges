#include <iostream>
#include <iomanip>
#include <vector>

/*
Code taken from https://sites.google.com/site/indy256/algo_cpp/bigint
and modified.

This was done to save a lot of time in implementing and debugging a
hand made big int class so that I could start on the same ground as
those using Java for these challenges.
*/
class big_int
{
    public:
        big_int(): m_sign(1) {}
        big_int(long long v) { *this = v; }
        big_int(const std::string &s) { read(s); }

        void operator=(const big_int &v)
        {
            m_sign = v.m_sign;
            m_data = v.m_data;
        }

        void operator=(long long v)
        {
            m_sign = 1;
            if (v < 0)
                m_sign = -1, v = -v;
            
            for (; v > 0; v = v / base)
                m_data.push_back(v % base);
        }

        big_int operator+(const big_int &v) const
        {
            if (m_sign == v.m_sign)
            {
                big_int res = v;

                for (int i = 0, carry = 0; i < (int) std::max(m_data.size(), v.m_data.size()) || carry; ++i)
                {
                    if (i == (int) res.m_data.size())
                        res.m_data.push_back(0);
                    
                    res.m_data[i] += carry + ((i < (int) m_data.size())? m_data[i] : 0);
                    carry = res.m_data[i] >= base;
                    
                    if (carry)
                        res.m_data[i] -= base;
                }

                return res;
            }

            return *this - (-v);
        }

        big_int operator-(const big_int &v) const
        {
            if (m_sign == v.m_sign)
            {
                if (abs() >= v.abs())
                {
                    big_int res = *this;
                    for (int i = 0, carry = 0; i < (int) v.m_data.size() || carry; ++i)
                    {
                        res.m_data[i] -= carry + ((i < (int) v.m_data.size()) ? v.m_data[i] : 0);
                        carry = res.m_data[i] < 0;
                        
                        if (carry)
                            res.m_data[i] += base;
                    }

                    res.trim();
                    return res;
                }

                return -(v - *this);
            }

            return *this + (-v);
        }

        void operator*=(int v)
        {
            if (v < 0)
                m_sign = -m_sign, v = -v;

            for (int i = 0, carry = 0; i < (int) m_data.size() || carry; ++i)
            {
                if (i == (int) m_data.size())
                    m_data.push_back(0);

                long long cur = m_data[i] * (long long) v + carry;
                carry = (int) (cur / base);
                m_data[i] = (int) (cur % base);
            }

            trim();
        }

        big_int operator*(int v) const
        {
            big_int res = *this;
            res *= v;
            return res;
        }

        big_int operator/(const big_int &v) const { return divmod(*this, v).first; }
        big_int operator%(const big_int &v) const { return divmod(*this, v).second; }

        void operator/=(int v)
        {
            if (v < 0)
                m_sign = -m_sign, v = -v;

            for (int i = (int) m_data.size() - 1, rem = 0; i >= 0; --i)
            {
                long long cur = m_data[i] + rem * (long long) base;
                m_data[i] = (int) (cur / v);
                rem = (int) (cur % v);
            }

            trim();
        }

        big_int operator/(int v) const
        {
            big_int res = *this;
            res /= v;
            return res;
        }

        int operator%(int v) const
        {
            if (v < 0)
                v = -v;

            int m = 0;
            for (int i = m_data.size() - 1; i >= 0; --i)
                m = (m_data[i] + m * (long long) base) % v;

            return m * m_sign;
        }

        void operator+=(const big_int &v) { *this = *this + v; }
        void operator-=(const big_int &v) { *this = *this - v; }
        void operator*=(const big_int &v) { *this = *this * v; }
        void operator/=(const big_int &v) { *this = *this / v; }

        bool operator<(const big_int &v) const
        {
            if (m_sign != v.m_sign)
                return m_sign < v.m_sign;

            if (m_data.size() != v.m_data.size())
                return m_data.size() * m_sign < v.m_data.size() * v.m_sign;

            for (int i = m_data.size() - 1; i >= 0; i--)
                if (m_data[i] != v.m_data[i])
                    return m_data[i] * m_sign < v.m_data[i] * m_sign;

            return false;
        }

        bool operator>(const big_int &v) const { return v < *this; }
        bool operator<=(const big_int &v) const { return !(v < *this); }
        bool operator>=(const big_int &v) const { return !(*this < v); }
        bool operator==(const big_int &v) const { return !(*this < v) && !(v < *this); }
        bool operator!=(const big_int &v) const { return *this < v || v < *this; }

        bool is_zero() const { return m_data.empty() || (m_data.size() == 1 && !m_data[0]); }

        big_int operator-() const
        {
            big_int res = *this;
            res.m_sign = -m_sign;
            return res;
        }

        big_int abs() const
        {
            big_int res = *this;
            res.m_sign *= res.m_sign;
            return res;
        }

        long long longValue() const
        {
            long long res = 0;

            for (int i = m_data.size() - 1; i >= 0; i--)
                res = res * base + m_data[i];

            return res * m_sign;
        }

        friend big_int gcd(const big_int &a, const big_int &b) { return (b.is_zero() ? a : gcd(b, a % b)); }
        friend big_int lcm(const big_int &a, const big_int &b) { return (a / gcd(a, b) * b); }

        friend std::istream& operator>>(std::istream &stream, big_int &v)
        {
            std::string s;
            stream >> s;
            v.read(s);
            return stream;
        }

        friend std::ostream& operator<<(std::ostream &stream, const big_int &v)
        {
            if (v.m_sign == -1)
                stream << '-';

            stream << (v.m_data.empty() ? 0 : v.m_data.back());
            for (int i = (int) v.m_data.size() - 2; i >= 0; --i)
                stream << std::setw(base_digits) << std::setfill('0') << v.m_data[i];

            return stream;
        }

        big_int operator*(const big_int &v) const
        {
            std::vector<int> a6 = convert_base(this->m_data, base_digits, 6);
            std::vector<int> b6 = convert_base(v.m_data, base_digits, 6);
            std::vector<long long> a(a6.begin(), a6.end());
            std::vector<long long> b(b6.begin(), b6.end());

            while (a.size() < b.size())
                a.push_back(0);
            while (b.size() < a.size())
                b.push_back(0);
            while (a.size() & (a.size() - 1))
                a.push_back(0), b.push_back(0);

            std::vector<long long> c = karatsuba_multiply(a, b);
            big_int res;
            res.m_sign = m_sign * v.m_sign;

            for (int i = 0, carry = 0; i < (int) c.size(); i++)
            {
                long long cur = c[i] + carry;
                res.m_data.push_back((int) (cur % 1000000));
                carry = (int) (cur / 1000000);
            }

            res.m_data = convert_base(res.m_data, 6, base_digits);
            res.trim();

            return res;
        }

    protected:
        std::vector<int> m_data;
        int m_sign;

        static const int base = 1000000000;
        static const int base_digits = 9;

    private:
        std::pair<big_int, big_int> divmod(const big_int &a1, const big_int &b1) const
        {
            int norm = base / (b1.m_data.back() + 1);

            big_int a = a1.abs() * norm;
            big_int b = b1.abs() * norm;
            big_int q, r;
            q.m_data.resize(a.m_data.size());

            for (int i = a.m_data.size() - 1; i >= 0; i--)
            {
                r *= base;
                r += a.m_data[i];

                int s1 = (r.m_data.size() <= b.m_data.size()) ? 0 : r.m_data[b.m_data.size()];
                int s2 = (r.m_data.size() <= b.m_data.size() - 1) ? 0 : r.m_data[b.m_data.size() - 1];
                int d = ((long long) base * s1 + s2) / b.m_data.back();

                r -= b * d;

                while (r < 0)
                    r += b, --d;

                q.m_data[i] = d;
            }

            q.m_sign = a1.m_sign * b1.m_sign;
            r.m_sign = a1.m_sign;

            q.trim();
            r.trim();

            return std::make_pair(q, r / norm);
        }

        void trim()
        {
            while (!m_data.empty() && !m_data.back())
                m_data.pop_back();

            if (m_data.empty())
                m_sign = 1;
        }

        void read(const std::string &s)
        {
            m_sign = 1;
            m_data.clear();

            int pos = 0;
            while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+'))
            {
                if (s[pos] == '-')
                    m_sign = -m_sign;

                ++pos;
            }
            for (int i = s.size() - 1; i >= pos; i -= base_digits)
            {
                int x = 0;

                for (int j = std::max(pos, i - base_digits + 1); j <= i; j++)
                    x = x * 10 + s[j] - '0';

                m_data.push_back(x);
            }

            trim();
        }

        static std::vector<int> convert_base(const std::vector<int> &a, int old_digits, int new_digits)
        {
            std::vector<long long> p(std::max(old_digits, new_digits) + 1);
            p[0] = 1;

            for (int i = 1; i < (int) p.size(); i++)
                p[i] = p[i - 1] * 10;

            std::vector<int> res;
            long long cur = 0;
            int cur_digits = 0;
            
            for (int i = 0; i < (int) a.size(); i++)
            {
                cur += a[i] * p[cur_digits];
                cur_digits += old_digits;

                while (cur_digits >= new_digits)
                {
                    res.push_back(int(cur % p[new_digits]));
                    cur /= p[new_digits];
                    cur_digits -= new_digits;
                }
            }

            res.push_back((int) cur);

            while (!res.empty() && !res.back())
                res.pop_back();

            return res;
        }

        static std::vector<long long> karatsuba_multiply(const std::vector<long long> &a, const std::vector<long long> &b)
        {
            int n = a.size();
            std::vector<long long> res(n + n);

            if (n <= 32)
            {
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        res[i + j] += a[i] * b[j];

                return res;
            }

            int k = n >> 1;
            std::vector<long long> a1(a.begin(), a.begin() + k);
            std::vector<long long> a2(a.begin() + k, a.end());
            std::vector<long long> b1(b.begin(), b.begin() + k);
            std::vector<long long> b2(b.begin() + k, b.end());

            std::vector<long long> a1b1 = karatsuba_multiply(a1, b1);
            std::vector<long long> a2b2 = karatsuba_multiply(a2, b2);

            for (int i = 0; i < k; i++)
                a2[i] += a1[i];
            for (int i = 0; i < k; i++)
                b2[i] += b1[i];

            std::vector<long long> r = karatsuba_multiply(a2, b2);
            for (int i = 0; i < (int) a1b1.size(); i++)
                r[i] -= a1b1[i];
            for (int i = 0; i < (int) a2b2.size(); i++)
                r[i] -= a2b2[i];

            for (int i = 0; i < (int) r.size(); i++)
                res[i + k] += r[i];
            for (int i = 0; i < (int) a1b1.size(); i++)
                res[i] += a1b1[i];
            for (int i = 0; i < (int) a2b2.size(); i++)
                res[i + n] += a2b2[i];
            return res;
        }
};
/* End of code from https://sites.google.com/site/indy256/algo_cpp/bigint*/

int main()
{
    big_int a;
    big_int b;

    std::vector<big_int> fibonacci(500);
    fibonacci[0] = 1;
    fibonacci[1] = 2;

    for (int i = 2; i < 500; i++)
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];

    while (std::cin >> a >> b && !(b == 0 && a ==0))
    {
        int num_fibs = 0;

        for (const big_int &i: fibonacci)
            if ((i >= a) && (i <= b))
                num_fibs++;

        std::cout << num_fibs << "\n";
    }

    return 0;
}