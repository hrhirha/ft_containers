#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <iterator>
# include "Iterator_Traits.hpp"
# include "Reverse_Iterator.hpp"

namespace ft
{
	template <class T>
		class Iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
		T	*_ptr;

		public:
		typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type
			difference_type;
		typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type
			value_type;
		typedef typename std::iterator<std::random_access_iterator_tag, T>::pointer
			pointer;
		typedef typename std::iterator<std::random_access_iterator_tag, T>::reference
			reference;
		typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category
			iterator_category;

		Iterator();
		Iterator(T *p) : _ptr(p) {};
		Iterator(Iterator const &x) { *this = x; };
		Iterator		&operator =(Iterator const &x) { _ptr = &(*x._ptr); return *this; };

		~Iterator() {};

		T const			&operator *() const { return (*_ptr); };
		T				&operator *() { return (*_ptr); };
		T const			*operator ->() const { return &(*_ptr); };
		T				*operator ->() { return &(*_ptr); };

		Iterator		&operator ++() { ++_ptr; return *this; };
		Iterator		&operator ++(int) { Iterator tmp = *this; ++(*this); return (tmp); };

		Iterator		&operator --() { --_ptr; return *this; };
		Iterator		&operator --(int) { Iterator tmp = *this; --(*this); return (tmp); };

		T				&operator +=(int n) { _ptr += n; };
		T				&operator -=(int n) { _ptr -= n; };

		Iterator		&operator +(int n) { return (Iterator(_ptr + n)); };
		Iterator		&operator -(int n) { return (Iterator(_ptr - n)); };
		difference_type	operator -(Iterator const &x) { return (Iterator(_ptr - x._ptr)); };

		bool			operator ==(Iterator const &x) const { return _ptr == x._ptr; };
		bool			operator !=(Iterator const &x) const { return _ptr != x._ptr; };
		bool			operator >(Iterator const &x) const { return _ptr > x._ptr; };
		bool			operator <(Iterator const &x) const { return _ptr < x._ptr; };
		bool			operator >=(Iterator const &x) const { return _ptr >= x._ptr; };
		bool			operator <=(Iterator const &x) const { return _ptr <= x._ptr; };

		T				&operator [](size_t n) { return *this + n; };
	};

	template <class T>
	static Iterator<T> operator +(int n, Iterator<T> const &x) { return x + n; }
/*
	template <class T, class Alloc = std::allocator<T> >
		class vector
		{
			value_type		value;
			allocator_type	allocator;
			size_type		size;

			public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef size_t										size_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename ft::Iterator<value_type>			iterator;
			typedef typename ft::Reverse_Iterator<value_type>	reverse_iterator;

			explicit vector(const allocator_type &alloc = allocator_type());
			explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type());
			template <class InputIter>
				vector(InputIter first, InputIter last, const allocator_type &alloc = allocator_type());
			vector(const vector &x);
			~vector();

			vector	&operator =(const vector &x);
		};
		*/
}

#endif
