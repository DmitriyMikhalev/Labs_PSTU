#include <iostream>
using namespace std;

template <class T>
class Tree
{
public:
	Tree(T);
	~Tree();
	T get_data();
	Tree<T>* eject_left();
	Tree<T>* eject_right();
	void delete_left();
	void delete_right();
	void insert_left(T);
	void insert_right(T);
	void direct_way(Tree<T>*);
	void symmetric_way(Tree<T>*);
	void reverse_way(Tree<T>*);
	void print_tree(int);
	void delete_tree() { delete this; }
	Tree<T>* get_left();
	Tree<T>* get_right();
	Tree<T>* get_parent();
	Tree<T>* copy();
	
private:
	Tree<T>* left;
	Tree<T>* right;
	Tree<T>* parent;
	T data;
};

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
	Tree<T>* temp = this->eject_right;
	delete temp;
}

template<class T>
void Tree<T>::delete_left()
{
	Tree<T>* temp = this->eject_left;
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
		for (int i = 1; i < level; i++) cout << " ";
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
T Tree<T>::get_data() {	return data; }


int main()
{
	Tree<char>* tree = new Tree<char>('A');

	tree->insert_left('B');
	tree->get_left()->insert_left('D');
	tree->get_left()->get_left()->insert_left('G');
	tree->get_left()->insert_right('E');
	tree->get_left()->get_left()->insert_right('H');
	tree->insert_right('C');
	tree->get_right()->insert_right('F');
	tree->get_right()->get_right()->insert_left('I');
	tree->get_right()->get_right()->insert_right('J');

	tree->direct_way(tree);
	cout << endl;
	tree->symmetric_way(tree);
	cout << endl;
	tree->reverse_way(tree);
	cout << endl << endl;
	tree->print_tree(2);
	return 0;
}