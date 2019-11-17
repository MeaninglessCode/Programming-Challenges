/*
I consulted https://belbesy.wordpress.com/2011/06/12/uva-10047-the-monocycle/
to better understand the problem.
*/

#include <iostream>
#include <vector>
#include <queue>

#define vec std::vector
#define int_pair std::pair<int, int>

constexpr int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

typedef struct
{
    int x;
    int y;
    int s;
    int c;
    int dir;
} queue_entry_t;

bool valid_move(const vec<vec<char>> &tileset, const int &M, const int &N, const int &x, const int &y)
{
    return (x >= 0 && x < M && y >= 0 && y < N && (tileset[x][y] != '#'));
}

int breadth_first_search(const vec<vec<char>> &tileset, int M, int N, const int_pair &sp, const int_pair &tp)
{
    vec<vec<vec<vec<bool>>>> visited(30, vec<vec<vec<bool>>>(30, vec<vec<bool>>(6, vec<bool>(6))));

    queue_entry_t start =
    {
        .x = sp.first,
        .y = sp.second,
        .s = 0,
        .c = 0,
        .dir = 0
    };

    std::queue<queue_entry_t> q;
    q.push(start);

    visited[start.x][start.y][0][0] = true;

    queue_entry_t front, tmp;

    while (!q.empty())
    {
        front = q.front();
        q.pop();

        tmp =
        {
            .x = front.x + dir[front.dir][0],
            .y = front.y + dir[front.dir][1],
            .s = front.s + 1,
            .c = (front.c + 1) % 5,
            .dir = front.dir
        };

        if (valid_move(tileset, M, N, tmp.x, tmp.y) && !visited[tmp.x][tmp.y][tmp.c][tmp.dir])
        {
            if (tmp.x == tp.first && tmp.y == tp.second && tmp.c == 0)
                return tmp.s;

            visited[tmp.x][tmp.y][tmp.c][tmp.dir] = true;
            q.push(tmp);
        }

        tmp =
        {
            .x = front.x,
            .y = front.y,
            .s = front.s + 1,
            .c = front.c,
            .dir = (front.dir + 1) % 4
        };

        if (valid_move(tileset, M, N, tmp.x, tmp.y) && !visited[tmp.x][tmp.y][tmp.c][tmp.dir])
        {
            visited[tmp.x][tmp.y][tmp.c][tmp.dir] = true;
            q.push(tmp);
        }

        tmp =
        {
            .x = front.x,
            .y = front.y,
            .s = front.s + 1,
            .c = front.c,
            .dir = (front.dir + 3) % 4
        };

        if (valid_move(tileset, M, N, tmp.x, tmp.y) && !visited[tmp.x][tmp.y][tmp.c][tmp.dir])
        {
            visited[tmp.x][tmp.y][tmp.c][tmp.dir] = true;
            q.push(tmp);
        }
    }

    return -1;
}

int main()
{
    int case_num = 1;
    int M;
    int N;

    while (std::cin >> M >> N && !(M == 0 && N == 0))
    {
        vec<vec<char>> tileset(M, vec<char>(N));
        int_pair start_pos;
        int_pair target_pos;

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                std::cin >> tileset[i][j];
                if (tileset[i][j] == 'S')
                    start_pos = int_pair(i, j);
                else if (tileset[i][j] == 'T')
                    target_pos = int_pair(i, j);
            }
        }

        if (case_num != 1)
            std::cout << "\n";

        std::cout << "Case #" << case_num << "\n";
        case_num++;

        int res = breadth_first_search(tileset, M, N, start_pos, target_pos);
        if (res != -1)
            std::cout << "minimum time = " << res << " sec\n";
        else
            std::cout << "destination not reachable\n";
    }

    return 0;
}