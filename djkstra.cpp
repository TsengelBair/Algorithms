#include <iostream>
#include <vector>

const int INF = 10000;

void djkstra(std::vector<std::vector<int>>&graph, int start)
{
    int n = graph.size();

    std::vector<int>dist(n, INF);
    std::vector<bool>visited(n, false);

    dist[start] = 0;

    /* на самой первой итерации этого цикла в minVertex будет лежать стартовой вершина */
    for (int i = 0; i < n; ++i) {
        /* вспомогательная переменная, которая поможет найти вершину с минимальным весом (как при поиске min/max в массиве) */
        int minVertex = -1;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && (minVertex == -1 || dist[v] < dist[minVertex])) {
                // на первой итерации цикла minVertex станет равной первому элементу dist[v]
                minVertex = v;
            }
        }

        visited[minVertex] = true; // отмечаем как просмотренную окончательно

        // просматриваем соседей минимальной вершины
        for (int v = 0; v < n; ++v) {
            // проверяем существует ли ребро между вершинами, если == INF, ребра нет
            // проверяем просмотрена ли вершина
            if (graph[minVertex][v] != INF && !visited[v]) {
                dist[v] = std::min(dist[v], dist[minVertex] + graph[minVertex][v]);
            }
        }
    }

    for (int i = 0; i < dist.size(); ++i) {
        std::cout << dist[i] << " ";
    }
};

int main()
{
    /* Задаем граф матрицей */
    std::vector<std::vector<int>>graph = {
        {0, 7, 9, INF, INF, 14},
        {7, 0, 10, 15, INF, INF},
        {9, 10, 0, 11, INF, 2},
        {INF, 15, 11, 0, 6, INF},
        {INF, INF, INF, 6, 0, 9},
        {14, INF, 2, INF, 9, 0}
    };

    djkstra(graph, 0);
}
