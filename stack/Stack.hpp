/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:07:21 by hrhirha           #+#    #+#             */
/*   Updated: 2021/10/18 19:45:31 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "../vector/Vector.hpp"

namespace ft
{
	template <class T, class Container = ft::Vector <T> >
		class stack
		{
			public :
				typedef T			value_type;
				typedef Container	container_type;
				typedef size_t		size_type;

				explicit stack (const container_type& ctnr = container_type()) :
					c(ctnr) {}

				bool empty() const { return c.empty(); }
				size_type size() const { return c.size(); }
				value_type& top() { return c.back(); }
				const value_type& top() const { return c.back(); }
				void push (const value_type& val) { c.push_back(val); }
				void pop() { c.pop_back(); }


				template <class U, class C>
				friend bool operator== (const stack<U,C>& lhs, const stack<U,C>& rhs);
				template <class U, class C>
				friend bool operator!= (const stack<U,C>& lhs, const stack<U,C>& rhs);
				template <class U, class C>
				friend bool operator<  (const stack<U,C>& lhs, const stack<U,C>& rhs);
				template <class U, class C>
				friend bool operator<= (const stack<U,C>& lhs, const stack<U,C>& rhs);
				template <class U, class C>
				friend bool operator>  (const stack<U,C>& lhs, const stack<U,C>& rhs);
				template <class U, class C>
				friend bool operator>= (const stack<U,C>& lhs, const stack<U,C>& rhs);

			protected :
				Container c;
		};

	template <class U, class C>
		bool operator	==(const stack<U,C>& lhs, const stack<U,C>& rhs)
		{ return lhs.c == rhs.c; }
	template <class U, class C>
		bool operator	!=(const stack<U,C>& lhs, const stack<U,C>& rhs)
		{ return lhs.c != rhs.c; }
	template <class U, class C>
		bool operator	<(const stack<U,C>& lhs, const stack<U,C>& rhs)
		{ return lhs.c < rhs.c; }
	template <class U, class C>
		bool operator	<=(const stack<U,C>& lhs, const stack<U,C>& rhs)
		{ return lhs.c <= rhs.c; }
	template <class U, class C>
		bool operator	>(const stack<U,C>& lhs, const stack<U,C>& rhs)
		{ return lhs.c > rhs.c; }
	template <class U, class C>
		bool operator	>=(const stack<U,C>& lhs, const stack<U,C>& rhs)
		{ return lhs.c >= rhs.c; }
}

#endif
