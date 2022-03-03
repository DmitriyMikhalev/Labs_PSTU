#include <iostream>
using namespace std;


class List
{
public:
	List()
	{
		head = nullptr;
		size = 0;
	}
	~List()
	{
		clear();
	}
	int get_size()
	{
		return size;
	}
	void push_back(int data);
	void push_front(int data);
	int& operator[](const int index);
	void pop_front();
	void clear();
	void delete_even();
	void pop_using_index(const int index);

private:
	class Node
	{
	public:
		Node* pointer_to_next_node;
		int data;
		Node(int data = 0, Node* pointer_to_next_node = nullptr)
		{
			this->data = data;
			this->pointer_to_next_node = pointer_to_next_node;
		}
	};
	int size;
	Node* head;
};

void print_list(List& list);
void fill_list(List& list)
{
	int count = 0;
	do
	{
		cout << "������� ���������� ������, ������� �� ������ ������: ";
		cin >> count;
	} while (count < 1);
	cout << endl;
	for (int i = 0; i < count; i++)
	{
		int data;
		cout << "������� �������� data: "; cin >> data;
		list.push_back(data);
	}
}
int main()
{
	setlocale(0, "");
	List list;
	fill_list(list);
	print_list(list);
	cout << endl << endl;
	cout << "�������� ������ �����.\n����� ������: ";
	list.delete_even();
	print_list(list);
	cout << endl << endl;
	return 0;
}

void print_list(List& list)
{
	int size = list.get_size();
	for (int i = 0; i < size; i++)
	{
		cout << list[i] << " ";
	}
}
void List::clear()
{
	while (size)
	{
		pop_front();
	}
}
void List::delete_even()
{
	Node* current = head;
	Node* prev = nullptr;
	int i = 0;
	while (current != nullptr)
	{
		if (i == 0 && current->data % 2 == 0) // ���� ���� ������ � ��� ���� ������
		{
			pop_front(); // ����� �������� ������� ����
			current = head; // ������ ������� ������ - ������ ���������������� ������
			prev = nullptr; // � ���������� ������� ��� � �������� nullptr
		}
		else if (current->data % 2 == 0) // ����� ���� ���� �� ������, �� ��� ��� ����� ���� ������
		{
			pop_using_index(i); // ��������� current 
			current = prev->pointer_to_next_node; // ������� ���� ��� ������, �� ������� ��������� ���������� ����� �������������� ������
		}
		else // ����� ���� ������� �� �����
		{
			prev = current; // �� ���������� - �������
			i++; // ���������� ���������� �������
			current = current->pointer_to_next_node; // � ����� ������� - ��� ����, �� ������� �������� �� ����� 
		}
	}
}
void List::pop_using_index(const int index)
{
	if (get_size() == 0) // ���� ������ ������ - ����� �� ������ 
	{
		return;
	}
	else if (get_size() == 1 || index == 0) // ���� ������ �������� �� ������ �������� ��� ���� ������� ��� �������� ������
	{
		pop_front(); // ��������� ������ ������� (������ ��������� ������)
	}
	else
	{
		Node* current = this->head; // ����� ������� - ������
		Node* previous = nullptr; // ���������� ����
		int count = 0; 
		while (current != nullptr) // �������� �� ����� ������
		{
			if (count == index) // ���� ������� ������ ����� �����������
			{
				previous->pointer_to_next_node = current->pointer_to_next_node; // �� ���������� ���� ������ ��������� �� ��� ����, ���� ��������� ������� (���������) ����
				delete current; // �������� ������� ����
				size--; // ��������� �������
				return; // �����
			}
			previous = current; // ���������� ���������� �������
			current = current->pointer_to_next_node; // ������� ���������� ���, ���� �������� ������ �������
			count++; // � ���������� ������� ����������
		}
	}
}
void List::push_front(int data)
{
	head = new Node(data);
	size++;
}
void List::push_back(int data)
{
	if (head == nullptr)
	{
		head = new Node(data);
	}
	else
	{
		Node* current = this->head;
		while (current->pointer_to_next_node != nullptr)
		{
			current = current->pointer_to_next_node;
		}
		current->pointer_to_next_node = new Node(data);
	}
	size++;
}
int& List::operator[](const int index) // ��������� ���� data ����� ������
{
	Node* current = this->head;
	int count = 0;
	while (current != nullptr)
	{
		if (count == index)
		{
			return current->data; 
		}
		count++;
		current = current->pointer_to_next_node;
	}

}
void List::pop_front()
{
	Node* temp = head;
	head = head->pointer_to_next_node;
	delete temp;
	size--;
}
