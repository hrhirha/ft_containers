/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:03:26 by hrhirha           #+#    #+#             */
/*   Updated: 2021/10/30 17:36:49 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
# include "RBTree.hpp"

namespace ft
{
	template <class Node, class Tree, class P>
		class map_iterator : std::iterator<std::bidirectional_iterator_tag, P>
	{
		public:
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, P>::iterator_category
				iterator_category;
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, P>::value_type
				value_type;
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, P>::difference_type
				difference_type;
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, P>::pointer
				pointer;
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, P>::reference
				reference;

			map_iterator() : _tree(NULL), _node(NULL) {}
			map_iterator(Node *n, Tree *t) : _tree(t), _node(n) {}
			map_iterator(const map_iterator &it) { *this = it; }
			map_iterator &operator =(const map_iterator &it) { _tree = it._tree; _node = it._node; return *this;}
			~map_iterator() {}

			operator map_iterator<Node,Tree,const P>() const { return map_iterator<Node,Tree,const P>(_node, _tree); }

			bool		operator ==(const map_iterator &it) const { return _node == it._node; }
			bool		operator !=(const map_iterator &it) const { return !(*this == it); }

			reference	operator *() const { return *_node->elem; }
			pointer		operator ->() const { return _node->elem; }

			Node *getNode() const { return _node; }

			map_iterator	&operator ++()
			{
				if (_node == _tree->right_most())
				{
					_node = _tree->getEnd();
				}
				else if (!_node->parent)
				{
					if (!_node->RCHILD) _node = _node->parent;
					else _node = right_successor(_node);
				}
				else if (_node == _node->parent->LCHILD && !_node->RCHILD)
					_node = _node->parent;
				else if (_node->RCHILD)
					_node = right_successor(_node);
				else
				{
					Node *x = _node;
					while (x->parent && x == x->parent->RCHILD)
						x = x->parent;
					_node = x->parent;
				}
				return *this;
			}
			map_iterator	operator ++(int) { map_iterator tmp = *this; ++(*this); return tmp; }

			map_iterator	&operator --()
			{
				if (_node == _tree->getEnd())
				{
					_node = _tree->right_most();
				}
				else if (!_node->parent)
				{
					if (!_node->LCHILD) _node = _node->parent;
					else _node = left_successor(_node);
				}
				else if (_node == _node->parent->RCHILD && !_node->LCHILD)
					_node = _node->parent;
				else if (_node->LCHILD)
					_node = left_successor(_node);
				else
				{
					Node *x = _node;
					while (x->parent && x == x->parent->LCHILD)
						x = x->parent;
					_node = x->parent;
				}
				return *this;
			}
			map_iterator	operator --(int) { map_iterator tmp = *this; --(*this); return tmp; }

		private:
			Tree *_tree;
			Node *_node;
	};
}

#endif
