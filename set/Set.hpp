/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:04:02 by hrhirha           #+#    #+#             */
/*   Updated: 2021/10/30 18:41:07 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include "RBTree.hpp"
# include "set_iterator.hpp"
# include "../tools/Reverse_Iterator.hpp"
# include "../vector/Vector.hpp"

namespace ft
{
	template <class T,
			 class Compare = std::less<T>,
			 class Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T														key_type;
			typedef T														value_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef RBTree<value_type, key_compare, allocator_type>			rbtree;
			typedef RBNode<value_type>										node;
			typedef typename ft::set_iterator<node,rbtree,value_type>		iterator;
			typedef typename ft::set_iterator<node,rbtree,const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::Iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

			// Constructor

			explicit set (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _size(0), _comp(comp)
			{
				_tree = _tree_alloc.allocate(1);
				_tree_alloc.construct(_tree);
				_root = _tree->getRoot();
			}

			template <class InputIterator>
				set (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp)
			{
				_tree = _tree_alloc.allocate(1);
				_tree_alloc.construct(_tree);
				_size = 0;
				insert(first, last);
				_root = _tree->getRoot();
			}

			set (const set& x) : _tree_alloc(x._tree_alloc), _alloc(x._alloc), _comp(x._comp)
			{
				_tree = _tree_alloc.allocate(1);
				_tree_alloc.construct(_tree);
				*this = x;
			}
			set	&operator =(const set& x)
			{
				clear();
				insert(x.begin(), x.end());
				return *this;
			}

			// Destructor

			~set()
			{
				clear();
				_tree_alloc.destroy(_tree);
				_tree_alloc.deallocate(_tree,1);
			}

			// Iterators

			iterator begin()
			{
				node *node = _tree->left_most();
				return iterator(node, _tree);
			}
			const_iterator begin() const
			{
				node *node = _tree->left_most();
				return const_iterator(node, _tree);
			}
			iterator end()
			{
				return iterator(_tree->getEnd(), _tree);
			}
			const_iterator end() const
			{
				return const_iterator(_tree->getEnd(), _tree);
			}
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			// Capacity

			bool empty() const { return _size==0; }
			size_type size() const { return _size; }
			size_type max_size() const { return _alloc.max_size(); }

			// Modifiers

			ft::pair<iterator,bool> insert (const value_type& val)
			{
				ft::pair<node*, bool> ans = _tree->insert(val);
				if (ans.second) _size++;
				_root = _tree->getRoot();
				return ft::pair<iterator, bool>(iterator(ans.first, _tree), ans.second);
			}
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				ft::pair<iterator, bool> ans = insert(val);
				return ans.first;
			}
			template <class InputIterator>
				void insert (InputIterator first, InputIterator last)
				{
					for (InputIterator it = first; it != last; it++)
						insert(*it);
				}
			
			void erase (iterator position)
			{
				if (_tree->erase_node(position.getNode()))
					_size--;
				_root = _tree->getRoot();
			}
			size_type erase (const value_type& val)
			{
				size_type ans = _tree->erase(val);
				if (ans) _size--;
				_root = _tree->getRoot();
				return ans;
			}
			void erase (iterator first, iterator last)
			{
				ft::vector<key_type> v;
				for (; first != last; first++) v.push_back(*first);
				for (size_type i = 0; i < v.size(); i++)
					erase(v[i]);
			}

			void	swap(set &x)
			{
				std::swap(_tree, x._tree);
				std::swap(_root, x._root);
				std::swap(_size, x._size);
			}
			void clear()
			{
				erase(begin(), end());
				_size = 0;
			}

			// Observers

			key_compare key_comp() const { return _comp; }
			value_compare value_comp() const { return _comp; }

			// operations

			iterator find (const value_type& val) const
			{
				node *ans = _tree->find(val);
				if (!ans) return iterator(_tree->getEnd(), _tree);
				return iterator(ans, _tree);
			}

			size_type count (const value_type& val) const
			{
				if (find(val) == iterator(_tree->getEnd(), _tree)) return 0;
				return 1;
			}

			iterator				lower_bound (const value_type& val) const
			{
				node *ans = _tree->lower_bound(val, _tree->getRoot());
				return iterator(ans, _tree);
			}
			iterator				upper_bound (const value_type& val) const
			{
				return iterator(_tree->upper_bound(val, _tree->getRoot()), _tree);
			}

			pair<iterator,iterator>	equal_range (const value_type& val) const
			{
				return ft::make_pair(lower_bound(val), upper_bound(val));
			}

			// Allocator

			allocator_type get_allocator() const { return _alloc; }

		private:
			rbtree											*_tree;
			node											*_root;
			typename Alloc::template rebind<rbtree>::other	_tree_alloc;
			allocator_type									_alloc;
			size_type										_size;
			key_compare										_comp;
	};

	// Relational operations
	
	template <class T, class Compare, class Alloc>
		bool operator== ( const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs )
		{
			return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
	template <class T, class Compare, class Alloc>
		bool operator!= ( const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs )
		{
			return !(lhs == rhs);
		}
	template <class T, class Compare, class Alloc>
		bool operator<  ( const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs )
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
	template <class T, class Compare, class Alloc>
		bool operator<= ( const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs )
		{
			return !(rhs < lhs);
		}
	template <class T, class Compare, class Alloc>
		bool operator>  ( const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs )
		{
			return rhs < lhs;
		}
	template <class T, class Compare, class Alloc>
		bool operator>= ( const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs )
		{
			return !(lhs < rhs);
		}
	
	// swap
	
	template <class T, class Compare, class Alloc>
		void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
		{
			x.swap(y);
		}
}

#endif
