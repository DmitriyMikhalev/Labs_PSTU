#pragma once
#include <iostream>
#include <list>
using namespace std;

template <class T>
class Tree
{
public:
	Tree(T);
	Tree() { left = right = parent = nullptr; data = 0; }
	~Tree();
	T get_data();
	void delete_left();
	void delete_right();
	void insert_left(T);
	void insert_right(T);
	void direct_way(Tree<T>*);
	void symmetric_way(Tree<T>*);
	void reverse_way(Tree<T>*);
	void parse(Tree<T>*, list<double>&);
	void print_tree(int);
	void delete_tree() { delete this; }
	void insert(T);
	void erase(T);
	void add_left(Tree<T>* temp) { left = temp; }
	void add_right(Tree<T>* temp) { right = temp; }
	Tree<T>* eject_left();
	Tree<T>* eject_right();
	Tree<T>* get_left();
	Tree<T>* get_right();
	Tree<T>* get_parent();
	Tree<T>* copy();
	Tree<T>* find(T);
	Tree<T>* next();
	Tree<T>* prev();
	Tree<T>* find_min();
	Tree<T>* find_max();
	Tree<T>* balanced(int);

private:
	Tree<T>* left;
	Tree<T>* right;
	Tree<T>* parent;
	T data;
};


template<class T>
void Tree<T>::erase(T data)
{
	Tree<T>* to_erase = this->find(data);
	Tree<T>* te_parent = to_erase->parent; // te_parent = to_erase_parent
	if (to_erase->left == nullptr && to_erase->right == nullptr) // если у удаляемого узла НЕТ потомков
	{
		if (te_parent->left == to_erase)
		{
			te_parent->left = nullptr;
			delete to_erase;
		}
		else
		{
			te_parent->right = nullptr;
			delete to_erase;
		}
	}
	else if ((to_erase->left != nullptr && to_erase->right == nullptr) || (to_erase->right != nullptr && to_erase->left == nullptr)) // если есть ОДИН потомок
	{
		if (to_erase->left == nullptr)
		{
			if (to_erase == te_parent->left)
			{
				te_parent->left = to_erase->right;
			}
			else
			{
				te_parent->right = to_erase->right;
			}
			to_erase->right->parent = te_parent;
		}
		else
		{
			if (te_parent->left == to_erase)
			{
				te_parent->left = to_erase->left;
			}
			else
			{
				te_parent->right = to_erase->left;
			}
			to_erase->left->parent = te_parent;
		}
	}
	else // если ДВА потомка
	{
		Tree<T>* next = to_erase->next();
		to_erase->data = next->data;
		if (next == next->parent->left)
		{
			next->parent->left = next->right;
			if (next->right != nullptr)
			{
				next->right->parent = next->parent;
			}

		}
		else
		{
			next->parent->right = next->right;
			if (next->right != nullptr)
			{
				next->right->parent = next->parent;
			}
		}
		delete next;
	}
}

template<class T>
void Tree<T>::insert(T data)
{
	Tree<T>* current = this;
	while (current != nullptr)
	{
		if (data > current->data)
		{
			if (current->right != nullptr)
			{
				current = current->right;
			}
			else
			{
				current->insert_right(data);
				return;
			}
		}
		else if (data < current->data)
		{
			if (current->left != nullptr)
			{
				current = current->left;
			}
			else
			{
				current->insert_left(data);
				return;
			}
		}
		else return;
	}
}

template<class T>
Tree<T>* Tree<T>::prev()
{
	Tree<T>* current = this;
	if (current->left != nullptr)
	{
		return current->left->find_max();
	}
	Tree<T>* temp = current->parent;
	while (temp != nullptr && current == temp->left) // пока текущий узел левый потомок, идем на уровень вверх.
	{
		current = temp;
		temp = temp->parent;
	}
	return temp;

}

template<class T>
Tree<T>* Tree<T>::find(T data)
{
	if (this == nullptr || this->data == data)
	{
		return this;
	}
	else if (data > this->data)
	{
		return this->right->find(data);
	}
	else
	{
		return this->left->find(data);
	}
}

template<class T>
Tree<T>* Tree<T>::find_max()
{
	if (this->right == nullptr)
	{
		return this;
	}
	return this->right->find_max();
}

template<class T>
Tree<T>* Tree<T>::find_min()
{
	if (this->left == nullptr)
	{
		return this;
	}
	return this->left->find_min();
}

template<class T>
Tree<T>* Tree<T>::next()
{
	Tree<T>* current = this;
	if (current->right != nullptr)
	{
		return current->right->find_min();
	}
	Tree<T>* temp = current->parent; // родитель рассматриваемого
	while (temp != nullptr && current == temp->right) // пока узел - правый потомок, переходим на уровень вверх. Узлом становится родитель предыдущего

	{
		current = temp;
		temp = temp->parent;
	}
	return temp;
}

template<class T>
Tree<T>* Tree<T>::copy()
{
	Tree<T>* temp = new Tree(this->data);
	if (this->parent != nullptr)
	{
		temp->parent = this->parent;
	}
	if (this->left != nullptr)
	{
		temp->left = this->left->copy();
	}
	if (this->right != nullptr)
	{
		temp->right = this->right->copy();
	}
	return temp;
}

template<class T>
void Tree<T>::delete_right()
{
	Tree<T>* temp = this->eject_right();
	delete temp;
}

template<class T>
void Tree<T>::delete_left()
{
	Tree<T>* temp = this->eject_left();
	delete temp;
}

template<class T>
Tree<T>* Tree<T>::eject_right()
{
	if (this == nullptr) return nullptr;
	else
	{
		Tree<T>* temp = this->right;
		this->right = nullptr;
		return temp;
	}
}

template<class T>
Tree<T>* Tree<T>::eject_left()
{
	if (this == nullptr) return nullptr;
	else
	{
		Tree<T>* temp = this->left;
		this->left = nullptr;
		return temp;
	}
}

template<class T>
void Tree<T>::print_tree(int level)
{
	if (this != nullptr)
	{
		this->left->print_tree(level + 1);
		for (int i = 1; i < level; i++) cout << "  ";
		cout << this->get_data() << endl;
		this->right->print_tree(level + 1);
	}
}

template<class T>
void Tree<T>::reverse_way(Tree<T>* current) // прямой обход: корень -> левый потомок -> правый потомок
{
	if (current == nullptr)
	{
		return;
	}
	else
	{
		reverse_way(current->get_left());
		reverse_way(current->get_right());
		cout << current->get_data() << " ";
	}
}

template<class T>
void Tree<T>::symmetric_way(Tree<T>* current) // прямой обход: корень -> левый потомок -> правый потомок
{
	if (current == nullptr)
	{
		return;
	}
	else
	{
		symmetric_way(current->get_left());
		cout << current->get_data() << " ";
		symmetric_way(current->get_right());
	}
}

template<class T>
Tree<T>* Tree<T>::get_left() { return left; }

template<class T>
Tree<T>* Tree<T>::get_right() { return right; }

template<class T>
Tree<T>* Tree<T>::get_parent() { return parent; }

template<class T>
Tree<T>::Tree(T data)
{
	this->data = data;
	left = right = parent = nullptr;
}

template<class T>
Tree<T>::~Tree()
{
	delete this->left;
	delete this->right;
}

template<class T>
void Tree<T>::insert_left(T data)
{
	Tree<T>* new_node = new Tree(data);
	if (this->left != nullptr)
	{
		this->left->parent = new_node;
		new_node->left = this->left;
	}
	this->left = new_node;
	new_node->parent = this;
}

template<class T>
void Tree<T>::insert_right(T data)
{
	Tree<T>* new_node = new Tree(data);
	if (this->right != nullptr)
	{
		this->right->parent = new_node;
		new_node->right = this->right;
	}
	this->right = new_node;
	new_node->parent = this;
}

template<class T>
T Tree<T>::get_data() { return data; }

template<class T>
Tree<T>* Tree<T>::balanced(int count)
{
	if (count <= 0)
	{
		return nullptr;
	}
	T data;
	cout << "Input data to balanced tree: "; cin >> data;
	Tree<T>* temp = new Tree<T>(data);
	temp->add_left(balanced(count / 2));
	temp->add_right(balanced(count - count / 2 - 1));
	return temp;
}

template<class T>
void Tree<T>::parse(Tree<T>* current, list<double>& list)
{
	if (current == nullptr)
	{
		return;
	}
	else
	{
		list.push_back(current->get_data());
		parse(current->get_left(), list);
		parse(current->get_right(), list);
	}
}

template<class T>
void Tree<T>::direct_way(Tree<T>* current) // прямой обход: корень -> левый потомок -> правый потомок
{
	if (current == nullptr)
	{
		return;
	}
	else
	{
		cout << current->get_data() << " ";
		direct_way(current->get_left());
		direct_way(current->get_right());
	}
}


int main()
{
	setlocale(0, "");
	Tree<int>* tree2 = new Tree<int>(10);

	tree2->insert(4);
	tree2->insert(2);
	tree2->insert(1);
	tree2->insert(5);
	tree2->insert(3);
	tree2->insert(16);
	tree2->insert(18);
	tree2->insert(17);
	tree2->insert(19);
	tree2->erase(16);

	cout << "Прямый обход: ";
	tree2->direct_way(tree2);
	cout << endl;

	cout << "Симметричный обход: ";
	tree2->symmetric_way(tree2);
	cout << endl;

	cout << "Обратный обход: ";
	tree2->reverse_way(tree2);
	cout << endl << endl;

	tree2->print_tree(2);

	int count;
	cout << "\n\nInput count of nodes balanced tree: "; cin >> count;
	cout << endl;
	Tree<double>* tree = new Tree<double>();
	tree = tree->balanced(count);
	
	cout << "\nbalanced tree: \n\n";
	tree->print_tree(2);
	cout << endl;


	list<double> nodes_data;
	tree->parse(tree, nodes_data);
	cout << "list of nodes: ";
	for (auto current : nodes_data)
	{
		cout << current << " ";
	}

	cout << "\n\nBinary Search Tree: \n";
	auto balanced_search_tree = new Tree<double>();
	for (auto current : nodes_data)
	{
		balanced_search_tree->insert(current);
	}

	cout << endl;
	balanced_search_tree->print_tree(2);
	cout << "\n\nFinding min.. Minimum = " << balanced_search_tree->find_min()->get_data() << endl << endl;
	return 0;
}
