#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;


bool check(vector<int> vect);

template<class T>
class Graph
{
private:
    queue<T> vertex_queue;
    vector<T> vertex_container;
    vector<vector<int>> adjacency_matrix;
    int count_of_vertex;
public:
    Graph() : Graph(0)
    {
    }
    Graph(const int& count_of_vertex)
    {
        this->count_of_vertex = count_of_vertex;
        adjacency_matrix = vector<vector<int>>(count_of_vertex, vector<int>(count_of_vertex));
        for (int i = 0; i < this->count_of_vertex; ++i)
        {
            for (int j = 0; j < this->count_of_vertex; ++j)
            {
                adjacency_matrix[i][j] = 0;
            }
        }
    }
    template<class T1>
    friend ostream& operator<<(ostream&, const Graph<T1>&);
    int get_count_vertex() { return count_of_vertex; }
    bool is_full() { return count_of_vertex == vertex_container.size(); }
    bool is_empty() { return vertex_container.size() == 0; }
    void insert_vertex(const T& new_vertex)
    {
        if (is_full())
        {
            cout << "Невозможно добавить вершину.\n";
            return;
        }
        vertex_container.push_back(new_vertex);
    }
    int get_vertex_index(const T& to_find)
    {
        if (is_empty()) return -1;
        int j = 0;
        for (auto i : vertex_container)
        {
            if (i == to_find)
            {
                return j;
            }
            j++;
        }
        return -1;
    }
    void insert_edge_not_oriented(const T& vertex_1, const T& vertex_2, int value = 1)
    {
        if (vertex_1 == vertex_2)
        {
            cout << "Петлю создавать нельзя!\n"; return;
        }
        if (!(get_vertex_index(vertex_1) != -1 && get_vertex_index(vertex_2) != -1)) // проверка на существование обеих вершин
        {
            cout << "Невозможно создать ребро.\n"; return;
        }

        int index_v1 = get_vertex_index(vertex_1);
        int index_v2 = get_vertex_index(vertex_2);

        if (adjacency_matrix[index_v1][index_v2] != 0)
        {
            cout << "Невозможно создать ребро, оно уже есть.\n"; return;
        }

        adjacency_matrix[index_v1][index_v2] = adjacency_matrix[index_v2][index_v1] = value;
    }
    void insert_edge_oriented(const T& vertex_1_from, const T& vertex_2_to, int value = 1)
    {
        if (vertex_1_from == vertex_2_to)
        {
            cout << "Петлю создавать нельзя!\n"; return;
        }
        if (!(get_vertex_index(vertex_1_from) != -1 && get_vertex_index(vertex_2_to) != -1)) // проверка на существование обеих вершин
        {
            cout << "Невозможно создать ребро.\n"; return;
        }

        int index_v1_from = get_vertex_index(vertex_1_from);
        int index_v2_to = get_vertex_index(vertex_2_to);

        if (adjacency_matrix[index_v1_from][index_v2_to] != 0)
        {
            cout << "Невозможно создать ребро, оно уже есть.\n"; return;
        }

        adjacency_matrix[index_v1_from][index_v2_to] = value;
    }
    int get_weight_between(const T& vertex_1, const T& vertex_2)
    {
        int index_v1 = get_vertex_index(vertex_1);
        int index_v2 = get_vertex_index(vertex_2);

        if (is_empty() || index_v1 == -1 || index_v2 == -1) return 0;

        return adjacency_matrix[index_v1][index_v2];
    }
    vector<T> get_neighbours(const T& current)
    {
        vector<T> vect;
        int current_index = get_vertex_index(current);
        if (current_index == -1) return vect;
        for (int j = 0; j < vertex_container.size(); j++)
        {
            if (adjacency_matrix[current_index][j] != 0) vect.push_back(vertex_container[j]);
        }
        return vect;
    }
    int get_count_edges_oriented()
    {
        if (is_empty()) return 0;
        int count = 0;
        int size = vertex_container.size();
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (adjacency_matrix[i][j] != 0)
                {
                    ++count;
                }
            }
        }
        return count;
    }
    int get_count_edges_not_oriented(){ return get_count_edges_oriented()/2; }
    void parse_deep(const T& start_vertex, bool* visited_verts)
    {
        cout << "Обработка вершины " << start_vertex << endl;
        visited_verts[get_vertex_index(start_vertex)] = true;
        vector<T> neighbours = get_neighbours(start_vertex);
        for (int i = 0; i < neighbours.size(); ++i)
        {
            if (visited_verts[get_vertex_index(neighbours[i])] == 0)
            {
                parse_deep(neighbours[i], visited_verts);
            }
        }
    }
    void parse_wide(const T& start_vertex, bool* visited_verts)
    {
        if (visited_verts[get_vertex_index(start_vertex)] == false)
        {
            vertex_queue.push(start_vertex);
            cout << "Обработка вершины " << start_vertex << endl;
            visited_verts[get_vertex_index(start_vertex)] = true;
        }
        vector<T> neighbours = get_neighbours(start_vertex);
        vertex_queue.pop();
        for (int i = 0; i < neighbours.size(); ++i)
        {
            if (visited_verts[get_vertex_index(neighbours[i])] != true)
            {
                vertex_queue.push(neighbours[i]);
                visited_verts[get_vertex_index(neighbours[i])] = true;
                cout << "Обработка вершины " << neighbours[i] << endl;
            }
        }
        if (vertex_queue.empty()) return;
        parse_wide(vertex_queue.front(), visited_verts);
    }

    void lowest_way(T& start_vertex)                                                    // Dijkstra algorithm
    {
        int start_index = get_vertex_index(start_vertex);

        if (is_empty() || start_index == -1)                                            // is graph and start vertex exist?
        {
            cout << "Ошибка.\n"; return;
        }

        int count_vertex = get_count_vertex();  
        
        for (int i = 0; i < count_vertex; ++i)                                          // any negative values of edges?
        {
            for (int j = 0; j < count_vertex; ++j)
            {
                if (adjacency_matrix[i][j] < 0)
                {
                    cout << "Метод не работает для графа с отрицательными путями.\n"; 
                    return;
                }
            }
        }

        vector<T> neighbours;
        vector<bool> visited_verts(count_vertex);                                       // vector for check visited verts
        vector<int> weights(count_vertex);                                              // vector for weights
        fill(weights.begin(), weights.end(), 999999);
        weights[start_index] = 0;                                                       // start vertex has weight = 0
        T current_vertex = start_vertex;

        while (!check(weights))                                                // 1 loop = process to 1 vertex
        {
            int current_index = get_vertex_index(current_vertex);
            neighbours = get_neighbours(current_vertex);                            // vector filled neighbours of current vertex
            int current_weight = weights[current_index];
            T* closest_neighbour = nullptr;
            int min_weight = 999999;

            for (int i = 0; i < neighbours.size(); ++i)
            {
                T neighbour_vertex = neighbours[i];
                int neighbour_index = get_vertex_index(neighbour_vertex);
                int neighbour_weight = get_weight_between(current_vertex, neighbour_vertex);

                if (current_weight + neighbour_weight < weights[neighbour_index])
                {
                    weights[neighbour_index] = current_weight + neighbour_weight;
                }

                if (visited_verts[neighbour_index] != true && weights[neighbour_index] < min_weight) // to find closest vertex
                {
                    min_weight = weights[neighbour_index];
                    closest_neighbour = &neighbours[i];
                }
            }
            visited_verts[current_index] = true;
            if (closest_neighbour != nullptr)
            {
                current_vertex = *closest_neighbour;
            }
        }
        for (int i = 0; i < start_index; ++i)
        {
            cout << "Кратчайшее расстояние от вершины " << start_vertex << " до вершины "
                << vertex_container[i] << " равно " << weights[i] << "\n";
        }
        for (int i = start_index; i < vertex_container.size(); ++i)
        {
            cout << "Кратчайшее расстояние от вершины " << start_vertex << " до вершины "
                << vertex_container[i] << " равно " << weights[i] << "\n";
        }
    }
};

template<class T1>
ostream& operator<<(ostream& out, const Graph<T1>& graph)
{
    int size = graph.vertex_container.size();
    out << setw(3) <<  "___+";
    for (int i = 1; i < size + 1; i++) out << "" << setw(3) << i << " ";
    out << setw(3) << endl;
    for (int k = 1, i = 0; i < size; i++, k++)
    {   
        out << setw(3) << k << "|";
        for (int j = 0; j < size; j++)
        {
            out << setw(3) << graph.adjacency_matrix[i][j] << " ";
        }
        out << setw(3) << endl;
    }
    return out;
}

bool check(vector<int> vect)
{
    for (auto i : vect) if (i == 999999) return false;
    return true;
}


int main()
{
    setlocale(0, "");
    cout << right;
    /*   int count, vertex, edge_weight, from_vertex, to_vertex;
       for (int i = 0; i < count; ++i)
       {
           cout << "Введите вершину графа #" << i+1 << ": "; cin >> vertex; graph.insert_vertex(vertex);
       }
       cout << "\n\nВведите количество ребер графа: "; cin >> count;
       for (int i = 0; i < count; ++i)
       {
           cout << "Введите исходную вершину графа #" << i+1 << ": "; cin >> from_vertex;
           cout << "Введите конечную вершину графа #" << i+1 << ": "; cin >> to_vertex;
           cout << "Введите вес ребра графа #" << i+1 << ": "; cin >> edge_weight;
           cout << endl << endl;
           graph.insert_edge_not_oriented(from_vertex, to_vertex, edge_weight);
       }
       cout << graph;

       fill(visited_verts, visited_verts + 20, false);*/

    int index = 3;                          //
    int count = 6;                          // hardcode for test
    Graph<int> graph(count);
    for (int i = 1; i < 7; ++i) graph.insert_vertex(i);
    graph.insert_edge_not_oriented(4, 3, 3);
    graph.insert_edge_not_oriented(3, 5, 21);
    graph.insert_edge_not_oriented(5, 2, 53);
    graph.insert_edge_not_oriented(2, 6, 45);
    graph.insert_edge_not_oriented(6, 1, 34);
    graph.insert_edge_not_oriented(1, 4, 5);
    graph.insert_edge_not_oriented(1, 3, 18);
    graph.insert_edge_not_oriented(2, 1, 12);
    graph.insert_edge_not_oriented(2, 3, 16);
    // cout << "\n\nStart: "; cin >> index;
 
    cout << graph;

    //bool* visited_verts = new bool[count];
    //fill(visited_verts, visited_verts + count, false);
    //graph.parse_deep(index, visited_verts);
    //graph.parse_wide(index, visited_verts);
    cout << endl << endl;
    graph.lowest_way(index);
    //delete[] visited_verts;
    return 0;
}