#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <iterator>

namespace ft
{
	template <class Iterator>
	class Iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::refernce				reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class Iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
		T	*_ptr;
		Iterator(T *p) : _ptr(p) {};
		
		public:
			Iterator();
			Iterator(Iterator const &x) { *this = x; };
			Iterator	&operator =(Iterator const &x) { _ptr = &(*x); return *this; };
			~Iterator();

			bool			operator ==(Iterator const &x) const { return _ptr == x._ptr };
			bool			operator !=(Iterator const &x) const { return _ptr != x._ptr };

			T const			&operator *() const { return (*_ptr) };
			T				&operator *() { return (*_ptr); };
			T const			*operator ->() const { return &(*_ptr) };
			T				*operator ->() { return &(*_ptr); };

			Iterator		&operator ++() { ++_ptr; return *this; };
			Iterator		&operator ++(int) { T tmp = *this; ++(*this); return (tmp); };

			Iterator		&operator --() { --_ptr; return *this; };
			Iterator		&operator --(int) { T tmp = *this; --(*this); return (tmp); };

			Iterator		&operator +(int n) { return (Iterator(_ptr + n)); };
			Iterator		&operator -(int n) { return (Iterator(_ptr - n)); };
			Iterator		&operator -(Iterator const &x) { return (Iterator(_ptr - x._ptr)); };

			bool			operator >(Iterator const &x) const { return _ptr > x._ptr; };
			bool			operator <(Iterator const &x) const { return _ptr < x._ptr; };
			bool			operator >=(Iterator const &x) const { return _ptr >= x._ptr; };
			bool			operator <=(Iterator const &x) const { return _ptr <= x._ptr; };

			T				&operator +=(int n) { _ptr += n; };
			T				&operator -=(int n) { _ptr -= n; };

			T				&operator [](size_t n) { return Iterator(&(_ptr[n])); };
	};

	template <class Iterator>
	class Reverse_Iterator
	{
		iterator_type	_base_iterator;

		 public:
			typedef Iterator												iterator_type;
			typedef typename Iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename Iterator_traits<Iterator>::value_type			value_type;
			typedef typename Iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename Iterator_traits<Iterator>::pointer				pointer;
			typedef typename Iterator_traits<Iterator>::reference			reference;

			Reverse_Iterator() {};
			explicit Reverse_Iterator(iterator_type it) : _base_iterator(it) {};
			template <class Iter>
				Reverse_Iterator(const Reverse_Iterator<Iter> &rev_it) { _base = rev_it._base; };

			~Reverse_Iterator() {};

			iterator_type	base() const { return (_base); };

			reference operator*() const { return *_base_iterator; };
			pointer operator->() const { return &(*_base_iterator) };

			reverse_iterator& operator ++() { --_base_iterator; return *this; };
			reverse_iterator& operator ++(int) { Reverse_Iterator tmp = *this; ++(*this); return (tmp); };
			
			reverse_iterator& operator --() { ++_base_iterator; return *this; };
			reverse_iterator& operator --(int) { Reverse_Iterator tmp = *this; --(*this); return (tmp); };

			reverse_iterator& operator +=(difference_type n) { _base_iterator -= n; return (*this); };
			reverse_iterator& operator -=(difference_type n) { _base_iterator += n; return (*this); };

			reverse_iterator operator +(difference_type n) const { Reverse_Iterator(_base_iterator - n); };
			reverse_iterator operator -(difference_type n) const { Reverse_Iterator(_base_iterator + n); };
	};

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

			explicit vector(const allocator_type &alloc = allocator_type());
			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
			template <class InputIter>
				vector(InputIter first, InputIter last, const allocator_type &alloc = allocator_type());
			vector(const vector &x);
			~vector();

			vector	&operator =(const vector &x);
	};
}

#endif
