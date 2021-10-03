#ifndef Reverse_Iterator_HPP
# define Reverse_Iterator_HPP
# include <iostream>
# include "Iterator_Traits.hpp"

namespace ft
{
	template <class Iterator>
		class Reverse_Iterator
		{
			public:
				typedef Iterator													iterator_type;
				typedef typename ft::Iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename ft::Iterator_traits<Iterator>::value_type			value_type;
				typedef typename ft::Iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename ft::Iterator_traits<Iterator>::pointer				pointer;
				typedef typename ft::Iterator_traits<Iterator>::reference			reference;

				Reverse_Iterator() {};
				explicit Reverse_Iterator(iterator_type it) : _base_iterator(it) {};
				template <class Iter>
					Reverse_Iterator(const Reverse_Iterator<Iter> &rev_it) { *this = rev_it; };
				Reverse_Iterator	&operator =(Reverse_Iterator const &rev_it)
				{
					_base_iterator = rev_it._base_iterator; return *this;
				}

				~Reverse_Iterator() {};

				iterator_type	base() const { return (_base_iterator); };

				reference			operator *() const { return *(_base_iterator - 1); };
				pointer				operator ->() const { return &(*(_base_iterator - 1)); };

				Reverse_Iterator&	operator ++()
				{
					--_base_iterator; return *this + 1;
				}
				Reverse_Iterator&	operator ++(int)
				{
					Reverse_Iterator tmp = *this; ++(*this); return (tmp + 1);
				}

				Reverse_Iterator&	operator --()
				{
					++_base_iterator; return *this + 1;
				}
				Reverse_Iterator&	operator --(int)
				{
					Reverse_Iterator tmp = *this; --(*this); return (tmp + 1);
				}

				Reverse_Iterator&	operator +=(difference_type n)
				{ _base_iterator -= n; return (*this + 1); }
				Reverse_Iterator&	operator -=(difference_type n)
				{ _base_iterator += n; return (*this + 1); }

				Reverse_Iterator	operator +(difference_type n) const
				{
					return Reverse_Iterator(_base_iterator - n);
				}
				Reverse_Iterator	operator -(difference_type n) const
				{
					return Reverse_Iterator(_base_iterator + n);
				}

				reference			operator[] (difference_type n) const
				{ return (_base_iterator[-n - 1]); }

				
				friend bool operator ==(const Reverse_Iterator<Iterator>& lhs,
					const Reverse_Iterator<Iterator>& rhs);
				friend bool operator !=(const Reverse_Iterator<Iterator>& lhs,
					const Reverse_Iterator<Iterator>& rhs);
				friend bool operator <(const Reverse_Iterator<Iterator>& lhs,
					const Reverse_Iterator<Iterator>& rhs);
				friend bool operator <=(const Reverse_Iterator<Iterator>& lhs,
					const Reverse_Iterator<Iterator>& rhs);
				friend bool operator >(const Reverse_Iterator<Iterator>& lhs,
					const Reverse_Iterator<Iterator>& rhs);
				friend bool operator >=(const Reverse_Iterator<Iterator>& lhs,
					const Reverse_Iterator<Iterator>& rhs);
				friend Reverse_Iterator<Iterator> operator +(
					typename Reverse_Iterator<Iterator>::difference_type n,
					const Reverse_Iterator<Iterator>& rev_it);
				friend typename Reverse_Iterator<Iterator>::difference_type operator -(
					const Reverse_Iterator<Iterator>& lhs,
					const Reverse_Iterator<Iterator>& rhs);

			private:
				iterator_type	_base_iterator;
		};

	template <class Iterator>
		bool operator ==(const Reverse_Iterator<Iterator>& lhs,
				const Reverse_Iterator<Iterator>& rhs)
		{ return lhs._base_iterator == rhs._base_iterator; }

	template <class Iterator>
		bool operator !=(const Reverse_Iterator<Iterator>& lhs,
				const Reverse_Iterator<Iterator>& rhs)
		{ return lhs._base_iterator != rhs._base_iterator; }

	template <class Iterator>
		bool operator <(const Reverse_Iterator<Iterator>& lhs,
				const Reverse_Iterator<Iterator>& rhs)
		{ return lhs._base_iterator > rhs._base_iterator; }

	template <class Iterator>
		bool operator <=(const Reverse_Iterator<Iterator>& lhs,
				const Reverse_Iterator<Iterator>& rhs)
		{ return lhs._base_iterator >= rhs._base_iterator; }

	template <class Iterator>
		bool operator >(const Reverse_Iterator<Iterator>& lhs,
				const Reverse_Iterator<Iterator>& rhs)
		{ return lhs._base_iterator < rhs._base_iterator; }

	template <class Iterator>
		bool operator >=(const Reverse_Iterator<Iterator>& lhs,
				const Reverse_Iterator<Iterator>& rhs)
		{ return lhs._base_iterator <= rhs._base_iterator; }

	template <class Iterator>
		Reverse_Iterator<Iterator> operator +(
				typename Reverse_Iterator<Iterator>::difference_type n,
				const Reverse_Iterator<Iterator>& rev_it)
		{
			return rev_it + n;
		}

	template <class Iterator>
		typename Reverse_Iterator<Iterator>::difference_type operator -(
				const Reverse_Iterator<Iterator>& lhs,
				const Reverse_Iterator<Iterator>& rhs)
		{
			return rhs._base_iterator - lhs._base_iterator;
		}
}

#endif
