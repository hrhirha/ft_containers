#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include <iostream>
# include "Iterator_Traits.hpp"

namespace ft
{
	template <class Iterator>
		class reverse_iterator
		{
			public:
				typedef Iterator													iterator_type;
				typedef typename ft::Iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename ft::Iterator_traits<Iterator>::value_type			value_type;
				typedef typename ft::Iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename ft::Iterator_traits<Iterator>::pointer				pointer;
				typedef typename ft::Iterator_traits<Iterator>::reference			reference;

				reverse_iterator() : _base_iterator() {};
				explicit reverse_iterator(iterator_type it) : _base_iterator(it)
				{
				}
				template <class Iter>
					reverse_iterator(const reverse_iterator<Iter> &rev_it)
					{
						*this = rev_it;
					}
				template <class Iter>
				reverse_iterator	&operator =(const reverse_iterator<Iter> &rev_it)
				{
					_base_iterator = rev_it.base();
					return *this;
				}

				~reverse_iterator() {};

				iterator_type	base() const { return (_base_iterator); };

				operator reverse_iterator<const Iterator>() const
				{return reverse_iterator<const Iterator>(_base_iterator);}

				reference			operator *() const
				{
					iterator_type tmp = _base_iterator; return *--tmp;
				}
				pointer				operator ->() const
				{
					iterator_type tmp = _base_iterator; return &(*--tmp);
				}

				reverse_iterator	&operator ++()
				{
					--_base_iterator; return *this;
				}
				reverse_iterator	operator ++(int)
				{
					reverse_iterator tmp = *this; ++(*this); return (tmp);
				}

				reverse_iterator	&operator --()
				{
					++_base_iterator; return *this;
				}
				reverse_iterator	operator --(int)
				{
					reverse_iterator tmp = *this; --(*this); return (tmp);
				}

				reverse_iterator	&operator +=(difference_type n)
				{ _base_iterator -= n; return (*this); }
				reverse_iterator	&operator -=(difference_type n)
				{ _base_iterator += n; return (*this); }

				reverse_iterator	operator +(difference_type n) const
				{
					return reverse_iterator(_base_iterator - n);
				}
				reverse_iterator	operator -(difference_type n) const
				{
					return reverse_iterator(_base_iterator + n);
				}

				reference			operator[] (difference_type n) const
				{ return (_base_iterator[-n - 1]); }


				template <class Iter>
				friend bool operator ==(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs);
				template <class Iter>
				friend bool operator !=(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs);
				template <class Iter>
				friend bool operator <(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs);
				template <class Iter>
				friend bool operator <=(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs);
				template <class Iter>
				friend bool operator >(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs);
				template <class Iter>
				friend bool operator >=(const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs);

				template <class Iter>
				friend reverse_iterator<Iter> operator +(
					typename reverse_iterator<Iter>::difference_type n,
					const reverse_iterator<Iter>& rev_it);
				template <class Iter>
				friend typename reverse_iterator<Iter>::difference_type operator -(
					const reverse_iterator<Iter>& lhs,
					const reverse_iterator<Iter>& rhs);

			private:
				iterator_type	_base_iterator;
		};

	template <class Iterator>
		bool operator ==(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{ return lhs._base_iterator == rhs._base_iterator; }

	template <class Iterator>
		bool operator !=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{ return lhs._base_iterator != rhs._base_iterator; }

	template <class Iterator>
		bool operator <(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{ return lhs._base_iterator > rhs._base_iterator; }

	template <class Iterator>
		bool operator <=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{ return lhs._base_iterator >= rhs._base_iterator; }

	template <class Iterator>
		bool operator >(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{ return lhs._base_iterator < rhs._base_iterator; }

	template <class Iterator>
		bool operator >=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{ return lhs._base_iterator <= rhs._base_iterator; }

	template <class Iterator>
		reverse_iterator<Iterator> operator +(
				typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rev_it)
		{
			return rev_it + n;
		}

	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator -(
				const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return rhs._base_iterator - lhs._base_iterator;
		}
}

#endif
