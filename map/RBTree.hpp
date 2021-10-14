#ifndef RBTREE_H
# define RBTREE_H
# include <iostream>
# include <algorithm>

# define BLACK 0
# define RED 1

# define LCHILD child[0]
# define RCHILD child[1]

template <class T>
struct RBNode
{
	RBNode	*parent;
	RBNode	*child[2];
	T		elem;
	int		col;
};

template <class T>
class RBTree
{
	public:
		RBTree() : _root(NULL) {}
		RBTree(RBTree const &x) { *this = x; }
		RBTree &operator =(RBTree &x)
		{
			_root = x._root;
			return *this;
		}

		~RBTree() {}

		// insertion

		RBNode<T> *insert(const T &new_elem)
		{
			RBNode<T> *new_node = new RBNode<T>();
			if (!new_node) throw std::bad_alloc();
			new_node->parent = NULL;
			new_node->LCHILD = NULL;
			new_node->RCHILD = NULL;
			new_node->elem = new_elem;
			new_node->col = RED;
			if (!_root)
			{
				_root = new_node;
				_root->col = BLACK;
				return _root;
			}
			RBNode<T> *ins_node = insert_node(_root, new_node);
			if (!ins_node) delete new_node;
			return ins_node;
		}

		RBNode<T> *insert_node(RBNode<T> *node, RBNode<T> *new_node)
		{
			if (new_node->elem < node->elem)
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
			else if (new_node->elem > node->elem)
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

		void	erase(const T &elem)
		{
			RBNode<T> *tmp = _root;

			while (tmp)
			{
				if (elem < tmp->elem)
				{
					tmp = tmp->LCHILD;
				}
				else if (elem > tmp->elem)
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

		void	erase_node(RBNode<T> *n)
		{
			RBNode<T> *p = n->parent;
			if (n->LCHILD)
			{
				RBNode<T> *lmr = left_successor(n);
				std::swap(n->elem, lmr->elem);
				erase_node(lmr);
			}
			else if (n->RCHILD)
			{
				RBNode<T> *rml = right_successor(n);
				std::swap(n->elem, rml->elem);
				erase_node(rml);
			}
			else
			{
				if (n == _root)
				{
					delete n;
					_root = NULL;
				}
				else if (n->col == RED)
				{
					if (n == p->LCHILD) p->LCHILD = NULL;
					else p->RCHILD = NULL;
					delete n;
				}
				else
				{
					RBNode<T> *sib = n == p->LCHILD ? p->RCHILD : p->LCHILD;
					if (n == p->LCHILD) p->LCHILD = NULL;
					else p->RCHILD = NULL;
					delete n;
					delete_rebalance(sib);
				}
			}
		}

		// Get Successor

		RBNode<T> *left_successor(RBNode<T> *n)
		{
			RBNode<T> *tmp = n->LCHILD;
			while (tmp->RCHILD) tmp = tmp->RCHILD;
			return tmp;
		}

		RBNode<T> *right_successor(RBNode<T> *n)
		{
			RBNode<T> *tmp = n->RCHILD;
			while (tmp->LCHILD) tmp = tmp->LCHILD;
			return tmp;
		}

	private:
		RBNode<T>	*_root;

		// Rebalance Tree after Deletion

		void delete_rebalance(RBNode<T> *sib)
		{
			RBNode<T> *p = sib->parent;
			RBNode<T> *lneph = sib->LCHILD;
			RBNode<T> *rneph = sib->RCHILD;
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
							RBNode<T> *gp = p->parent;
							RBNode<T> *s = p == gp->LCHILD ? gp->RCHILD : gp->LCHILD;
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

		void	rebalance(RBNode<T> *n)
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
				RBNode<T> *Gparent = n->parent->parent;
				RBNode<T> *uncle = n->parent == Gparent->LCHILD ? Gparent->RCHILD : Gparent->LCHILD;
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

		// Rotate

		void	left_rotate(RBNode<T> *x, RBNode<T> *y)
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

		void	right_rotate(RBNode<T> *x, RBNode<T> *y)
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
};

#endif
