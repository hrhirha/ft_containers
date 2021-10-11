#ifndef Vector_HPP
# define Vector_HPP
# include <iostream>
# include "Vector_Iterator.hpp"
# include "../tools/Iterator_Traits.hpp"
# include "../tools/Reverse_Iterator.hpp"
# include "../tools/types_traits.hpp"
# include "../tools/Algorithm.hpp"

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

				// Constructors

				explicit Vector(const allocator_type &alloc = allocator_type()) :
					_allocator(alloc), _ptr(nullptr), _size(0), _capacity(0) {}

				explicit Vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) :
					_allocator(alloc), _size(n), _capacity(n)
				{
					if (_capacity)
					{
						_ptr = _allocator.allocate(_capacity);
						if (!_ptr) throw std::bad_alloc();
						for (size_type i = 0; i < _size; i++)
							_ptr[i] = val;
					}
					else _ptr = nullptr;
				}

				template <class InputIter>
					Vector(InputIter first, InputIter last,
					typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type* t = 0,
							const allocator_type &alloc = allocator_type()): _allocator(alloc)
					{
						(void)t;
						_capacity = last - first;
						_size = _capacity;
						_ptr = _allocator.allocate(_capacity);
						if (!_ptr) throw std::bad_alloc();
						for (size_type i = 0; i < _size; i++)
							_ptr[i] = *(first++);
					}

				Vector(const Vector &x) : _ptr(nullptr), _size(0), _capacity(0)
				{
					*this = x;
				}
				Vector	&operator =(const Vector &x)
				{
					if (_capacity) _allocator.deallocate(_ptr, _capacity);
					_size = x._size;
					_capacity = x._capacity;
					_ptr = _allocator.allocate(_capacity);
					if (!_ptr) throw std::bad_alloc();
					for (size_type i = 0; i < _size; i++)
						_ptr[i] = x._ptr[i];
					return *this;
				}

				// Destructor

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
					return (_allocator.max_size());
				}

				void resize (size_type n, value_type val = value_type())
				{
					if (n > max_size()) throw std::length_error("max_size exceeded");
					if (n == _size) return ;
					if (n < _size)
					{
						for (size_type i = n; i < _size; i++)
							_ptr[i] = *end();
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
						size_type new_cap = n;
						pointer tmp = _allocator.allocate(new_cap);
						if (!tmp) throw std::bad_alloc();
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
							if (!_ptr) throw std::bad_alloc();
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
						if (!_ptr) throw std::bad_alloc();
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
						if (!_ptr) throw std::bad_alloc();
						_capacity = 1;
					}
					else if (_size == _capacity)
					{
						pointer tmp = _allocator.allocate(_capacity * 2);
						if (!tmp) throw std::bad_alloc();
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
					_ptr[_size] = *end();
					_size--;
				}

				iterator insert (iterator position, const value_type& val)
				{
					iterator ret;
					if (_capacity > _size)
					{
						iterator it = end();
						for (; it > position; it--) *it = *(it-1);
						*it = val;
						ret = it;
						_size++;
					}
					else if (_capacity)
					{
						pointer tmp = _allocator.allocate(_capacity * 2);
						if (!tmp) throw std::bad_alloc();
						iterator it = begin();
						iterator tmp_it = Iterator<value_type>(tmp);
						for (; it < position; it++) *(tmp_it++) = *it;
						*tmp_it = val;
						ret = tmp_it++;
						for (; it < end(); it++) *(tmp_it++) = *it;
						_allocator.deallocate(_ptr, _capacity);
						_ptr = tmp;
						_capacity *= 2;
						_size++;
					}
					else
					{
						push_back(val);
						ret = begin();
					}
					return (ret);
				}
				void insert (iterator position, size_type n, const value_type& val)
				{
					if (_capacity >= _size + n)
					{
						iterator s_it = position+n <= end() ? end() : position+n;
						iterator e_it = position+n > end() ? end() : position+n;
						for (; s_it >= position; s_it--)
						{
							if (s_it < e_it) *(s_it+n) = *s_it;
							*s_it = val;
						}
						_size += n;
					}
					else if (_capacity)
					{
						size_type new_cap = _size + n < _capacity*2 ? _capacity*2 : _size+n;
						while (new_cap < _size + n) new_cap *= 2;
						pointer tmp = _allocator.allocate(new_cap);
						if (!tmp) throw std::bad_alloc();
						iterator it = begin();
						iterator tmp_it = Iterator<value_type>(tmp);
						for (; it < position; it++) *(tmp_it++) = *it;
						for (size_type j = 0; j < n; j++) *(tmp_it++) = val;
						for (; it < end(); it++) *(tmp_it++) = *it;
						_allocator.deallocate(_ptr, _capacity);
						_ptr = tmp;
						_capacity = new_cap;
						_size += n;
					}
					else
					{
						_ptr = _allocator.allocate(n);
						for (size_type i = 0; i < n; i++) _ptr[i] = val;
						_capacity = n;
						_size = n;
					}
				}
				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* t = 0)
					{
						(void)t;
						size_type n = last - first;
						if (_capacity >= _size + n)
						{
							iterator it = end();
							for (; it >= position; it--) *(it+n) = *it;
							for(InputIterator tmp_it = first; tmp_it != last; tmp_it++) *(++it) = *tmp_it;
							_size += n;
						}
						else if (_capacity)
						{
							size_type new_cap = _size + n < _capacity*2 ? _capacity*2 : _size+n;
							while (new_cap < _size + n) new_cap *= 2;
							pointer tmp = _allocator.allocate(new_cap);
							if (!tmp) throw std::bad_alloc();
							size_type i = 0;
							iterator it = begin();
							for (; it < position; it++) tmp[i++] = *it;
							for (InputIterator tmp_it = first; tmp_it != last; tmp_it++) tmp[i++] = *tmp_it;
							for (; it < end(); it++) tmp[i++] = *it;
							_allocator.deallocate(_ptr, _capacity);
							_ptr = tmp;
							_capacity = new_cap;
							_size += n;
						}
						else
						{
							_ptr = _allocator.allocate(n);
							size_type i = 0;
							for (InputIterator tmp_it = first; tmp_it != last; tmp_it++) _ptr[i++] = *tmp_it;
							_capacity = n;
							_size = n;
						}
					}

				iterator erase (iterator position)
				{
					iterator it = position;
					iterator mid_it = begin() + _size/2;

					(*it).~T();
					if (it < mid_it)
					{
						for (; it != begin(); it--) *it = *(it - 1);
						_ptr += 1;
						_allocator.deallocate(_ptr-1, 1);
					}
					else
					{
						for (; it != end()-1; it++) *it = *(it + 1);
					}
					_size--;
					return position;
				}
				iterator erase (iterator first, iterator last)
				{
					size_type n = last - first;
					if (last == end())
					{
						for (iterator it = first; it != last; it++) (*it).~T();
					}
					else
					{
						for (iterator it = first; it < end()-n; it++)
						{
							(*it).~T();
							*it = *(it + n);
						}
					}

					_size -= n;
					return first;
				}

				void swap (Vector& x)
				{
					if (!_capacity)
					{
						x._allocator.deallocate(x._ptr, x._capacity);
						x._size = 0;
						x._capacity = 0;
						x._ptr = nullptr;
					}
					else
					{
						pointer tmp_ptr = _ptr;
						allocator_type tmp_alloc = _allocator;
						size_type tmp_size = _size;
						size_type tmp_capacity = _capacity;

						_allocator = x._allocator;
						_ptr = x._ptr;
						_size = x._size;
						_capacity = x._capacity;

						x._allocator = tmp_alloc;
						x._ptr = tmp_ptr;
						x._size = tmp_size;
						x._capacity = tmp_capacity;
					}
				}

				void clear()
				{
					for (size_type i = 0; i < _size; i++)
					{
						_ptr[i].~T();
					}
					_size = 0;
				}

				// Allocator

				allocator_type get_allocator() const { return _allocator; }

				// Non-members

				template <class U, class Allocator>
					friend bool operator	==(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs);
				template <class U, class Allocator>
					friend bool operator	!=(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs);
				template <class U, class Allocator>
					friend bool operator	<(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs);
				template <class U, class Allocator>
					friend bool operator	<=(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs);
				template <class U, class Allocator>
					friend bool operator	>(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs);
				template <class U, class Allocator>
					friend bool operator	>=(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs);

				template <class U, class Allocator>
					friend void swap (Vector<U,Allocator>& x, Vector<U,Allocator>& y);

			private:
				allocator_type	_allocator;
				pointer			_ptr;
				size_type		_size;
				size_type		_capacity;
		};

		template <class U, class Allocator>
			bool operator	==(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}
		template <class U, class Allocator>
			bool operator	!=(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs)
			{
				return !(lhs == rhs);
			}
		template <class U, class Allocator>
			bool operator	<(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs)
			{
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}
		template <class U, class Allocator>
			bool operator	<=(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs)
			{
				return !(rhs < lhs);
			}
		template <class U, class Allocator>
			bool operator	>(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs)
			{
				return rhs < lhs;
			}
		template <class U, class Allocator>
			bool operator	>=(const Vector<U,Allocator>& lhs, const Vector<U,Allocator>& rhs)
			{
				return !(lhs < rhs);
			}
		
		template <class U, class Allocator>
			void swap (Vector<U,Allocator>& x, Vector<U,Allocator>& y)
			{
				x.swap(y);
			}
}

#endif
