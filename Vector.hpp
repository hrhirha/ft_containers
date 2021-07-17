#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <iterator>

namespace ft
{
	template <class T>
		class Iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
		T	*_ptr;
		public:
		Iterator();
		Iterator(Iterator const &x) { *this = x; };
		Iterator	&operator =(Iterator const &x) { _ptr = &(*x); return *this; };
		~Iterator();

		bool			operator ==(Iterator const &) const;
		bool			operator !=(Iterator const &) const;

		T const			&operator *() const;
		T				&operator *() { return (*_ptr); };

		Iterator		&operator ++() { ++_ptr; return *this; };
		Iterator		&operator ++(int);

		Iterator		&operator --() { --_ptr; return *this; };
		Iterator		&operator --(int);

		Iterator		&operator +(int);
		Iterator		&operator +(Iterator const &);
		Iterator		&operator -(int);

		bool			operator >(Iterator const &) const;
		bool			operator <(Iterator const &) const;
		bool			operator >=(Iterator const &) const;
		bool			operator <=(Iterator const &) const;

		void			operator +=(int);
		void			operator -=(int);

		T				&operator [](size_t);
	};
	template <class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				typedef T											value_type;
				typedef Alloc										allocator_type;
				typedef size_t										size_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef typename Iterator<T>						iterator;

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
