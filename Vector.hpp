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

			Iterator		&operator ++() { ++_ptr; return *this; };
			Iterator		&operator ++(int) { T *tmp = _ptr; ++_ptr; return (Iterator(tmp)); };

			Iterator		&operator --() { --_ptr; return *this; };
			Iterator		&operator --(int) { T *tmp = _ptr; --_ptr; return (Iterator(tmp)); };

			Iterator		&operator +(int n) { return (Iterator(_ptr + n)); };
			Iterator		&operator -(int n) { return (Iterator(_ptr - n)); };
			Iterator		&operator -(Iterator const &x) { return (Iterator(_ptr - x._ptr)); };

			bool			operator >(Iterator const &x) { return _ptr > x._ptr; } const;
			bool			operator <(Iterator const &x) { return _ptr < x._ptr; } const;
			bool			operator >=(Iterator const &x) { return _ptr >= x._ptr; }const;
			bool			operator <=(Iterator const &x) { return _ptr <= x._ptr; }const;

			void			operator +=(int n) { _ptr += n; };
			void			operator -=(int n) { _ptr -= n; };

			T				&operator [](size_t n) { return Iterator(&(_ptr[n])); };
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
			explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type());
			template <class InputIter>
			vector(InputIter first, InputIter last,
					const allocator_type &alloc = allocator_type());
			vector(const vector &x);
			~vector();

			vector	&operator =(const vector &x);
	};
}

#endif
