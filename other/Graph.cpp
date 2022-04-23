#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

template<class T>
class Graph
{
private:
    vector<T> vertex_container;
    vector<vector<int>> adjacency_matrix;
    int count_of_vertex;
public:
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
    friend ostream& operator<<(ostream&, const Graph<int>&);
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
    int get_count_edges_not_oriented(){return get_count_edges_oriented()/2;}
};

ostream& operator<<(ostream& out, const Graph<int>& graph)
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


int main()
{
    setlocale(0, "");
    cout << right;
    Graph<int> graph = Graph<int>(8);
    for (int i = 0; i < graph.get_count_vertex(); i++)
    {
        graph.insert_vertex(i);
    }
    graph.insert_edge_not_oriented(0, 1, 9);
    graph.insert_edge_not_oriented(0, 7, 5);
    vector<int> a = graph.get_neighbours(0);
    cout << graph << "\n\n";
    for (auto i : a)
    {
        cout << i << " ";
    }
    {
        cout << " asdsadsadsadsa";
    }

    return 0;
}
