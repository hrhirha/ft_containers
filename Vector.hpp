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

		private:
			T	*_ptr;
			Iterator(T *p) : _ptr(p) {};
	};

	template <class T>
		static Iterator<T> operator +(int n, Iterator<T> const &x) { return x + n; }

	template <class T, class Alloc = std::allocator<T> >
		class Vector
		{
			public:
				typedef T												value_type;
				typedef Alloc											allocator_type;
				typedef size_t											size_type;
				typedef typename allocator_type::reference				reference;
				typedef typename allocator_type::const_reference		const_reference;
				typedef typename allocator_type::pointer				pointer;
				typedef typename allocator_type::const_pointer			const_pointer;
				typedef typename ft::Iterator<value_type>				iterator;
				typedef typename ft::Iterator<const value_type>			const_iterator;
				typedef typename ft::Reverse_Iterator<iterator>			reverse_iterator;
				typedef typename ft::Reverse_Iterator<const_iterator>	const_reverse_iterator;

				explicit Vector(const allocator_type &alloc = allocator_type()) : _allocator(alloc)
				{
					_ptr = nullptr;
					_size = 0;
					_capacity = 0;
				}
				explicit Vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
				{
					_allocator = alloc;
					_ptr = _allocator.allocate(n);
					for (size_type i = 0; i < n; i++)
						_ptr[i] = val;
				}
				template <class InputIter>
					Vector(InputIter first, InputIter last, const allocator_type &alloc = allocator_type());
				Vector(const Vector &x)
				{
					*this = x;
				}
				Vector	&operator =(const Vector &x)
				{
					_allocator.deallocate(_ptr, _capacity);
					_allocator = x._allocator;
					_size = x._size;
					_capacity = x._capacity;
					_ptr = allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_ptr[i] = x._ptr[i];
					return *this;
				}
				
				~Vector() {};

				iterator begin() {return ft::Iterator<value_type>(_ptr); }
				const_iterator begin() const;

			private:
				allocator_type	_allocator;
				pointer			_ptr;
				size_type		_size;
				size_type		_capacity;
		};
}

#endif
