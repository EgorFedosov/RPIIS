#include <iostream>
using namespace std;

// 3.6 матрица инцидентности для неопределенного графа

int main()
{
    int n, m;
    cout << "Введите количество вершин: ";
    cin >> n;
    cout << "Введите количество рёбер: ";
    cin >> m;

    int graph[m][2]; // для одного ребра пара вершин

    cout << "Введите рёбра (пары вершин):\n";
    for (int i = 0; i < m; i++)
    {
        cin >> graph[i][0] >> graph[i][1]; // 0-0  0-1   1-0  1-1
    }

    int mat[m][n];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = 0;
        }

        mat[i][graph[i][0] - 1] = 1; // единичку в нужный столбик
        mat[i][graph[i][1] - 1] = 1;
    }

    cout << "\nМатрица инцидентности для графа:\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
