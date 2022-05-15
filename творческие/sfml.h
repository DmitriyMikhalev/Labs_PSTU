
using namespace sf;
class Node : public CircleShape
{
public:
    Node(int radius) : CircleShape(radius)
    {
        x_pos = y_pos = 0;
    }

    float x_pos;
    float y_pos;
};

//bool move(CircleShape& obj, RenderWindow& Window)
//{
//    bool flag = false;
//    Vector2f node_coords = obj.getPosition();
//    RectangleShape rectangle;
//    rectangle.setPosition(Vector2f(node_coords.x, node_coords.y));
//    rectangle.setSize(Vector2f(obj.getRadius() * sqrt(3), obj.getRadius() * sqrt(3)));
//
//    if (rectangle.getGlobalBounds().contains(Mouse::getPosition(Window).x, Mouse::getPosition(Window).y))
//    {
//        while (Mouse::isButtonPressed(Mouse::Button::Left))
//        {
//             obj.setPosition(Mouse::getPosition(Window).x - obj.getRadius(), Mouse::getPosition(Window).y - obj.getRadius());
//             flag = true;
//        }
//    }
//    return flag;
//}

bool move(Node& obj, RenderWindow& Window)
{
    bool flag = false;
    Vector2f node_coords = obj.getPosition();
    RectangleShape rectangle;
    rectangle.setPosition(Vector2f(node_coords.x, node_coords.y));
    rectangle.setSize(Vector2f(obj.getRadius() * sqrt(3), obj.getRadius() * sqrt(3)));

    if (rectangle.getGlobalBounds().contains(Mouse::getPosition(Window).x, Mouse::getPosition(Window).y))
    {
        while (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            obj.setPosition(Mouse::getPosition(Window).x - obj.getRadius(), Mouse::getPosition(Window).y - obj.getRadius());
            flag = true;
        }
    }
    return flag;
}

void draw_vertex(const float& x, const float& y, const string& message, RenderWindow& Window)
{
    Vector2f vect(x, y);
    Node node(25);
    node.setPosition(vect);
    node.setFillColor(Color::Green);

    Font font;
    font.loadFromFile("timesnewromanpsmt.ttf");
    Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(20);
    text.setFillColor(Color::Black);

    Vector2f pos = node.getPosition();
    int radius = node.getRadius();
    text.setPosition(x + radius * 0.8, y + radius * 0.5);

    Window.draw(node);
    Window.draw(text);
}

void draw_line(vector<Vertex>& vect, RenderWindow& Window)
{
    Window.draw(&vect[0], vect.size(), Lines);
}

void draw_text(vector<Text>& vect, RenderWindow& Window)
{
    for_each(vect.begin(), vect.end(), [&Window](Text& object)->void 
        {
            Window.draw(object);
        });
}

void create_new_node(vector<Node>& shapes, const int RADIUS)
{
    Node temp(RADIUS);
    shapes.push_back(temp);
}

// lines[i] contains 1 vector, which has 2 objects: 
//                                                  lines[i][0] - first point
//                                                  lines[i][1] - second point
//                                                  and this is a line

void create_lines(const vector<vector<int>>& matrix, vector<vector<Vertex>>& lines, const vector<Node>& shapes)
{
    while (lines.size()) lines.pop_back();
    const int size = matrix.size();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (matrix[i][j] != 0 && matrix[i][j] != -1)
            {
                Vertex pos_1 = Vertex(Vector2f(shapes[i].getPosition().x + shapes[i].getRadius(), shapes[i].getPosition().y + shapes[i].getRadius()), Color::Black);
                Vertex pos_2 = Vertex(Vector2f(shapes[j].getPosition().x + shapes[j].getRadius(), shapes[j].getPosition().y + shapes[j].getRadius()), Color::Black);
                vector<Vertex> temp_vect = {pos_1, pos_2};
                lines.push_back(temp_vect);
            }
        }
    }
}

void create_text(const vector<vector<int>>& matrix, vector<Text>& texts, const vector<Node>& shapes, const Font& font)
{
    while (texts.size()) texts.pop_back();
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix.size(); ++j)
        {
            if (matrix[i][j] != 0 && matrix[i][j] != -1)
            {

                Text text;
                text.setFont(font);
                text.setCharacterSize(15);
                text.setFillColor(Color::Black);
                text.setString(to_string(matrix[i][j])); 
                Vector2f vect_1 = shapes[i].getPosition();
                Vector2f vect_2 = shapes[j].getPosition();
                Vector2f pos;
                pos.x = (vect_1.x + vect_2.x) / 2;
                pos.y = (vect_1.y + vect_2.y) / 2;
                text.setPosition(pos);
                //cout << "x = " << pos.x << " y = " << pos.y << '\n';
                texts.push_back(text);
                
            }
        }
    }
    
}


//template<class T>
//void create_text(Graph<T>& graph, const vector<Node>& shapes, vector<Text>& texts)
//{
//    while (texts.size()) texts.pop_back();
//    vector<vector<int>> matrix = graph.get_matrix();
//    for (int i = 0; i < matrix.size(); ++i)
//    {
//        for (int j = 0; j < matrix.size(); ++j)
//        {
//            if (matrix[i][j] != 0 && matrix[i][j] != -1)
//            {
//                Font font;
//                font.loadFromFile("timesnewromanpsmt.ttf");
//                Text text;
//                text.setFont(font);
//                text.setCharacterSize(15);
//                text.setFillColor(Color::Black);
//                text.setString(to_string(matrix[i][j]));
//                Vector2f vect_1 = shapes[i].getPosition();
//                Vector2f vect_2 = shapes[j].getPosition();
//                Vector2f pos;
//                pos.x = (vect_1.x + vect_2.x) / 2;
//                pos.y = (vect_1.y + vect_2.y) / 2;
//                text.setPosition(pos);
//                texts.push_back(text);
//            }
//        }
//    }
//}