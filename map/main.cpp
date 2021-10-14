#include <iostream>
#include <map>
#include "Map.hpp"

int	main()
{
	//ft::map<int,int> m1;
	std::map<int,int> m2;

	for (int i = 1; i <= 100; i++)
	{
		//m1._tree.insert(ft::make_pair(i,i*10));
		m2.insert(std::make_pair(i,i*10));
	}

	//ft::map<int, int>::iterator it1 = m1.begin();
	//ft::map<int, int>::iterator ite1 = m1.end();
	std::map<int, int>::iterator it2 = m2.begin();
	std::map<int, int>::iterator ite2 = m2.end();

	//std::cout << "ft\n";
	//for (; it1 != ite1; it1++)
	//	std::cout << (*it1).first <<" "<< (*it1).second << "\n";
	//std::cout << "std\n";
	for (; it2 != ite2; it2++)
		std::cout << (*it2).first <<" "<< (*it2).second << "\n";
}
