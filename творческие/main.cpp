#pragma once
#include "graph.h"
#include "methods.h"
#include "SFML/Graphics.hpp"
#include "sfml.h"
#include <cmath>
using namespace sf;

const int WIDTH = 1200;
const int HEIGHT = 800;
const int RADIUS = 30;

vector<Node> shapes;
vector<vector<Vertex>> lines;
vector<RectangleShape> buttons;
vector<Text> text_buttons;
vector<Text> texts;
vector<Text> test;


int main()
{
    cout << right;
    Graph<int> graph(5);
    fill_graph_hard(graph);
    RenderWindow Window(VideoMode(WIDTH, HEIGHT), "Voyager", Style::Close | Style::Titlebar);
    for (int i = 0; i < graph.get_count_vertex(); ++i) create_new_node(shapes, RADIUS);

    shapes[0].setPosition(Vector2f(100, 100));
    shapes[1].setPosition(Vector2f(100, 200));
    shapes[2].setPosition(Vector2f(200, 300));
    shapes[3].setPosition(Vector2f(400, 50));
    shapes[4].setPosition(Vector2f(500, 300));

    RectangleShape button_add(Vector2f(200, 40));
    button_add.setFillColor(Color::Green);
    button_add.setPosition(10, 750);

    RectangleShape button_delete = button_add;
    button_delete.setPosition(230, 750);

    RectangleShape button_show_matrix = button_add;
    button_show_matrix.setPosition(450, 750);

    RectangleShape button_get_answer = button_add;
    button_get_answer.setPosition(670, 750);

    buttons.push_back(button_add);
    buttons.push_back(button_delete);
    buttons.push_back(button_show_matrix);
    buttons.push_back(button_get_answer);

    Font font;
    font.loadFromFile("timesnewromanpsmt.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(Color::Black);

    text.setString("Add vertex");
    text.setPosition(Vector2f(55, 755));
    text_buttons.push_back(text);

    text.setString("Delete vertex");
    text.setPosition(Vector2f(270, 755));
    text_buttons.push_back(text);

    text.setString("Show matrix");
    text.setPosition(Vector2f(495, 755));
    text_buttons.push_back(text);

    text.setString("Get answer");
    text.setPosition(Vector2f(720, 755));
    text_buttons.push_back(text);

    vector<vector<Vertex>> lines_buttons =
    {
        {Vertex(Vector2f(10, 790), Color::Black), Vertex(Vector2f(10, 750), Color::Black)},
        {Vertex(Vector2f(210, 790), Color::Black), Vertex(Vector2f(210, 750), Color::Black)},
        {Vertex(Vector2f(230, 790), Color::Black), Vertex(Vector2f(230, 750), Color::Black)},
        {Vertex(Vector2f(430, 790), Color::Black), Vertex(Vector2f(430, 750), Color::Black)},
        {Vertex(Vector2f(450, 790), Color::Black), Vertex(Vector2f(450, 750), Color::Black)},
        {Vertex(Vector2f(650, 790), Color::Black), Vertex(Vector2f(650, 750), Color::Black)},
        {Vertex(Vector2f(670, 790), Color::Black), Vertex(Vector2f(670, 750), Color::Black)},
        {Vertex(Vector2f(870, 790), Color::Black), Vertex(Vector2f(870, 750), Color::Black)},

        {Vertex(Vector2f(10, 750), Color::Black), Vertex(Vector2f(210, 750), Color::Black)},
        {Vertex(Vector2f(230, 750), Color::Black), Vertex(Vector2f(430, 750), Color::Black)},
        {Vertex(Vector2f(450, 750), Color::Black), Vertex(Vector2f(650, 750), Color::Black)},
        {Vertex(Vector2f(670, 750), Color::Black), Vertex(Vector2f(870, 750), Color::Black)},

        {Vertex(Vector2f(10, 790), Color::Black), Vertex(Vector2f(210, 790), Color::Black)},
        {Vertex(Vector2f(230, 790), Color::Black), Vertex(Vector2f(430, 790), Color::Black)},
        {Vertex(Vector2f(450, 790), Color::Black), Vertex(Vector2f(650, 790), Color::Black)},
        {Vertex(Vector2f(670, 790), Color::Black), Vertex(Vector2f(870, 790), Color::Black)}
    };


    create_lines(graph.get_matrix(), lines, shapes);
    create_text(graph.get_matrix(), texts, shapes, font);

    while (Window.isOpen())
    {
        Window.clear(Color::White);
        Event event;
        int ID = 0;
        while (Window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::EventType::Closed:
                Window.close();
                break;
            case Event::EventType::MouseButtonPressed:
                if (Mouse::Button::Left == event.mouseButton.button)
                {
                    for_each(shapes.begin(), shapes.end(), [&Window, &graph, &font](Node& object)->void
                        {
                            if (move(object, Window))
                            {
                                create_lines(graph.get_matrix(), lines, shapes);
                                create_text(graph.get_matrix(), texts, shapes, font);
                            }
                        });

                    if (button_add.getGlobalBounds().contains(Mouse::getPosition(Window).x, Mouse::getPosition(Window).y))
                    {
                        graph.insert_vertex_full(graph.get_count_vertex() + 1);
                        create_new_node(shapes, RADIUS);
                    }
                    else if (button_delete.getGlobalBounds().contains(Mouse::getPosition(Window).x, Mouse::getPosition(Window).y))
                    {
                        int num;
                        do
                        {
                            cout << "Delete what?: ";
                            cin >> num;
                        } while (graph.get_vertex_index(num) == -1);
                        int index = graph.delete_vertex(num);
                        if (index != -1) 
                        {
                            auto it = shapes.begin();
                            for (int i = 0; i < index; ++i) ++it;
                            shapes.erase(it);
                        }
                        cout << "After delete:\n";
                        cout << graph;
                    }
                    else if (button_get_answer.getGlobalBounds().contains(Mouse::getPosition(Window).x, Mouse::getPosition(Window).y))
                    {
                        process_voyager(graph);
                        cout << endl;
                    }
                    else if (button_show_matrix.getGlobalBounds().contains(Mouse::getPosition(Window).x, Mouse::getPosition(Window).y))
                    {
                        cout << graph << "\n";
                    }
                }
            default:
                break;
            }
        }
        for_each(texts.begin(), texts.end(), [&Window](Text& text)->void
            {
                Window.draw(text);
            });
             
        for_each(lines.begin(), lines.end(), [&Window](vector<Vertex>& line)->void
            {
                draw_line(line, Window);
            });

        for_each(shapes.begin(), shapes.end(), [&Window, &ID](Node& shape)->void
            {
                draw_vertex(shape.getPosition().x, shape.getPosition().y, to_string(ID+1), Window);++ID;
            });

        //for_each(test.begin(), test.end(), [&Window](Text& object)->void
        //    {
        //        Window.draw(object);
        //    });
        for_each(buttons.begin(), buttons.end(), [&Window](RectangleShape& button)->void
            {
                Window.draw(button);
            });
        for_each(text_buttons.begin(), text_buttons.end(), [&Window](Text& text)->void 
            {
                Window.draw(text);
            });
        for_each(lines_buttons.begin(), lines_buttons.end(), [&Window](vector<Vertex>& vector)->void
            {
                draw_line(vector, Window);
            });
        Window.display();
    }


    //for_each(texts.begin(), texts.end(), [&Window](Text& obj)
    //    {
    //        cout << "x = " << obj.getPosition().x << " y = " << obj.getPosition().y << " text = " << obj.getString().toAnsiString() << "\n";
    //    });

    return 0;
}