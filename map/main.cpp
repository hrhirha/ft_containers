#include "RBTree.hpp"
#include "../tools/Utility.hpp"
#include <map>
#include <vector>
#include "../vector/Vector.hpp"

int	main()
{
	ft::Vector<int> *v = new  ft::Vector<int>(10, 10);

	delete v;

	std::cout << v->size() << "\n";
	std::cout << v->size() << "\n";
}
