#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

class Object;
class BOOK;
class PRINT;
class Vector;
class Dialog;
struct TEvent;
enum COMMAND;
class Error;
class IndexError;
class SizeError;
class MaxSizeError;
class EmptySizeError;

class Error
{
public:
    virtual void what() {};
};

class IndexError : public Error
{
public:
    IndexError() { message = "\nIndex error!\n"; }
    virtual void what() { cout << message; }
protected:
    string message;
};

class SizeError : public Error
{
protected:
    string msg;
public:
    SizeError() { msg = "\nSize error!\n"; }
    virtual void what() { cout << msg; }
};

class MaxSizeError : public SizeError
{
protected:
    string message;
public:
    MaxSizeError() { message = "\nYou asked to check index greater than container size!\n"; }
    virtual void what() { cout << msg << message; }
};

class EmptySizeError : public SizeError
{
protected:
    string message;
public:
    EmptySizeError() { message = "\nYou asked to delete object from container has empty size!\n"; }
    virtual void what() { cout << msg << message; }
};



class Object
{
public:
    virtual void show() = 0;
    virtual void input() = 0;
    virtual string get_name() = 0;
};

class PRINT : public Object
{
public:
    PRINT() { publisher_name = author_name = "NULL"; };
    void show() override;
    void input() override;
    void set_publisher_name(string);
    void set_author_name(string);
    PRINT(string publisher_name, string author_name)
    {
        this->publisher_name = publisher_name;
        this->author_name = author_name;
    }
    string get_name() { return author_name; }
    string get_publisher_name() { return publisher_name; }
protected:
    string author_name;
    string publisher_name;
};

void PRINT::show()
{
    cout << "Author: " << author_name << "\nPublisher name: " << publisher_name;
}
void PRINT::input()
{
    while (cin.get() != '\n');
    cout << "Enter author: "; getline(cin, author_name);
    cout << "Enter publisher name: "; getline(cin, publisher_name);
}
void PRINT::set_publisher_name(string data)
{
    this->publisher_name = data;
}
void PRINT::set_author_name(string data)
{
    this->author_name = data;
}

class BOOK : public PRINT
{
public:
    void show() override;
    void input() override;
    int get_pages_count() { return pages_count; }
    string get_name() { return author_name; }
    string get_publisher_name() { return publisher_name; }
    void set_pages_count(int data) { pages_count = data; }
protected:
    int pages_count;
};

void BOOK::show()
{
    cout << "Publisher name: " << publisher_name << "\nAuthor name: " << author_name << "\nPages count: " << pages_count;
}
void BOOK::input()
{
    while (cin.get() != '\n');
    cout << "Enter author: "; getline(cin, author_name);
    cout << "Enter publisher name: "; getline(cin, publisher_name);
    cout << "Enter pages count: "; cin >> pages_count;
}

class Vector
{
public:
    Vector() { count_of_objects = capacity = 0; beg = nullptr; }
    void add_object();
    void delete_object();
    void get_name();
    void show();
    int operator()() { return count_of_objects; }
protected:
    Object** beg;
    int capacity;
    int count_of_objects;
};

void Vector::add_object()
{
    if (count_of_objects == capacity) throw MaxSizeError();
    int type;
    do
    {
        cout << "\n1.Print\n2.Book\nChoose type of object: "; cin >> type;
    } while (type > 2 || type < 1);
    if (type == 1)
    {
        PRINT* object = new PRINT;
        object->input();
        if (count_of_objects < capacity)
        {
            beg[count_of_objects] = object;
            count_of_objects++;
        }
    }
    else
    {
        BOOK* object = new BOOK;
        object->input();
        if (count_of_objects < capacity)
        {
            beg[count_of_objects] = object;
            count_of_objects++;
        }
    }
}
void Vector::delete_object()
{
    if (count_of_objects == 0) throw EmptySizeError();
    vector<Object*> vect;
    for (int i = 0; i < count_of_objects; i++)
    {
        vect.push_back(beg[i]);
    }
    int number = 0;
    cout << endl;
    for (auto obj : vect)
    {
        cout << number + 1 << ") " << obj->get_name() << "\n";
        number++;
    }
    cout << "\nChoose the number of object to delete: ";
    int number_to_delete;
    cin >> number_to_delete;
    if (number_to_delete - 1 < 0 || number_to_delete > count_of_objects) throw IndexError();
    for (int i = number_to_delete - 1; i < count_of_objects; i++)
    {
        beg[i] = beg[i + 1];
    }
    count_of_objects--;
}
void Vector::get_name()
{
    Object** current = beg;
    cout << endl;
    if (count_of_objects <= 0) throw IndexError();
    for (int i = 0; i < count_of_objects; i++)
    {
        (*current)->show();
        if (count_of_objects == (i + 1))
        {
            cout << "\n";
        }
        else
        {
            cout << "\n\n";
        }
        current++;
    }
}
void Vector::show()
{
    if (count_of_objects == 0) throw IndexError();
    if (count_of_objects != 0)
    {
        Object** current = beg;
        cout << endl;
        for (int i = 0; i < count_of_objects; i++)
        {
            (*current)->show();
            if (count_of_objects == (i + 1))
            {
                cout << "\n";
            }
            else
            {
                cout << "\n\n";
            }
            current++;
        }
    }
    else
    {
        cout << "Capacity of the group is zero (or objects hasn't been added). Required option denied.\n";
    }
}

enum COMMAND
{
    EVENT_NOTHING,
    EVENT_MESSAGE,
    COMMAND_ADD,        // +
    COMMAND_DELETE,     // -
    COMMAND_GET,        // z
    COMMAND_SHOW,       // s
    COMMAND_MAKE,       // m
    COMMAND_QUIT        // q
};

struct TEvent
{
    int what;
    int command;
};

class Dialog : public Vector
{
    int end_state;
public:
    void get_event(TEvent&);
    void handle_event(TEvent&);
    void clear_event(TEvent&);
    bool valid();
    void execute();
    void end_execute();
};

void Dialog::handle_event(TEvent& event)
{
    if (event.what == COMMAND::EVENT_MESSAGE)
    {
        switch (event.command)
        {

        case COMMAND::COMMAND_ADD:
            try
            {
            add_object();
            clear_event(event);
            }
            catch (Error& error) { error.what(); }
            break;
        case COMMAND::COMMAND_DELETE:
            try 
            {
            delete_object();
            clear_event(event);
            }
            catch (Error& error) { error.what(); }
            break;
        case COMMAND::COMMAND_GET:
            try
            {
            get_name();
            clear_event(event);
            }
            catch (Error& error) { error.what(); }
            break;
        case COMMAND::COMMAND_SHOW:
            try
            {
            show();
            clear_event(event);
            }
            catch (Error& error) { error.what(); }
            break;
        case COMMAND::COMMAND_MAKE:
            cout << "\nEnter size: "; 
            cin >> capacity;
            if (capacity <= 0)
            {
                do
                {
                    cout << "Wrong capacity! Try again: ";
                    cin >> capacity;
                } while (capacity <= 0);
            }
            beg = new Object * [capacity];
            cout << "Group for " << capacity << " objects has just created. Now you can add objects -> select the desired option.\n";
            count_of_objects = 0;
            clear_event(event);
            break;
        case COMMAND::COMMAND_QUIT:
            end_execute();
            clear_event(event);
            break;
        }
    }
}
void Dialog::get_event(TEvent& event)
{
    const string options = "m+-szq";
    string input;
    cout << "\n>";
    cin >> input;
    char decision = input[0];
    if (options.find(decision) >= 0)
    {
        event.what = COMMAND::EVENT_MESSAGE;
        switch (decision)
        {
        case 'm':
            event.command = COMMAND::COMMAND_MAKE;
            break;
        case '+':
            event.command = COMMAND::COMMAND_ADD;
            break;
        case '-':
            event.command = COMMAND::COMMAND_DELETE;
            break;
        case 's':
            event.command = COMMAND::COMMAND_SHOW;
            break;
        case 'z':
            event.command = COMMAND::COMMAND_GET;
            break;
        case 'q':
            event.command = COMMAND::COMMAND_QUIT;
            break;
        }
    }
    else
    {
        event.what = COMMAND::EVENT_NOTHING;
    }
}
void Dialog::execute()
{
    TEvent event;
    do
    {
        end_state = 0;
        get_event(event);
        handle_event(event);
    } while (valid());
}
void Dialog::clear_event(TEvent& event)
{
    event.what = COMMAND::EVENT_NOTHING;
}
void Dialog::end_execute()
{
    end_state = 1;
}
bool Dialog::valid()
{
    return end_state == 0;
}

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);
    system("cls");
    cout << "________MENU________\nm: create group     |\n+: add information  |\n-: delete object    |\ns: show objects     |\nz: objects' names   |\nq: quit             |\n____________________|";
    Dialog dialog;
    dialog.execute();
    SetConsoleCP(866);
    return 0;
}