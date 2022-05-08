#pragma once

ostream& operator<<(ostream& out, const vector<zero_info>& vector)
{
    for_each(vector.begin(), vector.end(), [&out](const zero_info& object)->void 
        {
            out << "i = " << object.str << " j = " << object.col << " value = " << object.value << "\n";
        });
    return out;
}

ostream& operator<<(ostream& out, const vector<segment>& sections)
{
    for_each(sections.begin(), sections.end(), [&out](const segment& object)->void
        {
            out << object.num_from << "->" << object.num_to << " ";
        });
    return out;
}

ostream& operator<<(ostream& out, const vector<vector<int>> vect)
{
    int size = vect.size();
    out << setw(3) << "___+";
    for (int i = 1; i < size + 1; i++) out << "" << setw(3) << i << " ";
    out << setw(3) << endl;
    for (int k = 1, i = 0; i < size; i++, k++)
    {
        out << setw(3) << k << "|";
        for (int j = 0; j < size; j++)
        {
            if (vect[i][j] == -1) out << setw(3) << 'M' << " ";
            else out << setw(3) << vect[i][j] << " ";
        }
        out << setw(3) << endl;
    }
    return out;
}

template<class T>
Graph<T>::Graph(const int& count_of_vertex)
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

template<class T>
int Graph<T>::get_count_vertex() { return count_of_vertex; }

template<class T>
bool Graph<T>::is_full() { return count_of_vertex == vertex_container.size(); }

template<class T>
bool Graph<T>::is_empty() { return vertex_container.size() == 0; }

template<class T>
void Graph<T>::insert_vertex(const T & new_vertex)
{
    if (is_full())
    {
        cout << "Unable to add a vertex.\n";
        return;
    }
    vertex_container.push_back(new_vertex);
}

template<class T>
int Graph<T>::get_vertex_index(const T& to_find)
{
    if (is_empty()) return -1;
    int j = 0;
    for (auto i : vertex_container)
    {
        if (i == to_find) return j;
        ++j;
    }
    return -1;
}

template<class T>
int Graph<T>::get_weight_between(const T& vertex_1, const T& vertex_2)
{
    int index_v1 = get_vertex_index(vertex_1);
    int index_v2 = get_vertex_index(vertex_2);

    if (is_empty() || index_v1 == -1 || index_v2 == -1) return 0;

    return adjacency_matrix[index_v1][index_v2];
}

template<class T>
vector<T> Graph<T>::get_neighbours(const T& current)
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

template<class T>
int Graph<T>::get_count_edges_oriented()
{
    if (is_empty()) return 0;
    int count = 0;
    int size = vertex_container.size();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (adjacency_matrix[i][j] != 0) ++count;
        }
    }
    return count;
}

template<class T>
int Graph<T>::get_count_edges_not_oriented() { return get_count_edges_oriented() / 2; }

void fill_graph_hard(Graph<int>& graph)
{
    for (int i = 1; i < 7; ++i) graph.insert_vertex(i);

    //graph.insert_edge_not_oriented(1, 2, 6);
    //graph.insert_edge_not_oriented(1, 3, 4);
    //graph.insert_edge_not_oriented(1, 4, 8);
    //graph.insert_edge_not_oriented(1, 5, 7);
    //graph.insert_edge_not_oriented(1, 6, 14);
    //graph.insert_edge_not_oriented(2, 3, 7);
    //graph.insert_edge_not_oriented(2, 4, 11);
    //graph.insert_edge_not_oriented(2, 5, 7);
    //graph.insert_edge_not_oriented(2, 6, 10); // example net
    //graph.insert_edge_not_oriented(3, 4, 4);
    //graph.insert_edge_not_oriented(3, 5, 3);
    //graph.insert_edge_not_oriented(3, 6, 10);
    //graph.insert_edge_not_oriented(4, 5, 5);
    //graph.insert_edge_not_oriented(4, 6, 11);
    //graph.insert_edge_not_oriented(5, 6, 7);

    //graph.insert_edge_not_oriented(4, 3, 3);
    //graph.insert_edge_not_oriented(3, 5, 21);
    //graph.insert_edge_not_oriented(5, 2, 53);
    //graph.insert_edge_not_oriented(2, 6, 45);
    //graph.insert_edge_not_oriented(6, 1, 34); // true
    //graph.insert_edge_not_oriented(1, 4, 5);
    //graph.insert_edge_not_oriented(1, 3, 18);
    //graph.insert_edge_not_oriented(2, 1, 12);
    //graph.insert_edge_not_oriented(2, 3, 16);
    //graph.insert_edge_not_oriented(1, 5, 30);
    //graph.insert_edge_not_oriented(2, 4, 35);
    //graph.insert_edge_not_oriented(3, 6, 27);
    //graph.insert_edge_not_oriented(4, 5, 32);
    //graph.insert_edge_not_oriented(4, 6, 52);
    //graph.insert_edge_not_oriented(6, 5, 74);


    //graph.insert_edge_oriented(4, 3, 3);
    //graph.insert_edge_oriented(3, 5, 21);
    //graph.insert_edge_oriented(5, 2, 53);
    //graph.insert_edge_oriented(2, 6, 45);
    //graph.insert_edge_oriented(6, 1, 34);
    //graph.insert_edge_oriented(1, 4, 5);
    //graph.insert_edge_oriented(1, 3, 18);
    //graph.insert_edge_oriented(2, 1, 12);
    //graph.insert_edge_oriented(2, 3, 16);


    graph.insert_edge_oriented(1, 2, 5);
    graph.insert_edge_oriented(1, 3, 11);
    graph.insert_edge_oriented(1, 4, 9);
    graph.insert_edge_oriented(2, 3, 8);
    graph.insert_edge_oriented(2, 4, 7);
    graph.insert_edge_oriented(3, 4, 8);
    graph.insert_edge_oriented(2, 1, 10); // example
    graph.insert_edge_oriented(3, 1, 7);
    graph.insert_edge_oriented(4, 1, 12);
    graph.insert_edge_oriented(4, 2, 6);
    graph.insert_edge_oriented(3, 2, 14);
    graph.insert_edge_oriented(4, 3, 15);
}

template<class T>
vector<vector<int>> Graph<T>::get_matrix() { return vector<vector<int>>(adjacency_matrix); }

void find_str_mins(const vector<vector<int>> matrix, vector<int>& mins)
{
    int size = matrix.size();
    while (!mins.empty()) mins.pop_back();
    for (int i = 0; i < size; ++i)
    {   
        int min = 2147483647;
        for (int j = 0; j < size; ++j)
        {
            if (matrix[i][j] < min && matrix[i][j] != -1)
            {
                min = matrix[i][j];
            }
        }
        if (min != 2147483647) mins.push_back(min);
        else mins.push_back(0);
    }
}

void prepare_matrix(vector<vector<int>>& matrix)
{
    int size = matrix.size();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (matrix[i][j] == 0) matrix[i][j] = -1;
        }
    }
}

void reduction_str(const vector<int> mins, vector<vector<int>>& matrix)
{
    int size = matrix.size();
    for (int i = 0; i < size; ++i)
    {
        int value_to_erase = mins[i];
        for (int j = 0; j < size; ++j)
        {
            if (matrix[i][j] != -1) matrix[i][j] -= value_to_erase;
        }
    }
}

void reduction_col(const vector<int> mins, vector<vector<int>>& matrix)
{
    int size = matrix.size();
    for (int i = 0; i < size; ++i)
    {
        int value_to_erase = mins[i];
        for (int j = 0; j < size; ++j)
        {
            if (matrix[j][i] != -1) matrix[j][i] -= value_to_erase;
        }
    }
}

void find_col_mins(const vector<vector<int>> matrix, vector<int>& mins)
{
    int size = matrix.size();
    while (!mins.empty()) mins.pop_back();
    for (int i = 0; i < size; ++i)
    {
        int min = 2147483647;
        for (int j = 0; j < size; ++j)
        {
            if (matrix[j][i] < min && matrix[j][i] != -1)
            {
                min = matrix[j][i];
            }
        }
        if (min != 2147483647) mins.push_back(min);
        else mins.push_back(0);
    }
}

int find_value_for_zero(const int str, const int col, const vector<vector<int>>& matrix)
{
    int size = matrix.size();
    int min_str = 2147483647;
    int min_col = 2147483647;
    bool find_min_str = false; bool find_min_col = false;
    for (int i = 0; i < size; ++i)
    {
        if (matrix[str][i] < min_str && matrix[str][i] != -1 && col != i)
        {
            min_str = matrix[str][i];
            find_min_str = true;
        }
        if (matrix[i][col] < min_col && matrix[i][col] != -1 && str != i)
        {
            min_col = matrix[i][col];
            find_min_col = true;
        }
    }
    if (find_min_str && find_min_col) return min_str + min_col;
    else if (find_min_str) return min_str;
    else if (find_min_col) return min_col;
    else return 0;

}

vector<zero_info> handling_zero(const vector<vector<int>>& matrix)
{
    vector<zero_info> container_for_zero;
    int size = matrix.size();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (matrix[i][j] == 0)
            {
                zero_info temp;
                temp.str = i; temp.col = j; temp.value = find_value_for_zero(i, j, matrix);
                container_for_zero.push_back(temp);
            }
        }
    }
    return container_for_zero;
}

zero_info get_max_rate(const vector<zero_info>& container)
{
    int max = -1;
    int index = 0;
    int current_index = 0;
    for_each(container.begin(), container.end(), [&](const zero_info object)->void 
        {
            if (object.value > max)
            {
                max = object.value;
                index = current_index;
            }
            current_index++;
        });
    return container[index];
}

void mark_visit(const int row, const int col, vector<vector<int>>& matrix)
{
    int size = matrix.size();
    matrix[col][row] = -1;
    for (int i = 0; i < size; ++i)
    {
        matrix[row][i] = matrix[i][col] = -1;
    }
}

bool ways_obvious(const vector<vector<int>>& matrix)
{
    int size = matrix.size();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (matrix[i][j] != 0 && matrix[i][j] != -1) return false;
        }
    }
    return true;
}

vector<zero_info> get_zeros_obvious_ways(const vector<vector<int>>& matrix)
{
    vector<zero_info> container_for_zero;
    int size = matrix.size();
    for (int i = 0; i < size; ++i)
    {
        bool is_found = false;
        for (int j = 0; j < size; ++j)
        {
            if (matrix[i][j] == 0 && !is_found)
            {
                zero_info temp;
                temp.str = i; temp.col = j;
                is_found = true;
                container_for_zero.push_back(temp);
            }
        }
    }
    return container_for_zero;
}

bool correct(const vector<vector<int>>& matrix)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix.size(); ++j)
        {
            if (matrix[i][j] == 0 && i != j) return false;
        }
    }
    return true;
}

void fill_graph(Graph<int>& graph)
{
    int count, vertex, edge_weight, from_vertex, to_vertex;
    for (int i = 0; i < graph.get_count_vertex(); ++i)
    {
        cout << "¬ведите вершину графа #" << i + 1 << ": "; cin >> vertex; graph.insert_vertex(vertex);
    }

    int i = 0;
    int key;
    do
    {
        cout << "If graph oriented input 1, else input 0: "; cin >> key;
    } while (key != 1 && key != 0);
    switch (key)
    {
    case 0:
        while (!correct(graph.get_matrix()))
        {
            cout << "¬ведите исходную вершину графа #" << i + 1 << ": "; cin >> from_vertex;
            cout << "¬ведите конечную вершину графа #" << i + 1 << ": "; cin >> to_vertex;
            cout << "¬ведите вес ребра графа #" << i + 1 << ": "; cin >> edge_weight;
            cout << "\n\n";
            graph.insert_edge_not_oriented(from_vertex, to_vertex, edge_weight);
            cout << graph << "\n\n";
            i++;
        }
        break;
    case 1:
        while (!correct(graph.get_matrix()))
        {
            cout << "¬ведите исходную вершину графа #" << i + 1 << ": "; cin >> from_vertex;
            cout << "¬ведите конечную вершину графа #" << i + 1 << ": "; cin >> to_vertex;
            cout << "¬ведите вес ребра графа #" << i + 1 << ": "; cin >> edge_weight;
            cout << "\n\n";
            graph.insert_edge_oriented(from_vertex, to_vertex, edge_weight);
            cout << graph << "\n\n";
            i++;
        }
        break;
    default:
        break;
    }


}

int find(const vector<segment>& sections, const int to_find)
{
    int index = -1;
    int current_index = 0;
    for_each(sections.begin(), sections.end(), [&index, &to_find, &current_index](const segment& object)->void
        {
            if (object.num_from == to_find)
            {
                index = current_index;
            }
            current_index++;
        }
    );
    return index;
}



vector<segment> create_way(vector<segment>& sections)
{
    int start_number;
    do
    {
        cout << "Input number of start vertex: "; cin >> start_number;
    } while (start_number <= 0 || start_number > sections.size());
    int size = sections.size();
    vector<segment> optimal_way;
    optimal_way.push_back(sections[find(sections, start_number)]);
    segment previous = optimal_way[0];
    for (int i = 1; i < size; ++i)
    {
        if (find(sections, previous.num_to) != -1)
        {
            optimal_way.push_back(sections[find(sections, previous.num_to)]);
            previous = optimal_way[i];
        }
    }
    return optimal_way;
}


void get_best_way(vector<segment>& sections, const vector<vector<int>>& matrix)
{
    vector<segment> vect = create_way(sections);
    int length = 0;
    for_each(vect.begin(), vect.end(), [&length, &matrix](const segment& object)->void
        {
            length += matrix[object.num_from - 1][object.num_to - 1];
            cout << matrix[object.num_from - 1][object.num_to - 1] << " ";
        });
    cout << "Optimal way is " << vect << "\nLength: " << length << "\n";
}

template<class T>
void process_voyager(Graph<T>& graph)
{
    vector<int> str_mins;
    vector<int> col_mins;
    vector<segment> sections; // vector for segments of optimal way
    cout << "Basic graph: \n" << graph << "\n";
    vector<vector<int>> edited_matrix = graph.get_matrix(); // this vector is a copy of adjacency matrix will be edited further 
    prepare_matrix(edited_matrix); // fill all 0 with NAN == M == -1 label
    //cout << "Edited graph: \n" << edited_matrix;

    // PROCESSING OF SEGMENT SEARCH //

    //while (sections.size() != graph.get_count_vertex() && !ways_obvious(edited_matrix))
    while (!ways_obvious(edited_matrix))
    {
        //cout << "\nMinimums in rows: ";
        find_str_mins(edited_matrix, str_mins); // fill vector with mins of strs
        //for (auto i : str_mins){cout << i << " ";}
        reduction_str(str_mins, edited_matrix);
        //cout << "\n\nAfter rows reduction:\n" << edited_matrix << "\nMinimums in cols: ";

        find_col_mins(edited_matrix, col_mins); // fill vector with mins of cols
        //for (auto i : col_mins){cout << i << " ";}
        reduction_col(col_mins, edited_matrix);
        //cout << "\n\nAfter cols reduction:\n" << edited_matrix << "\n";

        if (ways_obvious(edited_matrix)) break;

        vector<zero_info> vector_of_0 = handling_zero(edited_matrix);
        zero_info max_value_zero = get_max_rate(vector_of_0);
        sections.push_back(segment(max_value_zero.str, max_value_zero.col));
        if (!ways_obvious(edited_matrix)) mark_visit(max_value_zero.str, max_value_zero.col, edited_matrix);

        //cout << "Now we have a way from " << max_value_zero.str+1 << " vertex to " << max_value_zero.col + 1 << " vertex.\n";
        //cout << "Marked visited:\n" << edited_matrix;
        //cout << endl << endl << vector_of_0; 
    }


    // ADDING OBVIOUS WAYS TO SEGMENT CONTAINER 

    vector<zero_info> vect = get_zeros_obvious_ways(edited_matrix);
    for_each(vect.begin(), vect.end(), [&](const zero_info& object)->void
    {
        sections.push_back(segment(object.str, object.col));
    });
    get_best_way(sections, graph.get_matrix());
}

