//задача1
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cout << "Введите N и M: ";
    cin >> N >> M;

    vector<vector<int>> a(N, vector<int>(M));
    cout << "Введите матрицу баллов:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> a[i][j];
        }
    }

    // Матрица для хранения максимальных сумм до каждой клетки
    vector<vector<int>> dp(N, vector<int>(M, 0));
    
    // Матрица для восстановления пути (1 - пришли сверху, 2 - пришли слева)
    vector<vector<int>> from(N, vector<int>(M, 0));

    dp[0][0] = a[0][0];

    // Заполняем первую строку и первый столбец
    for (int j = 1; j < M; j++) {
        dp[0][j] = dp[0][j - 1] + a[0][j];
        from[0][j] = 2; // пришли слева
    }
    for (int i = 1; i < N; i++) {
        dp[i][0] = dp[i - 1][0] + a[i][0];
        from[i][0] = 1; // пришли сверху
    }

    // Основное динамическое программирование
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j] + a[i][j];
                from[i][j] = 1;
            } else {
                dp[i][j] = dp[i][j - 1] + a[i][j];
                from[i][j] = 2;
            }
        }
    }

    cout << "Максимальная сумма баллов: " << dp[N - 1][M - 1] << endl;

    // Восстановление пути с конца в начало
    vector<pair<int, int>> path;
    int cur_i = N - 1;
    int cur_j = M - 1;
    
    while (cur_i >= 0 && cur_j >= 0) {
        path.push_back({cur_i, cur_j});
        if (cur_i == 0 && cur_j == 0) break;
        
        if (from[cur_i][cur_j] == 1) {
            cur_i--;
        } else {
            cur_j--;
        }
    }

    cout << "Маршрут (координаты):" << endl;
    // Выводим в обратном порядке
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i].first << " " << path[i].second << endl;
    }

    return 0;
}
//задача2
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    vector<int> dp(m, 0);
    dp[0] = a[0][0];

    for (int j = 1; j < m; j++) {
        dp[j] = dp[j - 1] + a[0][j];
    }

    for (int i = 1; i < n; i++) {
        dp[0] += a[i][0];
        for (int j = 1; j < m; j++) {
            if (dp[j] > dp[j - 1]) dp[j] = dp[j] + a[i][j];
            else dp[j] = dp[j - 1] + a[i][j];
        }
    }

    cout << dp[m - 1] << endl;
    return 0;
}
//задача3
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k, l;
    cin >> n >> k >> l;
    vector<int> a(n);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.rbegin(), a.rend());

    int sum = 0, count = 0;
    
    for (int i = 0; i < n; i++) {
        if (count == k) break;

        int same = 0;
        for (int j = 0; j < i; j++) {
            if (a[j] == a[i]) same++;
        }

        if (same < l) {
            sum += a[i];
            count++;
        }
    }

    cout << sum << endl;
    return 0;
}
//задача1 практика 12
#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n, m;
    cout << "Введите N и M: ";
    cin >> n >> m;

    char a[100][100];
    cout << "Введите лабиринт:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    int sx, sy;
    cout << "Введите старт (x y): ";
    cin >> sx >> sy;

    // Массив посещенных клеток
    bool vis[100][100] = {false};
    
    // Очередь хранит: x, y и сколько файлов собрано
    queue<int> qx, qy, qp;
    
    qx.push(sx);
    qy.push(sy);
    qp.push(0);
    vis[sx][sy] = true;

    int ans = -1;

    // Направления: вправо, влево, вниз, вверх
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    while (!qx.empty()) {
        int x = qx.front();
        int y = qy.front();
        int pdf = qp.front();
        qx.pop(); qy.pop(); qp.pop();

        // Если нашли файл, плюсуем
        if (a[x][y] == 'P') {
            pdf++;
        }

        // Если вышли на улицу
        if (a[x][y] == 'E') {
            ans = pdf;
            break; // Вышли, дальше искать не надо
        }

        // Идем в 4 стороны
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Проверка границ
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                // Если не стена и не были тут
                if (a[nx][ny] != '1' && !vis[nx][ny]) {
                    vis[nx][ny] = true;
                    qx.push(nx);
                    qy.push(ny);
                    qp.push(pdf);
                }
            }
        }
    }

    if (ans != -1) {
        cout << "Собрано файлов: " << ans << endl;
    } else {
        cout << "Выхода нет!" << endl;
    }

    return 0;
}