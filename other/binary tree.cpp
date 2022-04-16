#include "tree.h"

int main()
{
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
	cout << endl << endl << endl;
	tree2->print_tree(2);

	int count;
	cout << "\n\n\n\nInput count of nodes balanced tree: "; cin >> count;
	cout << endl << endl;
	Tree<double>* tree = new Tree<double>();
	tree = tree->balanced(count);
	tree->print_tree(2);

	cout << endl << endl;
	list<double> nodes_data;
	tree->parse(tree, nodes_data);

	auto balanced_tree = new Tree<double>();
	for (auto current : nodes_data)
	{
		balanced_tree->insert(current);
	}

	cout << endl << endl;
	balanced_tree->print_tree(2);
	cout << "Finding min.. Minimum = " << balanced_tree->find_min()->get_data();
	return 0;
}
