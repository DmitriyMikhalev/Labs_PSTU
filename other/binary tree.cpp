#include "tree.h"

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
