#pragma once
#include "graph.h"
#include "methods.h"


int main()
{
    setlocale(0, "");
    cout << right;
    int count;
    do
    {
        cout << "Введите количество вершин графа: "; cin >> count;
    } while (count <= 0);
    Graph<int> graph(count);
    fill_graph(graph);
    process_voyager(graph);
    return 0;
}