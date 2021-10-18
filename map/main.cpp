#include <iostream>
#include <map>
#include <vector>
#include <random>
#include "Map.hpp"

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

int	main()
{
	   std::map<int,std::string> m1;
	   ft::map<int,std::string> m2;	

	   int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150};
	   for (int i = 0; i < 9; i++)
	   {
		   m1.insert(std::make_pair(arr[i], "string1"));
		   m2.insert(ft::make_pair(arr[i], "string1"));
	   }

	  // for (std::map<int,std::string>::iterator i=m1.begin(); i!=m1.end(); i++)
		//   std::cout << i->first << "\n";

	   ft::map<int,std::string>::iterator i = m2.begin();
	   ft::map<int,std::string>::const_iterator ci(i);

	   ci->second = "aaaaaaa";

	   for (; i != m2.end(); i++)
		   std::cout << i->first << " " << i->second << std::endl;

	   //std::cout << m1.upper_bound(1e5)->first << "\n";
	   //std::cout << m2.upper_bound(1e5)->first << "\n";
		
	//ft::map<int,int>::reverse_iterator rit;
	//rit = m1.rbegin();
	//std::cout << rit->first << "\n";

	//if (&(*m1.rbegin()) == &(*m1.end())) std::cout << "====\n";

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

