#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    int n, m;
    cout << "Введите количество вершин и рёбер: ";
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));
    cout << "Введите матрицу инцидентности (n x m):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> matrix[i][j];
        }
    }

    vector<vector<int>> graph(n, vector<int>(n, 0)); // n - кол-во вершин, 0 -не связаны
    for (int j = 0; j < m; j++)
    {
        int u = -1, v = -1;         // индексы двух  вершин (-1 -- не найдены)
        for (int i = 0; i < n; i++) // проходим по ребру
        {
            if (matrix[i][j] == 1)
            {
                if (u == -1)
                    u = i;
                else
                    v = i;
            }
        }
        if (u != -1 && v != -1)
        {
            graph[u][v] = 1;
            graph[v][u] = 1; // неориентированный
        }
    }

    set<pair<int, int>> unionGraph; // тут  все ребра гамильтонова цикла
    vector<int> path;               // тут все вершины которые мы прошли
    vector<bool> visited(n, false); // проверка проходили мы вершины
    bool cycleFound = false;        // найден ли гам. цикл

    for (int start = 0; start < n; start++)
    {
        path.clear();                                // очищаем
        fill(visited.begin(), visited.end(), false); // чтобы все вершины не пройдены
        visited[start] = true;                       // стартовая строка - посетили
        path.push_back(start);                       // добавили в путь

        vector<int> stack = {start}; // для поиска соседей (Берём вершину 3 из стека (она на верхушке), ищем её соседей (0 и 2). Вершина 0 уже посещена, добавляем 2 в стек: Берём вершину 2 из стека, ищем её соседей (1 и 3). Вершина 3 уже посещена, 1 тоже, процесс завершён.)

        while (!stack.empty()) // пока есть элементы
        {
            int vertex = stack.back(); // берем верхушку(вершина которая добавлена в стек)
            stack.pop_back();          // удаляем ее чтобы

            if (path.size() == n) // проверяем прошли ли мы по всем путям
            {
                if (graph[path.back()][path[0]] == 1) // проверяем сущ. ли ребро соед. последнюю вершину с начальной
                {
                    for (int i = 0; i < n; i++)
                    {
                        int u = path[i];           // текущая вершина
                        int v = path[(i + 1) % n]; // след вершина
                        if (u > v)                 // сортируем чтобы избегать дубликатов
                            swap(u, v);
                        unionGraph.insert({u, v}); // добавляем, инсерт не дает добавить дубликаты
                    }
                    cycleFound = true; // найден гам. цикл
                }
                continue;
            }

            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && graph[vertex][i] == 1) // проверяем можно ли переместиться в вершину
                {
                    visited[i] = true;
                    path.push_back(i);  // добавляем в путь
                    stack.push_back(i); // добавляем в стек
                    break;
                }
            }
            if (stack.size() == path.size()) // если одинаковое количество вершин то нету новых для пути, удаляем последнюю вершину
            {
                path.pop_back();
            }
        }
    }

    // Вывод объединённого графа
    cout << "Рёбра объединённого графа: " << endl;
    if (!cycleFound)
    {
        cout << "Нет рёбер в объединённом графе" << endl;
    }
    else
    {
        for (auto &edge : unionGraph)
        {
            cout << edge.first + 1 << " - " << edge.second + 1 << endl; // Сдвиг на 1 для вывода
        }
    }

    return 0;
}
