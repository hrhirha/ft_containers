#include "RBTree.hpp"
#include "../tools/Utility.hpp"
#include <map>

int	main()
{
	RBTree<ft::pair<int,int> > tree;
	//std::map<int, int> tree;



	for (size_t i = 1; i <= 10; i++)
	{
		tree.insert(ft::make_pair(i,i));
	}
	for (size_t i = 1; i <= 10; i++)
	{
		tree.erase(ft::make_pair(i,i));
	}
	while (1) {}
}
