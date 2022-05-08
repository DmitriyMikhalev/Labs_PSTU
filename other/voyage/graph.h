#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <functional>
#include <iterator>
using namespace std;

template<class T>
class Graph
{
private:
    queue<T> vertex_queue;
    vector<T> vertex_container;
    vector<vector<int>> adjacency_matrix;
    int count_of_vertex;
public:
    Graph() : Graph(0){}
    Graph(const int& count_of_vertex);
    template<class T1>
    friend ostream& operator<<(ostream&, const Graph<T1>&);
    int get_count_vertex();
    bool is_full();
    bool is_empty();
    void insert_vertex(const T& new_vertex);
    int get_vertex_index(const T& to_find);
    void insert_edge_not_oriented(const T& vertex_1, const T& vertex_2, int value = 1)
    {
        if (vertex_1 == vertex_2)
        {
            cout << "Петлю создавать нельзя!\n"; return;
        }
        if (!(get_vertex_index(vertex_1) != -1 && get_vertex_index(vertex_2) != -1)) // both vertexes exist?
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
        if (!(get_vertex_index(vertex_1_from) != -1 && get_vertex_index(vertex_2_to) != -1)) // both vertexes exist?
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
    int get_weight_between(const T& vertex_1, const T& vertex_2);
    vector<T> get_neighbours(const T& current);
    int get_count_edges_oriented();
    int get_count_edges_not_oriented();
    vector<vector<int>> get_matrix();
    /*void parse_deep(T& start_vertex, bool* visited_verts)
    {
        cout << "Processing vertex " << start_vertex << endl;
        visited_verts[get_vertex_index(start_vertex)] = true;
        vector<T> neighbours = get_neighbours(start_vertex);
        for (int i = 0; i < neighbours.size(); ++i)
        {
            if (visited_verts[get_vertex_index(neighbours[i])] == 0)
            {
                parse_deep(neighbours[i], visited_verts);
            }
        }
    }*/
    /*void parse_wide(T& start_vertex, bool* visited_verts)
    {
        if (visited_verts[get_vertex_index(start_vertex)] == false)
        {
            vertex_queue.push(start_vertex);
            cout << "Processing vertex " << start_vertex << endl;
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
    }*/
};

template<class T1>
ostream& operator<<(ostream& out, const Graph<T1>& graph)
{
    int size = graph.vertex_container.size();
    out << setw(3) << "___+";
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

class zero_info
{
public:
    int str   = -1; // i 
    int col   = -1; // j
    int value = -1; // rate
    zero_info(const int i, const int j)
    {
        str = i; col = j;
    }
    zero_info() {};
};

class segment
{
public:
    int num_from; // num of start vertex
    int num_to;   // num of finish vertex
    segment(const int index_from, const int index_to){ num_from = index_from + 1; num_to = index_to + 1; }
    bool operator>(const segment& other)
    {
        if (num_from > other.num_from) return true;
        return false;
    }
    bool operator<(const segment& other) {return !operator>(other);}
    bool operator>=(const segment& other)
    {
        if (num_from >= other.num_from) return true;
        return false;
    }
    bool operator<=(const segment& other)
    {
        if (num_from <= other.num_from) return true;
        return false;
    }
    bool operator==(const segment& other)
    {
        if (num_to == other.num_to && num_from == other.num_from) return true;
        return false;
    }
};
