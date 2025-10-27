// Codinome: TaylorScript. Luiz Eduardo, Eduardo de Almeida, Lucas Cogrossi

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#define INF (1 << 25)

int matrix[501][501];

int dijkstra(int src, int des, int n) {
    vector<int> dist(n + 1, INF);
    vector<bool> visited(n + 1, false);

    dist[src] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, short_dis = INF;

        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < short_dis) {
                short_dis = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 1; v <= n; v++) {
            if (!visited[v] && matrix[u][v] != INF &&
                dist[u] + matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + matrix[u][v];
            }
        }
    }

    return dist[des];
}

int main() {
    int n, e;
    while (cin >> n >> e && (n || e)) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                matrix[i][j] = INF;

        for (int i = 0; i < e; i++) {
            int x, y, h;
            cin >> x >> y >> h;
            matrix[x][y] = h;
            if (matrix[y][x] != INF)
                matrix[x][y] = matrix[y][x] = 0;
        }

        int k;
        cin >> k;

        for (int i = 0; i < k; i++) {
            int o, d;
            cin >> o >> d;
            int r = dijkstra(o, d, n);
            if (r == INF)
                cout << "Nao e possivel entregar a carta" << endl;
            else
                cout << r << endl;
        }

        cout << endl;
    }

    return 0;
}