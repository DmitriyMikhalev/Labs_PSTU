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
		return size;#include <iostream>
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
		cout << "Введите количество данных, которое вы хотите ввести: ";
		cin >> count;
	} while (count < 1);
	cout << endl;
	for (int i = 0; i < count; i++)
	{
		int data;
		cout << "Введите значение data: "; cin >> data;
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
	cout << "Удаление четных полей.\nНовый список: ";
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
		if (i == 0 && current->data % 2 == 0) // если узел первый и его надо убрать
		{
			pop_front(); // тогда удаление первого узла
			current = head; // теперь текущий объект - голова редактированного списка
			prev = nullptr; // а предыдущий элемент так и остается nullptr
		}
		else if (current->data % 2 == 0) // иначе если узел не первый, но его все равно надо убрать
		{
			pop_using_index(i); // удаляется current 
			current = prev->pointer_to_next_node; // текущим стал тот объект, на который указывает предыдущий после редактирования списка
		}
		else // иначе если удалять не нужно
		{
			prev = current; // то предыдущий - текущий
			i++; // увеличение локального индекса
			current = current->pointer_to_next_node; // и новый текущий - тот узел, на который указывал до этого 
		}
	}
}
void List::pop_using_index(const int index)
{
	if (get_size() == 0) // если пустой список - выход из фунции 
	{
		return;
	}
	else if (get_size() == 1 || index == 0) // если список непустой из одного элемента или если элемент для удаления первый
	{
		pop_front(); // удаляется первый элемент (внутри изменится размер)
	}
	else
	{
		Node* current = this->head; // иначе текущий - голова
		Node* previous = nullptr; // предыдущий нуль
		int count = 0; 
		while (current != nullptr) // итерации до конца списка
		{
			if (count == index) // если текущий индекс равен переданному
			{
				previous->pointer_to_next_node = current->pointer_to_next_node; // то предыдущий узел должен указывать на тот узел, куда указывает текущий (удаляемый) узел
				delete current; // удаление нужного узла
				size--; // изменение размера
				return; // выход
			}
			previous = current; // предыдущим становится текущий
			current = current->pointer_to_next_node; // текущим становится тот, куда указывал старый текущий
			count++; // и увеличение индекса локального
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
int& List::operator[](const int index) // получение поля data через индекс
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
		cout << "Ââåäèòå êîëè÷åñòâî äàííûõ, êîòîðîå âû õîòèòå ââåñòè: ";
		cin >> count;
	} while (count < 1);
	cout << endl;
	for (int i = 0; i < count; i++)
	{
		int data;
		cout << "Ââåäèòå çíà÷åíèå data: "; cin >> data;
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
	cout << "Óäàëåíèå ÷åòíûõ ïîëåé.\nÍîâûé ñïèñîê: ";
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
		if (i == 0 && current->data % 2 == 0) // åñëè óçåë ïåðâûé è åãî íàäî óáðàòü
		{
			pop_front(); // òîãäà óäàëåíèå ïåðâîãî óçëà
			current = head; // òåïåðü òåêóùèé îáúåêò - ãîëîâà ðåäàêòèðîâàííîãî ñïèñêà
			prev = nullptr; // à ïðåäûäóùèé ýëåìåíò òàê è îñòàåòñÿ nullptr
		}
		else if (current->data % 2 == 0) // èíà÷å åñëè óçåë íå ïåðâûé, íî åãî âñå ðàâíî íàäî óáðàòü
		{
			pop_using_index(i); // óäàëÿåòñÿ current 
			current = prev->pointer_to_next_node; // òåêóùèì ñòàë òîò îáúåêò, íà êîòîðûé óêàçûâàåò ïðåäûäóùèé ïîñëå ðåäàêòèðîâàíèÿ ñïèñêà
		}
		else // èíà÷å åñëè óäàëÿòü íå íóæíî
		{
			prev = current; // òî ïðåäûäóùèé - òåêóùèé
			i++; // óâåëè÷åíèå ëîêàëüíîãî èíäåêñà
			current = current->pointer_to_next_node; // è íîâûé òåêóùèé - òîò óçåë, íà êîòîðûé óêàçûâàë äî ýòîãî 
		}
	}
}
void List::pop_using_index(const int index)
{
	if (get_size() == 0) // åñëè ïóñòîé ñïèñîê - âûõîä èç ôóíöèè 
	{
		return;
	}
	else if (get_size() == 1 || index == 0) // åñëè ñïèñîê íåïóñòîé èç îäíîãî ýëåìåíòà èëè åñëè ýëåìåíò äëÿ óäàëåíèÿ ïåðâûé
	{
		pop_front(); // óäàëÿåòñÿ ïåðâûé ýëåìåíò (âíóòðè èçìåíèòñÿ ðàçìåð)
	}
	else
	{
		Node* current = this->head; // èíà÷å òåêóùèé - ãîëîâà
		Node* previous = nullptr; // ïðåäûäóùèé íóëü
		int count = 0; 
		while (current != nullptr) // èòåðàöèè äî êîíöà ñïèñêà
		{
			if (count == index) // åñëè òåêóùèé èíäåêñ ðàâåí ïåðåäàííîìó
			{
				previous->pointer_to_next_node = current->pointer_to_next_node; // òî ïðåäûäóùèé óçåë äîëæåí óêàçûâàòü íà òîò óçåë, êóäà óêàçûâàåò òåêóùèé (óäàëÿåìûé) óçåë
				delete current; // óäàëåíèå íóæíîãî óçëà
				size--; // èçìåíåíèå ðàçìåðà
				return; // âûõîä
			}
			previous = current; // ïðåäûäóùèì ñòàíîâèòñÿ òåêóùèé
			current = current->pointer_to_next_node; // òåêóùèì ñòàíîâèòñÿ òîò, êóäà óêàçûâàë ñòàðûé òåêóùèé
			count++; // è óâåëè÷åíèå èíäåêñà ëîêàëüíîãî
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
int& List::operator[](const int index) // ïîëó÷åíèå ïîëÿ data ÷åðåç èíäåêñ
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
