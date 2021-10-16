#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
# include "RBTree.hpp"

namespace ft
{
	template <class T1, class T2, class C, class A>
		class map_iterator : std::iterator<std::bidirectional_iterator_tag, ft::pair<const T1,T2> >
	{
		public:
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, ft::pair<const T1,T2> >::iterator_category
				iterator_category;
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, ft::pair<const T1,T2> >::value_type
				value_type;
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, ft::pair<const T1,T2> >::difference_type
				difference_type;
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, ft::pair<const T1,T2> >::pointer
				pointer;
			typedef typename
				std::iterator<std::bidirectional_iterator_tag, ft::pair<const T1,T2> >::reference
				reference;

			map_iterator() : _tree(), _node(NULL) {}
			map_iterator(RBNode<T1,T2> *n, RBTree<T1,T2,C,A> t) : _tree(t), _node(n) {}
			map_iterator(const map_iterator<T1,T2,C,A> &it) : _tree(it._tree), _node(it._node) {}
			map_iterator &operator =(const map_iterator<T1,T2,C,A> &it) { _tree = it._tree; _node = it._node; return *this;}
			~map_iterator() {}

			bool		operator ==(const map_iterator<T1,T2,C,A> &it) const { return _node == it._node; }
			bool		operator !=(const map_iterator<T1,T2,C,A> &it) const { return !(*this == it); }

			reference	operator *() const { return *_node->elem; }
			pointer		operator ->() const { return _node->elem; }

			RBNode<T1,T2> *getNode() const { return _node; }

			map_iterator	&operator ++()
			{
				if (_node == _tree.right_most())
				{
					_node = _tree.getEnd();
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
					RBNode<T1,T2> *x = _node;
					while (x->parent && x == x->parent->RCHILD)
						x = x->parent;
					_node = x->parent;
				}
				return *this;
			}
			map_iterator	operator ++(int) { map_iterator tmp = *this; ++(*this); return tmp; }

			map_iterator	&operator --()
			{
				if (_node == _tree.getEnd())
				{
					_node = _tree.right_most();
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
					RBNode<T1,T2> *x = _node;
					while (x->parent && x == x->parent->LCHILD)
						x = x->parent;
					_node = x->parent;
				}
				return *this;
			}
			map_iterator	operator --(int) { map_iterator tmp = *this; --(*this); return tmp; }

		private:
			RBTree<T1,T2,C,A> _tree;
			RBNode<T1,T2> *_node;
	};
}

#endif
