#include <iostream>
#include <vector>
#include <queue>

const int INF = 10000; // для инициализации

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

int main()
{
    setlocale(LC_ALL, "ru");
    /* Задаем граф матрицей */
    std::vector<std::vector<int>>graph = {
        {0, 7, 9, INF, INF, 14},
        {7, 0, 10, 15, INF, INF},
        {9, 10, 0, 11, INF, 2},
        {INF, 15, 11, 0, 6, INF},
        {INF, INF, INF, 6, 0, 9},
        {14, INF, 2, INF, 9, 0}
    };

    std::vector<int>res = djkstra(graph, 0, 5);
    for (int i = 0; i < res.size(); ++i) {
        std::cout << res[i] << " ";
    }

    return 0;
}
