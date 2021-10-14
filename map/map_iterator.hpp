#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
# include "RBTree.hpp"

namespace ft
{
	template <class T1, class T2>
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

			map_iterator() : _root(NULL) {}
			map_iterator(RBNode<T1,T2> *node) : _root(node) {}
			map_iterator(const map_iterator<T1,T2> &it) : _root(it._root) {}
			map_iterator &operator =(const map_iterator<T1,T2> &it) { _root = it._root; return *this;}
			~map_iterator() {}

			bool		operator ==(const map_iterator<T1,T2> &it) const { return _root == it._root; }
			bool		operator !=(const map_iterator<T1,T2> &it) const { return !(*this == it); }

			reference	operator *() const { return *_root->elem; }
			reference	operator ->() const { return &(*_root->elem); }

			map_iterator	&operator ++()
			{
				if (!_root->parent && _root->RCHILD)
					_root = right_successor(_root);
				else if (_root == _root->parent->LCHILD && !_root->RCHILD)
					_root = _root->parent;
				else if (_root->RCHILD)
					_root = right_successor(_root);
				else
				{
					RBNode<T1,T2> *x = _root;
					while (x->parent && x == x->parent->RCHILD)
						x = x->parent;
					_root = x->parent;
				}
				return *this;
			}
			map_iterator	operator ++(int) { map_iterator tmp = *this; ++(*this); return tmp; }

			map_iterator	&operator --()
			{
				if (!_root->parent && _root->LCHILD)
					_root = left_successor(_root);
				else if (_root == _root->parent->RCHILD && !_root->LCHILD)
					_root = _root->parent;
				else if (_root->LCHILD)
					_root = left_successor(_root);
				else
				{
					RBNode<T1,T2> *x = _root;
					while (x->parent && x == x->parent->LCHILD)
						x = x->parent;
					_root = x->parent;
				}
				return *this;
			}
			map_iterator	operator --(int) { map_iterator tmp = *this; --(*this); return tmp; }

		private:
			RBNode<T1,T2> *_root;
	};
}

#endif
