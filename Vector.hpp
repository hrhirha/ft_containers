#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include "Vector_Iterator.hpp"
# include "Iterator_Traits.hpp"
# include "Reverse_Iterator.hpp"
# include "types_traits.hpp"
# include <cmath>

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

				explicit Vector(size_type n, const value_type &val = value_type(),
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
						(void)t;
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
					_size = x._size;
					_capacity = x._capacity;
					_ptr = _allocator.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_ptr[i] = x._ptr[i];
					return *this;
				}

				~Vector() {};

				// Iterators

				iterator				begin() {return iterator(_ptr); }
				const_iterator			begin() const {return const_iterator(_ptr); };

				iterator				end() {return iterator(_ptr + _size); }
				const_iterator			end() const {return const_iterator(_ptr + _size); };

				reverse_iterator		rbegin() { return reverse_iterator(end()); };
				const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); };

				reverse_iterator		rend() { return reverse_iterator(begin()); };
				const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); };

				// Capacity

				size_type size() const { return _size; }
				size_type max_size() const
				{
					size_type ret = pow(2, 64 - sizeof(T)) * sizeof(T);
					return (ret - 1);
				}

				void resize (size_type n, value_type val = value_type())
				{
					if (n == _size) return ;
					if (n < _size)
					{
						for (size_type i = n; i < _size; i++)
							_ptr[i] = 0;
						_size = n;
					}
					else
					{
						reserve(n);
						for (size_type i = _size; i < n; i++)
							_ptr[i] = val;
						_size = n;
					}
				}

				size_type capacity() const { return _capacity; }

				bool empty() const { return !_size ? true : false; }

				void reserve (size_type n)
				{
					if (n > _capacity)
					{
						size_type new_cap = n >= _capacity*2 ? n : _capacity * 2;
						pointer tmp = _allocator.allocate(new_cap);
						for (size_type i = 0; i < _size; i++)
							tmp[i] = _ptr[i];
						_allocator.deallocate(_ptr, _capacity);
						_ptr = tmp;
						_capacity = new_cap;
					}
				}

				// Element access

				reference		operator [](size_type n) { return _ptr[n]; }
				const_reference	operator [](size_type n) const { return _ptr[n]; }

				reference		at (size_type n)
				{
					if (n >= _size) throw std::out_of_range("Vector");
					return (*this)[n];
				}
				const_reference	at (size_type n) const
				{
					if (n >= _size) throw std::out_of_range("Vector");
					return (*this)[n];
				}

				reference		front() { return *begin(); }
				const_reference	front() const { return *begin(); }

				reference		back() { return *(end() - 1); }
				const_reference	back() const { return *(end() - 1); }

				// Modifiers

				template <class InputIterator>
					void	assign (InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* t = 0)
					{
						(void)t;
						size_type n = last - first;
						if (n > _capacity)
						{
							_allocator.deallocate(_ptr, _capacity);
							_capacity = n;
							_ptr = _allocator.allocate(_capacity);
						}
						_size = n;
						for (size_type i = 0; i < _size; i++)
							_ptr[i] = *(first++);
					}

				void		assign (size_type n, const value_type& val)
				{
					if (n > _capacity)
					{
						_allocator.deallocate(_ptr, _capacity);
						_capacity = n;
						_ptr = _allocator.allocate(_capacity);
					}
					_size = n;
					for (size_type i = 0; i < _size; i++)
						_ptr[i] = val;
				}

				void push_back (const value_type& val)
				{
					if (_capacity == 0)
					{
						_ptr = _allocator.allocate(1);
						_capacity = 1;
					}
					else if (_size == _capacity)
					{
						pointer tmp = _allocator.allocate(_capacity * 2);
						for (size_type i = 0; i < _size; i++)
							tmp[i] = _ptr[i];
						_allocator.deallocate(_ptr, _capacity);
						_ptr = tmp;
						_capacity *= 2;
					}
					_ptr[_size] = val;
					_size++;
				}
				void pop_back()
				{
					_ptr[_size] = 0;
					_size--;
				}

				iterator insert (iterator position, const value_type& val)
				{
					if (_capacity > _size)
					{
						iterator it = end();
						for (; it != position; it--)
						{
							*it = *(it-1);
						}
						*it = val;
					}
					else
					{
						pointer tmp = _allocator.allocate(_capacity * 2);
						size_type i = 0;
						for (iterator it = begin(); it < position; it++)
							tmp[i++] = *it;
						tmp[i++] = val;
						for (iterator it = position+1; it < end(); it++)
							tmp[i++] = *it;
						_allocator.deallocate(_ptr, _capacity);
						_ptr = tmp;
						_capacity *= 2;
					}
					_size++;
					return (position);
				}
				void insert (iterator position, size_type n, const value_type& val)
				{
					if (_capacity >= _size + n)
					{
						iterator it = end();
						for (; it >= position; it--)
						{
							*(it+n) = *it;
						}
						for(size_type i = 0; i < n; i++)
							*(++it) = val;
					}
					else
					{
						size_type new_cap = _capacity;
						while (new_cap < _size + n) new_cap *= 2;
						pointer tmp = _allocator.allocate(new_cap);
						size_type i = 0;
						iterator it = begin();
						for (; it < position; it++) tmp[i++] = *it;
						for (size_type j = 0; j < n; j++) tmp[i++] = val;
						for (; it < end(); it++) tmp[i++] = *it;
						_allocator.deallocate(_ptr, _capacity);
						_ptr = tmp;
						_capacity = new_cap;
					}
					_size += n;
				}
				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* t = 0);

			private:
				allocator_type	_allocator;
				pointer			_ptr;
				size_type		_size;
				size_type		_capacity;
		};
}

#endif
