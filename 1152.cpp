#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int pai[200005];

int find(int x)
{
    if (pai[x] != x)
        pai[x] = find(pai[x]);
    return pai[x];
}
// função Union: retorna true se uniu, false se ja eram unidos
bool unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y)
        return false;
    pai[y] = x;
    return true;
}

struct Aresta
{
    int u, v, peso;
    bool operator<(const Aresta &outra) const
    {
        return peso < outra.peso;
    }
};

// Algoritmo de Kruskal
long long kruskal(int m, vector<Aresta> &arestas)
{
    
    sort(arestas.begin(), arestas.end()); // ordena pelo peso

    for (int i = 0; i < m; i++)
        pai[i] = i;

    long long custoMST = 0;
    for (auto &aresta : arestas)
    {
        if (unite(aresta.u, aresta.v))
        {
            custoMST += aresta.peso;
        }
    }
    return custoMST;
}

int main()
{
    int m, n;

    while (cin >> m >> n && (m || n))
    {
        vector<Aresta> arestas;
        long long custoTotal = 0;

        // passa por todas as arestas
        for (int i = 0; i < n; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            arestas.push_back({x, y, z});
            custoTotal += z;
        }

        long long custoMST = kruskal(m, arestas); // calc usando kruskal

        cout  << custoTotal - custoMST << endl; // custo total - custo da arvore
    }

    return 0;
}