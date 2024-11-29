## Алгоритм Дейкстры

### Простейшая реализация Дейкстры циклами

![1](/img/1.jpg) 

1. Зададим граф матрицей 

```c++
std::vector<std::vector<int>>graph = {
    {0, 7, 9, INF, INF, 14},
    {7, 0, 10, 15, INF, INF},
    {9, 10, 0, 11, INF, 2},
    {INF, 15, 11, 0, 6, INF},
    {INF, INF, INF, 6, 0, 9},
    {14, INF, 2, INF, 9, 0}
};
```

Элементы главной диагонали всегда нули (если в графе нет петлевых ребер), так как расстояние до самой себя 0

INF обозначает отсутствие ребра между двумя вершинами, то есть маршрута напрямую нет

```c++
const int INF = 10000;
```

2. Реализация алгоритма 

Создаем два массива:

Массив dist для хранения окончательных расстояний, изначально инициализируем все элементы бесконечностью, т.к. расстояния еще не известны

Массив visited для отслеживания обработанных вершин, если вершина просмотрена, значит ее вес окончательный, изначально инициализируем как false, т.к. ни одина из вершин не просмотрена

Помечаем стартовую вершину нулем, т.к. путь до самой себя 0

```c++
void djkstra(std::vector<std::vector<int>>&graph, int start)
{
    int n = graph.size();

    std::vector<int>dist(n, INF);
    std::vector<bool>visited(n, false);

    dist[start] = 0;
};
```

**Находим минимальную вершину**

```c++
void djkstra(std::vector<std::vector<int>>&graph, int start)
{
    int n = graph.size();

    std::vector<int>dist(n, INF);
    std::vector<bool>visited(n, false);

    dist[start] = 0;

    /* Основной цикл, кол-во итераций == кол-ву вершин */
    /* на каждой итерации определяем итоговое расстояние до одной из вершин */
    for (int i = 0; i < n; ++i) {
        /* переменная в которой сохраним минимальную необработанную вершину */
        int minVertex = -1;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && (minVertex == -1 || dist[v] < dist[minVertex])) {
                 /* на первой итерации это стартовая вершина, т.к. ее значение dist[start] = 0 */
                 /* в то время как у остальных - это INF */
                minVertex = v;
            }
        }

        visited[minVertex] = true; // отмечаем как просмотренную окончательно
    }
};
```

**Просматриваем соседей минимальной вершины**

```c++
void djkstra(std::vector<std::vector<int>>&graph, int start)
{
    int n = graph.size();

    std::vector<int>dist(n, INF);
    std::vector<bool>visited(n, false);

    dist[start] = 0;

    /* Основной цикл, кол-во итераций == кол-ву вершин */
    /* на каждой итерации определяем итоговое расстояние до одной из вершин */
    for (int i = 0; i < n; ++i) {
        /* переменная в которой сохраним минимальную необработанную вершину */
        int minVertex = -1;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && (minVertex == -1 || dist[v] < dist[minVertex])) {
                 /* на первой итерации это стартовая вершина, т.к. ее значение dist[start] = 0 */
                 /* в то время как у остальных - это INF */
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
};
```

**Итоговый код**

```c++
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

    djkstra(graph, 0); // [0, 7, 9, 20, 20, 11]
}
```