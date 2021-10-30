#include <iostream>
#include <string>
#include <deque>
#include <sys/time.h>

#if 0 //CREATE A REAL STL EXAMPLE
# include <map>
# include <stack>
# include <vector>
namespace ft = std;
#else
# include "../map/Map.hpp"
# include "../stack/Stack.hpp"
# include "../vector/Vector.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

#define GREEN "\e[1;32m"
#define YELLOW "\e[0;33m"
#define RESET "\e[0m"

time_t get_time(void)
{
	struct timeval time_now;

	gettimeofday(&time_now, NULL);
	time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
	return (msecs_time);
}

void vector_test()
{
	std::cout.width(40); std::cout << std::internal << GREEN << "TESTING VECTOR" << RESET << std::endl;
	std::cout << YELLOW << "Constructors" << RESET << std::endl;
	{
		ft::vector<int> first;
		time_t s1 = get_time();
		ft::vector<int> second (1e5,1337);
		time_t e1 = get_time();
		std::cout << "fill constructor time: " << e1 - s1 << "ms" << std::endl;

		time_t s2 = get_time();
		ft::vector<int> third (second.begin(),second.end());
		time_t e2 = get_time();
		std::cout << "range constructor time: " << e2 - s2 << "ms" << std::endl;

		time_t s3 = get_time();
		ft::vector<int> fourth (third);
		time_t e3 = get_time();
		std::cout << "copy constructor time: " << e3 - s3 << "ms" << std::endl;

		int myints[] = {16,2,77,29};
		ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << YELLOW << "Operator =()" << RESET << std::endl;
	{
		ft::vector<int> foo (1e6,0);
		ft::vector<int> bar (1e5,0);

		time_t s1 = get_time();
		bar = foo;
		time_t e1 = get_time();
		std::cout << "time: " << e1 - s1 << "ms" << std::endl;
		foo = ft::vector<int>();

		std::cout << "Size of foo: " << int(foo.size()) << '\n';
		std::cout << "Size of bar: " << int(bar.size()) << '\n';
	}
	std::cout << YELLOW << "begin() and end()" << RESET << std::endl;
	{
		ft::vector<int> myvector;
		for (int i=1; i<=30; i++) myvector.push_back(i);

		time_t s1 = get_time();
		ft::vector<int>::iterator it = myvector.begin();
		time_t e1 = get_time();
		std::cout << "begin() time: " << e1 - s1 << "ms" << std::endl;

		time_t s2 = get_time();
		ft::vector<int>::iterator eit = myvector.end();
		time_t e2 = get_time();
		std::cout << "end() time: " << e2 - s2 << "ms" << std::endl;

		for (; it != eit; ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	std::cout << YELLOW << "rbegin() and rend()" << RESET << std::endl;
	{
		ft::vector<int> myvector;
		for (int i=1; i<=30; i++) myvector.push_back(i);

		time_t s1 = get_time();
		ft::vector<int>::reverse_iterator it = myvector.rbegin();
		time_t e1 = get_time();
		std::cout << "rbegin() time: " << e1 - s1 << "ms" << std::endl;

		time_t s2 = get_time();
		ft::vector<int>::reverse_iterator eit = myvector.rend();
		time_t e2 = get_time();
		std::cout << "rend() time: " << e2 - s2 << "ms" << std::endl;

		for (; it != eit; ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	std::cout << YELLOW << "size() and max_size()" << RESET << std::endl;
	{
		ft::vector<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i=0; i<10; i++) myints.push_back(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.insert (myints.end(),10,100);
		std::cout << "2. size: " << myints.size() << '\n';

		myints.pop_back();
		std::cout << "3. size: " << myints.size() << '\n';

		std::cout << "vector<int> max_size: " << ft::vector<int>().max_size() << std::endl;
		std::cout << "vector<string> max_size: " << ft::vector<std::string>().max_size() << std::endl;
		std::cout << "vector<float> max_size: " << ft::vector<float>().max_size() << std::endl;
	}
	std::cout << YELLOW << "resize() and capacity()" << RESET << std::endl;
	{
		ft::vector<std::string> v(1e4, "1337");

		time_t s1 = get_time();
		v.resize(1e6, "42");
		time_t e1 = get_time();
		std::cout << "resize() time: " << e1 - s1 << "ms" << std::endl;

		ft::vector<int> myvector;

		for (int i=1;i<10;i++) myvector.push_back(i);

		myvector.resize(5);
		std::cout << "size: " << myvector.size() << ", capacity: " << myvector.capacity() << '\n';
		myvector.resize(8, 100);
		std::cout << "size: " << myvector.size() << ", capacity: " << myvector.capacity() << '\n';
		myvector.resize(33);
		std::cout << "size: " << myvector.size() << ", capacity: " << myvector.capacity() << '\n';

		std::cout << "myvector contains:";
		for (int i=0;i<myvector.size();i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}
	std::cout << YELLOW << "empty()" << RESET << std::endl;
	{
		ft::vector<int> myvector;
		int sum (0);

		for (int i=1;i<=30;i++) myvector.push_back(i);

		while (!myvector.empty())
		{
			sum += myvector.back();
			myvector.pop_back();
		}

		std::cout << "total: " << sum << '\n';
	}
	std::cout << YELLOW << "reserve()" << RESET << std::endl;
	{
		ft::vector<int> v(1e3, 1337);

		time_t s1 = get_time();
		v.reserve(1e6);
		time_t e1 = get_time();
		std::cout << "reserve() time: " << e1 - s1 << "ms" << std::endl;

		ft::vector<int>::size_type sz;

		ft::vector<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for (int i=0; i<100; ++i) {
			foo.push_back(i);
			if (sz!=foo.capacity()) {
				sz = foo.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}

		ft::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100);
		std::cout << "making bar grow:\n";
		for (int i=0; i<100; ++i) {
			bar.push_back(i);
			if (sz!=bar.capacity()) {
				sz = bar.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}
	}
	std::cout << YELLOW << "operator []()" << RESET << std::endl;
	{
		ft::vector<int> myvector (10);

		ft::vector<int>::size_type sz = myvector.size();

		// assign some values:
		for (unsigned i=0; i<sz; i++) myvector[i]=i;

		std::cout << "myvector contains:";
		for (unsigned i=0; i<sz; i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}
	std::cout << YELLOW << "at()" << RESET << std::endl;
	{
		ft::vector<std::string> v(1e6, "1337");

		time_t s1 = get_time();
		v.at(1e5);
		time_t e1 = get_time();
		std::cout << "at() time: " << e1 - s1 << "ms" << std::endl;

		ft::vector<int> myvector(10);

		// assign some values:
		for (unsigned i=0; i<myvector.size(); i++)
			myvector.at(i)=i;

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector.at(i);
		std::cout << '\n';
	}
	std::cout << YELLOW << "front() and back()" << RESET << std::endl;
	{
		ft::vector<int> myvector;

		myvector.push_back(12);
		myvector.push_back(45);
		myvector.push_back(578);
		myvector.push_back(917);

		std::cout << "myvector.front(): " << myvector.front() << '\n';
		std::cout << "myvector.back(): " << myvector.back() << '\n';
	}
	std::cout << YELLOW << "assign()" << RESET << std::endl;
	{
		ft::vector<int> v;
		ft::vector<int> v1;

		time_t s1 = get_time();
		v.assign(1e6,1337);
		time_t e1 = get_time();
		std::cout << "assign(fill) time: " << e1 - s1 << "ms" << std::endl;

		time_t s2 = get_time();
		v1.assign(v.begin(),v.end());
		time_t e2 = get_time();
		std::cout << "assign(range) time: " << e2 - s2 << "ms" << std::endl;

		ft::vector<int> first;
		ft::vector<int> second;
		ft::vector<int> third;

		first.assign (7,100);

		ft::vector<int>::iterator it;
		it=first.begin()+1;

		second.assign (it,first.end()-1);

		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);

		std::cout << "Size of first: " << int (first.size()) << '\n';
		std::cout << "Size of second: " << int (second.size()) << '\n';
		std::cout << "Size of third: " << int (third.size()) << '\n';
	}
	std::cout << YELLOW << "push_back() and pop_back()" << RESET << std::endl;
	{
		ft::vector<int> v(1e6,42);

		time_t s1 = get_time();
		v.push_back(1337);
		time_t e1 = get_time();
		std::cout << "push_back() time: " << e1 - s1 << "ms" << std::endl;
		std::cout << "back(): "<< v.back() << '\n';
		time_t s2 = get_time();
		v.pop_back();
		time_t e2 = get_time();
		std::cout << "pop_back() time: " << e2 - s2 << "ms" << std::endl;
		std::cout << "back() after pop(): "<< v.back() << '\n';
	}
	std::cout << YELLOW << "insert()" << RESET << std::endl;
	{
		{
			ft::vector<int> v(1e6,1337);
			ft::vector<int> v1;

			time_t s1 = get_time();
			v.insert(v.begin()+1e5, 42);
			time_t e1 = get_time();
			std::cout << "insert(single elem) time: " << e1 - s1 << "ms" << std::endl;
		
			v.reserve(1e8);
			time_t s2 = get_time();
			v.insert(v.begin()+10, 1e2, 42);
			time_t e2 = get_time();
			std::cout << "insert(fill) time: " << e2 - s2 << "ms" << std::endl;
			
			time_t s3 = get_time();
			v1.insert(v1.begin(), v.begin(), v.end());
			time_t e3 = get_time();
			std::cout << "insert(range) time: " << e3 - s3 << "ms" << std::endl;
		}
		
		ft::vector<int> myvector (3,100);
		ft::vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert ( it , 200 );

		myvector.insert (it,2,300);

		it = myvector.begin();

		ft::vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());

		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);

		std::cout << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
}

int main()
{
	vector_test();
}
