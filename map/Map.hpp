#ifndef MAP_HPP
# define MAP_HPP
# include "RBTree.hpp"
# include "map_iterator.hpp"
# include "../tools/Reverse_Iterator.hpp"

namespace ft
{
	template <class Key,
			 class T,
			 class Compare = std::less<Key>,
			 class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			// value_compare
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename ft::map_iterator<key_type,mapped_type>			iterator;
			typedef typename ft::map_iterator<key_type,mapped_type>			const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::Iterator_traits<iterator>::difference_type difference_type;
			typedef size_t													size_type;

			// Constructor

			explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) :
				_tree(), _alloc(alloc), _size(0), _comp(comp) { _root = _tree.getRoot(); }

			template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp)
			{
				for (InputIterator it = first; it != last; it++)
				{
					_tree.insert(*it);
					_size++;
				}
				_root = _tree.getRoot();
			}

			map (const map& x) : _tree(x._tree), _alloc(x._alloc), _size(x._size), _comp(x._comp) {}
			map	&operator =(const map& x)
			{
				_tree = x._tree; _size = x._size; _root = _tree.getRoot();
			}

			// Destructor

			~map() {}

			// Iterators

			iterator begin()
			{
				_root = _tree.getRoot();
				node *tmp = _root;
				if (!_root) return iterator();
				if (!_root->LCHILD) return iterator(_root);
				while (tmp->LCHILD) tmp = tmp->LCHILD;
				return iterator(tmp);
			}
			const_iterator begin() const
			{
				_root = _tree.getRoot();
				node *tmp = _root;
				if (!_root) return iterator();
				if (!_root->LCHILD) return iterator(_root);
				while (tmp->LCHILD) tmp = tmp->LCHILD;
				return iterator(tmp);
			}
			iterator end()
			{
				_root = _tree.getRoot();
				node *tmp = _root;
				if (!_root) return iterator();
				if (!_root->RCHILD) return iterator(_root);
				while (tmp->RCHILD) tmp = tmp->RCHILD;
				return iterator(tmp->RCHILD);
			}
			const_iterator end() const
			{
				_root = _tree.getRoot();
				node *tmp = _root;
				if (!_root) return iterator();
				if (!_root->RCHILD) return iterator(_root);
				while (tmp->RCHILD) tmp = tmp->RCHILD;
				return iterator(tmp->RCHILD);
			}

		public:
			typedef RBTree<key_type, mapped_type, key_compare, allocator_type>	rbtree;
			typedef RBNode<key_type, mapped_type>								node;
			rbtree			_tree;
			node			*_root;
			allocator_type	_alloc;
			size_type		_size;
			key_compare		_comp;
	};
}

#endif
