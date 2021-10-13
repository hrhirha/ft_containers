#include "RBTree.hpp"

int	main()
{
	RBTree<int> tree;

	//tree.insert(20);


	for (size_t i = 1; i <= 100; i++)
	{
		tree.insert(i);
	}
	for (size_t i = 100; i >= 1; i--)
	{
		tree.erase(i);
	}
}
