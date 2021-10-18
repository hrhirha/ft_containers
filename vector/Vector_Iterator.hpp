/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector_Iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:08:31 by hrhirha           #+#    #+#             */
/*   Updated: 2021/10/18 18:08:32 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP
# include <iostream>
# include <iterator>

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

			Iterator() {}
			Iterator(pointer p) : _ptr(p) {};
			Iterator(Iterator const &x) { *this = x; }
			Iterator		&operator =(Iterator const &x) { _ptr = x._ptr; return *this; }

			~Iterator() {}
			
			operator Iterator<const T>() const {return Iterator<const T>(_ptr);}

			reference		operator *() const { return (*_ptr); };
			pointer			operator ->() const { return &(*_ptr); };

			Iterator		&operator ++() { ++_ptr; return *this; };
			Iterator		operator ++(int) { Iterator tmp = *this; ++(*this); return (tmp); };

			Iterator		&operator --() { --_ptr; return *this; };
			Iterator		operator --(int) { Iterator tmp = *this; --(*this); return (tmp); };

			Iterator		&operator +=(int n) { _ptr += n; return *this; };
			Iterator		&operator -=(int n) { _ptr -= n; return *this; };

			Iterator		operator +(int n) const { return (Iterator(_ptr + n)); };
			Iterator		operator -(int n) const { return (Iterator(_ptr - n)); };
			difference_type	operator -(Iterator const &x) const { return (_ptr - x._ptr); };

			bool			operator ==(Iterator const &x) const { return _ptr == x._ptr; };
			bool			operator !=(Iterator const &x) const { return _ptr != x._ptr; };
			bool			operator >(Iterator const &x) const { return _ptr > x._ptr; };
			bool			operator <(Iterator const &x) const { return _ptr < x._ptr; };
			bool			operator >=(Iterator const &x) const { return _ptr >= x._ptr; };
			bool			operator <=(Iterator const &x) const { return _ptr <= x._ptr; };

			T				&operator [](size_t n) const { return (*this + n)._ptr[n]; };

		private:
			pointer	_ptr;
	};

	template <class T>
		static Iterator<T> operator +(int n, Iterator<T> const &x) { return x + n; }
}

#endif
