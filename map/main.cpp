#include "RBTree.hpp"

int	main()
{
	RBTree<int> tree;

	//tree.insert(20);


	for (size_t i = 1; i <= 10; i++)
	{
		tree.insert(i);
	}

}
