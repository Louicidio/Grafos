#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int GRID_SIZE = 50;
const double WORLD_SIZE = 10000.0;
const double CELL_SIZE = WORLD_SIZE / GRID_SIZE;

struct Montanha {
    double x, y, r, r2;
};

// DFS para percorrer componentes conectados
void dfs(int v, const vector<vector<int>>& grafo, vector<bool>& visitado) {
    visitado[v] = true;
    for (int u : grafo[v]) {
        if (!visitado[u]) {
            dfs(u, grafo, visitado);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    static double fx[1000], fy[1000];
    
    for (int i = 0; i < n; i++) {
        cin >> fx[i] >> fy[i];
    }
    
    vector<Montanha> montanhas(m);
    vector<int> grid[GRID_SIZE][GRID_SIZE];
    
    for (int i = 0; i < m; i++) {
        cin >> montanhas[i].x >> montanhas[i].y >> montanhas[i].r;
        montanhas[i].r2 = montanhas[i].r * montanhas[i].r;
        
        // Adiciona a montanha a todas as células do grid que ela toca
        int minCellX = max(0, (int)((montanhas[i].x - montanhas[i].r) / CELL_SIZE));
        int maxCellX = min(GRID_SIZE - 1, (int)((montanhas[i].x + montanhas[i].r) / CELL_SIZE));
        int minCellY = max(0, (int)((montanhas[i].y - montanhas[i].r) / CELL_SIZE));
        int maxCellY = min(GRID_SIZE - 1, (int)((montanhas[i].y + montanhas[i].r) / CELL_SIZE));
        
        for (int gx = minCellX; gx <= maxCellX; gx++) {
            for (int gy = minCellY; gy <= maxCellY; gy++) {
                grid[gx][gy].push_back(i);
            }
        }
    }
    
    // Construir GRAFO com lista de adjacência
    vector<vector<int>> grafo(n);
    
    for (int i = 0; i < n; i++) {
        double ax = fx[i], ay = fy[i];
        
        for (int j = i + 1; j < n; j++) {
            double bx = fx[j], by = fy[j];
            double dx = bx - ax, dy = by - ay;
            double len2 = dx * dx + dy * dy;
            
            if (len2 == 0) continue;
            
            double minX = min(ax, bx);
            double maxX = max(ax, bx);
            double minY = min(ay, by);
            double maxY = max(ay, by);
            
            // Identifica células do grid que o segmento atravessa
            int minCellX = max(0, (int)(minX / CELL_SIZE));
            int maxCellX = min(GRID_SIZE - 1, (int)(maxX / CELL_SIZE));
            int minCellY = max(0, (int)(minY / CELL_SIZE));
            int maxCellY = min(GRID_SIZE - 1, (int)(maxY / CELL_SIZE));
            
            bool bloqueado = false;
            vector<bool> checked(m, false);
            
            for (int gx = minCellX; gx <= maxCellX && !bloqueado; gx++) {
                for (int gy = minCellY; gy <= maxCellY && !bloqueado; gy++) {
                    for (int idx : grid[gx][gy]) {
                        if (checked[idx]) continue;
                        checked[idx] = true;
                        
                        const auto &mont = montanhas[idx];
                        double cx = mont.x, cy = mont.y, r = mont.r, r2 = mont.r2;
                        
                        if (cx + r < minX || cx - r > maxX || cy + r < minY || cy - r > maxY)
                            continue;
                        
                        double t = ((cx - ax) * dx + (cy - ay) * dy) / len2;
                        
                        double px, py;
                        if (t <= 0) {
                            px = ax; py = ay;
                        } else if (t >= 1) {
                            px = bx; py = by;
                        } else {
                            px = ax + t * dx;
                            py = ay + t * dy;
                        }
                        
                        double dist_x = cx - px;
                        double dist_y = cy - py;
                        
                        if (dist_x * dist_x + dist_y * dist_y < r2) {
                            bloqueado = true;
                            break;
                        }
                    }
                }
            }
            
            // Se não está bloqueado, adiciona aresta no GRAFO
            if (!bloqueado) {
                grafo[i].push_back(j);
                grafo[j].push_back(i);
            }
        }
    }
    
    // Contar componentes conectados usando DFS
    vector<bool> visitado(n, false);
    int componentes = 0;
    
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            dfs(i, grafo, visitado);
            componentes++;
        }
    }
    
    cout << componentes - 1 << '\n';
    
    return 0;
}