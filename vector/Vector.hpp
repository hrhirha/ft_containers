/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:08:20 by hrhirha           #+#    #+#             */
/*   Updated: 2021/11/01 16:03:11 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include "Vector_Iterator.hpp"
# include "../tools/Iterator_Traits.hpp"
# include "../tools/Reverse_Iterator.hpp"
# include "../tools/types_traits.hpp"
# include "../tools/Algorithm.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
		class vector
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
				typedef typename ft::Iterator_traits<iterator>::difference_type
					difference_type;

				// Constructors

				explicit vector(const allocator_type &alloc = allocator_type()) :
					_allocator(alloc), _ptr(NULL), _size(0), _capacity(0) {}

				explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) :
					_allocator(alloc), _size(n), _capacity(n)
				{
					if (_capacity)
					{
						_ptr = _allocator.allocate(_capacity);
						if (!_ptr) throw std::bad_alloc();
						for (size_type i = 0; i < _size; i++)
							_allocator.construct(&_ptr[i], val);
					}
					else _ptr = NULL;
				}
				template <class InputIter>
					vector(InputIter first, InputIter last,
					typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type* t = 0,
							const allocator_type &alloc = allocator_type()): _allocator(alloc)
					{
						(void)t;
						InputIter it = first;
						_capacity = std::distance(first, last);
						if (_capacity > max_size()) throw std::length_error("vector");
						_size = _capacity;
						_ptr = _allocator.allocate(_capacity);
						if (!_ptr) throw std::bad_alloc();
						for (size_type i = 0; i < _size && it != last; i++)
						{
							_allocator.construct(&_ptr[i], *(it++));
						}
					}

				vector(const vector &x) : _ptr(NULL), _size(0), _capacity(0)
				{
					*this = x;
				}
				vector	&operator =(const vector &x)
				{
					if (_capacity)
					{
						for (size_type i = 0; i < _size; i++)
							_allocator.destroy(&_ptr[i]);
						_allocator.deallocate(_ptr, _capacity);
					}
					_size = x._size;
					_capacity = x._capacity;
					if (_capacity)
					{
						_ptr = _allocator.allocate(_capacity);
						if (!_ptr) throw std::bad_alloc();
					}
					for (size_type i = 0; i < _size; i++)
						_allocator.construct(&_ptr[i], x._ptr[i]);
					return *this;
				}

				// Destructor

				~vector()
				{
					if (_capacity)
					{
						for (size_type i = 0; i < _size; i++)
							_allocator.destroy(&_ptr[i]);
						_allocator.deallocate(_ptr, _capacity);
						_size = 0;
						_capacity = 0;
					}
				}

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
					if (n > max_size()) throw std::length_error("vector");
					if (n == _size) return ;
					if (n < _size)
					{
						for (size_type i = n; i < _size; i++)
							_allocator.destroy(&_ptr[i]);
						_size = n;
					}
					else
					{
						if (n > _capacity)
							reserve((n > _capacity*2)?n:_capacity*2);
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
							_allocator.construct(&tmp[i], _ptr[i]);
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
					if (n >= _size) throw std::out_of_range("vector");
					return (*this)[n];
				}
				const_reference	at (size_type n) const
				{
					if (n >= _size) throw std::out_of_range("vector");
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
							_allocator.construct(&_ptr[i], *(first++));
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
						_allocator.construct(&_ptr[i], val);
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
						{
							_allocator.construct(&tmp[i], _ptr[i]);
							_allocator.destroy(&_ptr[i]);
						}
						_allocator.deallocate(_ptr, _capacity);
						_ptr = tmp;
						_capacity *= 2;
					}
					_allocator.construct(&_ptr[_size], val);
					_size++;
				}
				void pop_back()
				{
					_allocator.destroy(&_ptr[_size-1]);
					_size--;
				}

				iterator insert (iterator position, const value_type& val)
				{
					pointer ret = NULL;
					size_type pos = std::distance(begin(), position);
					if (pos > max_size()) throw std::length_error("vector");
					if (_capacity > _size)
					{
						size_type i = _size;
						for (; i > pos; i--) std::swap(_ptr[i], _ptr[i-1]);
						_allocator.construct(&_ptr[i], val);
						ret = _ptr + pos;
						_size++;
					}
					else if (_capacity)
					{
						pointer tmp = _allocator.allocate(_capacity * 2);
						if (!tmp) throw std::bad_alloc();
						size_type i = 0;
						size_type tmp_i = 0;
						for (; i < pos; i++) _allocator.construct(&tmp[tmp_i++], _ptr[i]);
						_allocator.construct(&tmp[tmp_i], val);
						for (; i < _size; i++)
							_allocator.construct(&tmp[++tmp_i], _ptr[i]);
						_allocator.deallocate(_ptr, _capacity);
						_ptr = tmp;
						ret = _ptr + pos;
						_capacity *= 2;
						_size++;
					}
					else
					{
						push_back(val);
						ret = _ptr;
					}
					return (iterator(ret));
				}
				void insert (iterator position, size_type n, const value_type& val)
				{
					size_type pos = std::distance(begin(), position);
					if (pos > max_size()) throw std::length_error("vector");
					if (_capacity >= _size + n)
					{
						if (_size >= pos+n)
						{
							for (size_type i = _size-1; i >= pos && i < max_size(); i--)
							{
								_allocator.construct(&_ptr[i+n], _ptr[i]);
								_allocator.destroy(&_ptr[i]);
								if (i < pos+n) _allocator.construct(&_ptr[i], val);
							}
						}
						else
						{
							for (size_type i = pos+n-1; i >= pos && i < max_size(); i--)
							{
								if (i < _size)
								{
									_allocator.construct(&_ptr[i+n], _ptr[i]);
									_allocator.destroy(&_ptr[i]);
								}
								_allocator.construct(&_ptr[i], val);
							}
						}
						_size += n;
					}
					else if (_capacity)
					{
						size_type new_cap = _size + n < _capacity*2 ? _capacity*2 : _size+n;
						pointer tmp = _allocator.allocate(new_cap);
						if (!tmp) throw std::bad_alloc();
						size_type i = 0;
						size_type tmp_i = 0;
						for (; i < pos; i++) _allocator.construct(&tmp[tmp_i++], _ptr[i]);
						for (size_type j = 0; j < n; j++) _allocator.construct(&tmp[tmp_i++], val);
						for (; i < _size; i++) _allocator.construct(&tmp[tmp_i++], _ptr[i]);
						_allocator.deallocate(_ptr, _capacity);
						_ptr = tmp;
						_capacity = new_cap;
						_size += n;
					}
					else
					{
						_ptr = _allocator.allocate(n);
						for (size_type i = 0; i < n; i++) _allocator.construct(&_ptr[i], val);
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
						size_type pos = std::distance(begin(), position);
						if (pos > max_size()) throw std::length_error("vector");
						if (_capacity >= _size + n)
						{
							if (_size >= pos+n)
							{
								for (size_type i = _size-1; i >= pos && i < max_size(); i--)
								{
									_allocator.construct(&_ptr[i+n], _ptr[i]);
									_allocator.destroy(&_ptr[i]);
									if (i < pos+n) _allocator.construct(&_ptr[i], *--last);
								}
							}
							else
							{
								for (size_type i = pos+n-1; i >= pos && i < max_size(); i--)
								{
									if (i < _size)
									{
										_allocator.construct(&_ptr[i+n], _ptr[i]);
										_allocator.destroy(&_ptr[i]);
									}
									_allocator.construct(&_ptr[i], *--last);
								}
							}
							_size += n;
						}
						else if (_capacity)
						{
							size_type new_cap = _size + n < _capacity*2 ? _capacity*2 : _size+n;
							pointer tmp = _allocator.allocate(new_cap);
							if (!tmp) throw std::bad_alloc();
							size_type i = 0;
							size_type tmp_i = 0;
							for (; i < pos; i++)
								_allocator.construct(&tmp[tmp_i++], _ptr[i]);
							for (InputIterator tmp_it = first; tmp_it != last; tmp_it++)
								_allocator.construct(&tmp[tmp_i++], *tmp_it);
							for (; i < _size; i++)
								_allocator.construct(&tmp[tmp_i++], _ptr[i]);
							_allocator.deallocate(_ptr, _capacity);
							_ptr = tmp;
							_capacity = new_cap;
							_size += n;
						}
						else
						{
							_ptr = _allocator.allocate(n);
							size_type i = 0;
							for (InputIterator tmp_it = first; tmp_it != last; tmp_it++)
								_allocator.construct(&_ptr[i++], *tmp_it);
							_capacity = n;
							_size = n;
						}
					}

				iterator erase (iterator position)
				{
					difference_type dif = position - begin();
					for (size_type i = dif ; i < _size-1; i++)
						std::swap(_ptr[i], _ptr[i+1]);
					_ptr[_size-1].~T();
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

				void swap (vector& x)
				{
					if (!_capacity)
					{
						x._allocator.deallocate(x._ptr, x._capacity);
						x._size = 0;
						x._capacity = 0;
						x._ptr = NULL;
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

			private:
				allocator_type	_allocator;
				pointer			_ptr;
				size_type		_size;
				size_type		_capacity;
		};

		template <class U, class Allocator>
			bool operator	==(const vector<U,Allocator>& lhs, const vector<U,Allocator>& rhs)
			{
				return lhs.size() == rhs.size() && (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}
		template <class U, class Allocator>
			bool operator	!=(const vector<U,Allocator>& lhs, const vector<U,Allocator>& rhs)
			{
				return !(lhs == rhs);
			}
		template <class U, class Allocator>
			bool operator	<(const vector<U,Allocator>& lhs, const vector<U,Allocator>& rhs)
			{
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}
		template <class U, class Allocator>
			bool operator	<=(const vector<U,Allocator>& lhs, const vector<U,Allocator>& rhs)
			{
				return !(rhs < lhs);
			}
		template <class U, class Allocator>
			bool operator	>(const vector<U,Allocator>& lhs, const vector<U,Allocator>& rhs)
			{
				return rhs < lhs;
			}
		template <class U, class Allocator>
			bool operator	>=(const vector<U,Allocator>& lhs, const vector<U,Allocator>& rhs)
			{
				return !(lhs < rhs);
			}
		
		template <class U, class Allocator>
			void swap (vector<U,Allocator>& x, vector<U,Allocator>& y)
			{
				x.swap(y);
			}
}

#endif
