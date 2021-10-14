#ifndef RBTREE_H
# define RBTREE_H
# include <iostream>
# include <algorithm>
# include "../tools/Utility.hpp"

# define BLACK 0
# define RED 1

# define LCHILD child[0]
# define RCHILD child[1]

template <class T1, class T2>
struct RBNode
{
	RBNode					*parent;
	RBNode					*child[2];
	ft::pair<const T1, T2>	*elem;
	int						col;
};

template <class T1, class T2, class Compare = std::less<T1>,
		 class Alloc = std::allocator<ft::pair<const T1, T2> > >
		 class RBTree
{
	public:
		RBTree() : _root(NULL) {}
		RBTree(RBTree const &x) { *this = x; }
		RBTree &operator =(RBTree &x)
		{
			_root = x._root;
			_alloc_elem = x._alloc_elem;
			_comp = x._comp;
			return *this;
		}

		~RBTree() {}

		RBNode<T1, T2> *getRoot() const { return _root; }

		// insertion

		RBNode<T1, T2> *insert(const ft::pair<const T1, T2> &new_elem)
		{
			RBNode<T1, T2> *new_node = _alloc.allocate(1);
			if (!new_node) throw std::bad_alloc();
			new_node->parent = NULL;
			new_node->LCHILD = NULL;
			new_node->RCHILD = NULL;
			new_node->elem = _alloc_elem.allocate(1);
			_alloc_elem.construct(new_node->elem, new_elem);
			new_node->col = RED;
			if (!_root)
			{
				_root = new_node;
				_root->col = BLACK;
				return _root;
			}
			RBNode<T1, T2> *ins_node = insert_node(_root, new_node);
			if (!ins_node)
			{
				_alloc_elem.deallocate(new_node->elem, 1);
				_alloc.deallocate(new_node, 1);
			}
			return ins_node;
		}

		RBNode<T1, T2> *insert_node(RBNode<T1, T2> *node, RBNode<T1, T2> *new_node)
		{
			if (_comp(new_node->elem->first, node->elem->first))
			{
				if (!node->LCHILD)
				{
					node->LCHILD = new_node;
					new_node->parent = node;
					rebalance(new_node);
				}
				else
				{
					insert_node(node->LCHILD, new_node);
				}
			}
			else if (!_comp(new_node->elem->first, node->elem->first))
			{
				if (!node->RCHILD)
				{
					node->RCHILD = new_node;
					new_node->parent = node;
					rebalance(new_node);
				}
				else
				{
					insert_node(node->RCHILD, new_node);
				}
			}
			else
				return NULL;
			return new_node;
		}

		// Deletion

		void	erase(const T2 &elem)
		{
			RBNode<T1, T2> *tmp = _root;

			while (tmp)
			{
				if (_comp(elem, tmp->elem->first))
				{
					tmp = tmp->LCHILD;
				}
				else if (!_comp(elem, tmp->elem->first))
				{
					tmp = tmp->RCHILD;
				}
				else
				{
					erase_node(tmp);
					break ;
				}
			}
		}

		void	erase_node(RBNode<T1, T2> *n)
		{
			RBNode<T1, T2> *p = n->parent;
			if (n->LCHILD)
			{
				RBNode<T1, T2> *lmr = left_successor(n);
				std::swap(n->elem->first, lmr->elem->first);
				std::swap(n->elem->second, lmr->elem->second);
				erase_node(lmr);
			}
			else if (n->RCHILD)
			{
				RBNode<T1, T2> *rml = right_successor(n);
				std::swap(n->elem->first, rml->elem->first);
				std::swap(n->elem->second, rml->elem->second);
				erase_node(rml);
			}
			else
			{
				if (n == _root)
				{
					_alloc.deallocate(n, 1);
					_root = NULL;
				}
				else if (n->col == RED)
				{
					if (n == p->LCHILD) p->LCHILD = NULL;
					else p->RCHILD = NULL;
					_alloc.deallocate(n, 1);
				}
				else
				{
					RBNode<T1, T2> *sib = n == p->LCHILD ? p->RCHILD : p->LCHILD;
					if (n == p->LCHILD) p->LCHILD = NULL;
					else p->RCHILD = NULL;
					_alloc.deallocate(n, 1);
					delete_rebalance(sib);
				}
			}
		}

	private:
		RBNode<T1, T2>					*_root;
		std::allocator<RBNode<T1, T2> >	_alloc;
		Alloc							_alloc_elem;
		Compare							_comp;

		// Rebalance Tree after Deletion

		void delete_rebalance(RBNode<T1, T2> *sib)
		{
			RBNode<T1, T2> *p = sib->parent;
			RBNode<T1, T2> *lneph = sib->LCHILD;
			RBNode<T1, T2> *rneph = sib->RCHILD;
			if (sib->col == BLACK)
			{
				if (sib == p->RCHILD && (rneph && rneph->col == RED))
				{
					left_rotate(sib, p);
					if (_root == p) _root = sib;
					if (p->col == RED)
					{
						p->col = BLACK;
						rneph->col = BLACK;
						sib->col = RED;
					}
					else
						rneph->col = BLACK;
				}
				else if (sib == p->LCHILD && (lneph && lneph->col == RED))
				{
					right_rotate(sib, p);
					if (_root == p) _root = sib;
					if (p->col == RED)
					{
						p->col = BLACK;
						lneph->col = BLACK;
						sib->col = RED;
					}
					else
						lneph->col = BLACK;
				}
				else if (sib == p->RCHILD && (lneph && lneph->col == RED))
				{
					right_rotate(lneph, sib);
					if (_root == p) _root = lneph;
					left_rotate(lneph, p);
					if (p->col == RED)
					{
						p->col = BLACK;
						lneph->col = BLACK;
						sib->col = RED;
					}
					else
						lneph->col = BLACK;
				}
				else if (sib == p->LCHILD && (rneph && rneph->col == RED))
				{
					left_rotate(rneph, sib);
					if (_root == p) _root = rneph;
					right_rotate(rneph, p);
					if (p->col == RED)
					{
						p->col = BLACK;
						rneph->col = BLACK;
						sib->col = RED;
					}
					else
						rneph->col = BLACK;
				}
				else
				{
					sib->col = RED;
					if (p->col == RED) p->col = BLACK;
					else
					{
						if (p == _root) return ;
						else
						{
							RBNode<T1, T2> *gp = p->parent;
							RBNode<T1, T2> *s = p == gp->LCHILD ? gp->RCHILD : gp->LCHILD;
							delete_rebalance(s);
						}
					}
				}
			}
			else
			{
				if (sib == p->LCHILD)
				{
					right_rotate(sib, p);
					if (_root == p) _root = sib;
					std::swap(sib->col, p->col);
					delete_rebalance(p->LCHILD);
				}
				else
				{
					left_rotate(sib, p);
					if (_root == p) _root = sib;
					std::swap(sib->col, p->col);
					delete_rebalance(p->RCHILD);
				}
			}
		}

		// Rebalance Tree after Insertion

		void	rebalance(RBNode<T1, T2> *n)
		{
			if (!n->parent) return ;
			else if (!n->parent->parent)
			{
				if (n->parent->col == RED)
					n->parent->col = BLACK;
				return ;
			}
			else
			{
				RBNode<T1, T2> *Gparent = n->parent->parent;
				RBNode<T1, T2> *uncle = n->parent == Gparent->LCHILD ? Gparent->RCHILD : Gparent->LCHILD;
				if (n->parent->col == BLACK) return ;
				else if (uncle && uncle->col == RED)
				{
					n->parent->col = BLACK;
					uncle->col = BLACK;
					if (Gparent->parent) Gparent->col = RED;
					rebalance(Gparent);
				}
				else if (uncle == Gparent->RCHILD)
				{
					if (n == n->parent->LCHILD)
					{
						std::swap(n->parent->col, Gparent->col);
						right_rotate(n->parent, Gparent);
						if (_root == Gparent) _root = n->parent;
					}
					else
					{
						left_rotate(n, n->parent);
						std::swap(n->col, n->parent->col);
						if (_root == n->parent) _root = n;
						right_rotate(n, n->parent);
					}
				}
				else
				{
					if (n == n->parent->RCHILD)
					{
						std::swap(n->parent->col, Gparent->col);
						left_rotate(n->parent, Gparent);
						if (_root == Gparent) _root = n->parent;
					}
					else
					{
						right_rotate(n, n->parent);
						if (_root == n->parent) _root = n;
						std::swap(n->col, n->parent->col);
						left_rotate(n, n->parent);
					}
				}
			}
		}
};

// Get Successor

template <class T1, class T2>
RBNode<T1, T2> *left_successor(RBNode<T1, T2> *n)
{
	RBNode<T1, T2> *tmp = n->LCHILD;
	while (tmp->RCHILD) tmp = tmp->RCHILD;
	return tmp;
}

template <class T1, class T2>
RBNode<T1, T2> *right_successor(RBNode<T1, T2> *n)
{
	RBNode<T1, T2> *tmp = n->RCHILD;
	while (tmp->LCHILD) tmp = tmp->LCHILD;
	return tmp;
}

// Rotate

template <class T1, class T2>
void	left_rotate(RBNode<T1, T2> *x, RBNode<T1, T2> *y)
{
	x->parent = y->parent;
	if (x->parent)
	{
		if (y == y->parent->LCHILD) y->parent->LCHILD = x;
		else y->parent->RCHILD = x;
	}
	y->RCHILD = x->LCHILD;
	x->LCHILD = y;
	if (y->RCHILD) y->RCHILD->parent = y;
	y->parent = x;
}

template <class T1, class T2>
void	right_rotate(RBNode<T1, T2> *x, RBNode<T1, T2> *y)
{
	x->parent = y->parent;
	if (x->parent)
	{
		if (y == y->parent->LCHILD) y->parent->LCHILD = x;
		else y->parent->RCHILD = x;
	}
	y->LCHILD = x->RCHILD;
	x->RCHILD = y;
	if (y->LCHILD) y->LCHILD->parent = y;
	y->parent = x;
}

#endif
