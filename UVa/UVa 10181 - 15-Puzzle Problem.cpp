#include <iostream>
#include <vector>
#include <limits>

#define vec std::vector
#define vint std::vector<int>
#define int_pair std::pair<int, int>

class puzzle
{
    public:
        puzzle(): m_board(vec<vec<char>>(4, vec<char>(4))),
            m_pos(vec<int_pair>(17)), m_solved(false), m_init_x(-1), m_init_y(-1), m_max_depth(-1),
            m_htable(vec<vec<vint>>(4, vec<vint>(4, vint(16)))) {};

        void init_board()
        {
            for (int i = 0, k = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    m_pos[++k].first = i;
                    m_pos[k].second = j;
                }
            }

            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    for (int k = 1; k < 16; k++)
                        m_htable[i][j][k] = abs(i - m_pos[k].first) + abs(j - m_pos[k].second);

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    int k;
                    std::cin >> k;
                    m_board[i][j] = k;

                    if (m_board[i][j] == 0)
                    {
                        m_init_x = i;
                        m_init_y = j;
                    }
                }
            }
        }

        std::string solve()
        {
            if (!solvable())
                return "This puzzle is not solvable.\n";

            int init_h = H();
            m_max_depth = init_h;

            if (m_max_depth == 0)
                return "\n";

            std::string test;
            test.resize(100);

            while (!m_solved)
                m_max_depth = iterative_deepening_a(test, 0, init_h, -1);

            return test + "\n";
        }


    private:
        vec<vec<char>> m_board;
        vec<int_pair> m_pos;
        vec<vec<vint>> m_htable;

        const static vec<int_pair> dir;
        const static vec<char> dirc;

        int m_init_x;
        int m_init_y;
        int m_max_depth;
        bool m_solved;

        bool solvable()
        {
            int s = 0;
            int r;

            for (int i = 0; i < 16; i++)
            {
                int idiv4 = i / 4;
                int imod4 = i % 4;

                if (m_board[idiv4][imod4] == 0)
                    r = idiv4 + 1;
                else
                {
                    for (int j = i + 1; j < 16; j++)
                    {
                        int jdiv4 = j / 4;
                        int jmod4 = j % 4;

                        if (m_board[jdiv4][jmod4] < m_board[idiv4][imod4])
                            if (m_board[jdiv4][jmod4])
                                s++;
                    }
                }
            }

            return 1 - (s + r) % 2;
        }

        int iterative_deepening_a(std::string &cur_path, int depth, int hv, int prev_step)
        {
            if (hv == 0)
            {
                m_solved = depth;
                cur_path = cur_path.substr(0, depth);
                return depth;
            }

            if (depth + 5 * hv / 3 > m_max_depth)
                return depth + 5 * hv / 3;

            int tx;
            int ty;
            int x = m_init_x;
            int y = m_init_y;

            int shv;
            int submxdep = std::numeric_limits<int>::max();
            int val = submxdep;

            for (int i = 0; i < 4; i++)
            {
                if (i + prev_step == 3)
                    continue;
                
                tx = x + dir[i].first;
                ty = y + dir[i].second;

                if (tx < 0 || ty < 0 || tx > 3 || ty > 3)
                    continue;

                shv = hv;
                shv -= m_htable[tx][ty][m_board[tx][ty]];
                shv += m_htable[x][y][m_board[tx][ty]];

                m_init_x = tx;
                m_init_y = ty;
                std::swap(m_board[x][y], m_board[tx][ty]);

                cur_path[depth] = dirc[i];
                val = iterative_deepening_a(cur_path, depth + 1, shv, i);

                std::swap(m_board[x][y], m_board[tx][ty]);
                m_init_x = x;
                m_init_y = y;

                if (m_solved)
                    return m_solved;

                submxdep = std::min(submxdep, val);
            }

            return submxdep;
        }

        int H()
        {
            int s = 0;

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    int n = m_board[i][j];
                    
                    if (n != 0)
                        s += abs(i - m_pos[n].first) + abs(j - m_pos[n].second);
                }
            }

            return s;
        }
};

const vec<int_pair> puzzle::dir = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};
const vec<char> puzzle::dirc = {'L', 'U', 'D', 'R'};

int main()
{
    int num_puzzles;
    std::cin >> num_puzzles;

    while (num_puzzles--)
    {
        puzzle p;
        p.init_board();
        std::cout << p.solve();
    }

    return 0;
}