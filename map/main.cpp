#include <iostream>
#include <map>
#include <vector>
#include "Map.hpp"

int	main()
{
	/*
	std::map<int,int> m;

	m.insert(std::make_pair(10, 1111));
	std::map<int,int>::iterator it = m.insert(std::make_pair(20, 2222)).first;

	std::cout << "it: " << (++it)->first << "\n";
	*/


	ft::map<int,int> m1;
	ft::map<int,int> m2;	
	std::vector<ft::pair<int,int> > vp;

	ft::map<int,int>::iterator it;

	srand(time(NULL));
	for (int i = 0; i < 9; i++)
		vp.push_back(ft::make_pair(i, rand()%103));

	m1.insert(vp.begin()+1, vp.end()-1);

	for (int i = 1; i <= 10; i++)
		m2.insert(ft::make_pair(i, i*10));

	ft::map<int,int>::reverse_iterator rit;
	rit = m1.rbegin();
	std::cout << rit->first << "\n";

	if (&(*m1.rbegin()) == &(*m1.end())) std::cout << "====\n";

/*
	ft::map<int,int> m3;
	//m3.insert(ft::make_pair(1, 22));
	//m3.clear();
	
	m3 = m1;

	ft::swap(m2, m3);
	ft::swap(m3, m1);

	if (m1 == m3) std::cout << "m1 == m2\n";
	if (m1 != m3) std::cout << "m1 != m2\n";
	if (m1 < m3) std::cout << "m1 < m2\n";
	if (m1 <= m3) std::cout << "m1 <= m2\n";
	if (m1 > m3) std::cout << "m1 > m2\n";
	if (m1 >= m3) std::cout << "m1 >= m2\n";

	//std::map<int,int>::key_compare comp = m2.key_comp();

	//m2.erase(m2.begin(), m2.end());
	//m2.erase(4);
	for (ft::map<int,int>::iterator it = m3.begin(); it != m3.end(); ++it)
		std::cout << (*it).first << " " << (*it).second << std::endl;
	std::cout << std::endl;
*/
/*
	ft::map<int,int>::iterator it = m2.lower_bound(10);
	ft::map<int,int>::iterator it2 = m2.upper_bound(9);
	std::cout << "lower_bound: " << it->first << "\n";
	std::cout << "upper_bound: " << it2->first << "\n";

	ft::pair<ft::map<int,int>::iterator, ft::map<int,int>::iterator> range = m2.equal_range(11);
	for (; range.first != range.second; range.first++)
		std::cout << "range: " << range.first->first << "\n";
*/
	/*
	m1.swap(m2);

	for (std::map<int,int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << (*it).first << " " << (*it).second << std::endl;
	std::cout << "\n";
	for (std::map<int,int>::iterator it = m2.begin(); it != m2.end(); ++it)
		std::cout << (*it).first << " " << (*it).second << std::endl;
	
	std::cout << "\n";
	std::map<int,int>::iterator it = m1.begin();
	std::map<int,int>::iterator eit = m1.end();
//	m1.erase(it, eit);
	m1.clear();
	for (std::map<int,int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << (*it).first << " " << (*it).second << std::endl;
	std::cout << "\n";
	for (std::map<int,int>::iterator it = m2.begin(); it != m2.end(); ++it)
		std::cout << (*it).first << " " << (*it).second << std::endl;
	*/
}

