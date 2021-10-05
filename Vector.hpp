#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include "Vector_Iterator.hpp"
# include "Iterator_Traits.hpp"
# include "Reverse_Iterator.hpp"
# include "types_traits.hpp"

namespace ft
{
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
				typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

				explicit Vector(const allocator_type &alloc = allocator_type()) :
					_allocator(alloc), _ptr(nullptr), _size(0), _capacity(0) {}

				explicit Vector(size_type n, const size_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) :
					_allocator(alloc), _size(n), _capacity(n)
				{
					if (_capacity)
					{
						_ptr = _allocator.allocate(_capacity);
						for (size_type i = 0; i < _size; i++)
							_ptr[i] = val;
					}
					else _ptr = nullptr;
				}

				template <class InputIter>
					Vector(InputIter first, InputIter last,
					typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type* t = 0,
							const allocator_type &alloc = allocator_type())
					{
						_capacity = last - first;
						_size = _capacity;
						_ptr = _allocator.allocate(_capacity);
						for (size_type i = 0; i < _size; i++)
							_ptr[i] = *(first++);
					}

				Vector(const Vector &x) : _capacity(0), _size(0), _ptr(nullptr)
				{
					*this = x;
				}
				Vector	&operator =(const Vector &x)
				{
					if (_capacity) _allocator.deallocate(_ptr, _capacity);
					_allocator = x._allocator;
					_size = x._size;
					_capacity = x._capacity;
					_ptr = _allocator.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_ptr[i] = x._ptr[i];
					return *this;
				}

				~Vector() {};

				iterator begin() {return iterator(_ptr); }
				const_iterator begin() const {return const_iterator(_ptr); };

				iterator end() {return iterator(_ptr + _size); }
				const_iterator end() const {return const_iterator(_ptr + _size); };

				reverse_iterator rbegin() { return reverse_iterator(end()); };
				const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };

				reverse_iterator rend() { return reverse_iterator(begin()); };
				const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

			private:
				allocator_type	_allocator;
				pointer			_ptr;
				size_type		_size;
				size_type		_capacity;
		};
}

#endif
