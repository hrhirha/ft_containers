/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:07:52 by hrhirha           #+#    #+#             */
/*   Updated: 2021/10/29 11:36:30 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP
# include <iostream>

namespace ft
{
	template <class T1, class T2>
		struct pair
		{
			typedef T1 first_type;
			typedef T2 second_type;

			first_type	first;
			second_type	second;

			pair() : first(), second() {}
			~pair() { first.~first_type(); second.~second_type(); }
			pair (const first_type& a, const second_type& b) : first(a), second(b) {}
			template<class U, class V>
				pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
			pair& operator= (const pair& pr) { first = pr.first; second = pr.second; return *this; }
		};

	template <class T1, class T2>
		bool operator	==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class T1, class T2>
		bool operator	!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs == rhs); }

	template <class T1, class T2>
		bool operator	<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
		bool operator	<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs < lhs); }

	template <class T1, class T2>
		bool operator	>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs < lhs; }

	template <class T1, class T2>
		bool operator	>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs < rhs); }

	// make_pair

	template <class T1, class T2>
		pair<T1,T2> make_pair(T1 x, T2 y)
		{
			return (pair<T1, T2>(x, y));
		}
}

#endif
