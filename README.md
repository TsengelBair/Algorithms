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

### Реализация с использованием очереди с приориетом

Предыдущая реализация обладает сложностью O(n^2) из-за использования цикла для поиска мимимального элемента (линейный поиск)

```c++
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
```

Эту сложность можно улучшить, используя очередь с приоритетом. Вместо линейного поиска минимальной вершины, с помощью очереди с приоритетом можно извлекать вершину с минимальным расстоянием за логарифмическое время, что снижает сложность поиска с O(n) до O(log n).

Кроме того, использование массива std::vector<bool> visited становится излишним, так как очереди с приоритетом уже гарантируют обработку каждой вершины один раз, что делает проверку на посещённость ненужной.

```c++
void djkstra(std::vector<std::vector<int>>& graph, int start) {

    int n = graph.size();

    // массив для отслеживания текущих расстояний, по дефолту заполнен INF, т.к. расстояния еще неизвестны
    std::vector<int>dist(n, INF);

    // очередь с приоритетом в порядке возрастания, для того чтобы всегда извлекать минимальную вершину
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>>q;

    dist[start] = 0; // расстояние до самой себя всегда == 0 (если граф не петлевой)

    q.push(std::make_pair(0, start)); // добавляем в очередь стартовую вершину и начинаем основной алгоритм

    // основной цикл алгоритма
    while (!q.empty()) {
        int currentDist = q.top().first; // извлекаем вес вершины
        int minVertex = q.top().second; // извлекаем номер вершины
        q.pop(); // удаляем из очереди и начинаем обработку

        // если извлеченный вес больше уже имеющегося в массиве dist пропускаем 
        if (currentDist > dist[minVertex]) continue;

        // просматриваем соседей извлеченной вершины
        // соседа с минимальным весом добавим в очередь
        for (int v = 0; v < n; ++v) {
            // проверяем, существует ли ребро в графе между двумя вершинами
            // проверяем больше ли имеющийся вес в сравнении с только что найденным
            if (graph[minVertex][v] != INF && dist[v] > currentDist + graph[minVertex][v]) {
                // если найденный вес меньше -> обновляем значение, т.к. нашли более короткий путь
                dist[v] = currentDist + graph[minVertex][v];
                // добавляем вершину в очередь
                q.push(std::make_pair(dist[v], v));
            }
        }
    }

    for (int i = 0; i < dist.size(); ++i) {
        std::cout << dist[i] << " ";
    }
};
```

**Восстановление пути**

Для восстановления пути добавляем массив from, в котором отслеживаем для каждого элемента его родительскую вершину (вершину из которой пришел)

```c++
std::vector<int> djkstra(std::vector<std::vector<int>>& graph, int start, int end) {

    int n = graph.size();

    // массив для отслеживания текущих расстояний, по дефолту заполнен INF, т.к. расстояния еще неизвестны
    std::vector<int>dist(n, INF);

    // массив для отселживания из какой вершины пришли 
    // к примеру если под индексом 1 хранится значение 0, значит в вершину 1 пришли из вершины 0
    std::vector<int>from(n, -1);

    // очередь с приоритетом в порядке возрастания, для того чтобы всегда извлекать минимальную вершину
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>>q;

    dist[start] = 0; // расстояние до самой себя всегда == 0 (если граф не петлевой)

    q.push(std::make_pair(0, start)); // добавляем в очередь стартовую вершину и начинаем основной алгоритм

    // основной цикл алгоритма
    while (!q.empty()) {
        int currentDist = q.top().first; // извлекаем вес вершины
        int minVertex = q.top().second; // извлекаем номер вершины
        q.pop(); // удаляем из очереди и начинаем обработку

        // если извлеченный вес больше уже имеющегося в массиве dist пропускаем 
        if (currentDist > dist[minVertex]) continue;

        // просматриваем соседей извлеченной вершины
        // соседа с минимальным весом добавим в очередь
        for (int v = 0; v < n; ++v) {
            // проверяем, существует ли ребро в графе между двумя вершинами
            // проверяем больше ли имеющийся вес в сравнении с только что найденным
            if (graph[minVertex][v] != INF && dist[v] > currentDist + graph[minVertex][v]) {
                // если найденный вес меньше -> обновляем значение, т.к. нашли более короткий путь
                dist[v] = currentDist + graph[minVertex][v];
                from[v] = minVertex; // вершина из которой пришли
                // добавляем вершину в очередь
                q.push(std::make_pair(dist[v], v));
            }
        }
    }

    std::vector<int>path;
    /* начинаем цикл с конечного элемента и последовательно добавляем в path родительские вершины */
    for (int v = end; v != -1; v = from[v]) {
        path.push_back(v);
    }

    /* разворачиваем, т.к. вершины добавляли с конца */
    std::reverse(path.begin(), path.end());
    return path;
};
```