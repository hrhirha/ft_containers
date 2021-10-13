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
			std::cout << "\n new_elem = " << new_node->elem << " ("
				<< (new_node->col == BLACK ? "BLACK" : "\033[31mRED\033[0m") << ")\n";
			std::cout << "_root = " << _root->elem << " ("
				<< (_root->col == BLACK ? "BLACK" : "\033[31mRED\033[0m") << ")\n";
			RBNode<T> *ins_node = insert_node(_root, new_node);
			if (!ins_node) delete new_node;
			return ins_node;
		}

		RBNode<T> *insert_node(RBNode<T> *node, RBNode<T> *new_node)
		{
			if (new_node->elem < node->elem)
			{
				std::cout << "LEFT: " << node->elem << " ("
					<< (node->col == BLACK ? "BLACK" : "\033[31mRED\033[0m") << ")\n";
				if (!node->LCHILD)
				{
					node->LCHILD = new_node;
					new_node->parent = node;
					std::cout << "/: " << new_node->elem << " ("
						<< (new_node->col == BLACK ? "BLACK" : "\033[31mRED\033[0m") << ")\n";
					rebalance(new_node);
				}
				else
				{
					insert_node(node->LCHILD, new_node);
				}
			}
			else if (new_node->elem > node->elem)
			{
				std::cout << "RIGHT: " << node->elem << " ("
					<< (node->col == BLACK ? "BLACK" : "\033[31mRED\033[0m") << ")\n";
				if (!node->RCHILD)
				{
					node->RCHILD = new_node;
					new_node->parent = node;
					std::cout << "\\: " << new_node->elem << " ("
						<< (new_node->col == BLACK ? "BLACK" : "\033[31mRED\033[0m") << ")\n";
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

			std::cout << "\nErasing " << elem << "\n";
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
					std::cout << "erasing _root " << _root->elem << "\n";
					delete n;
					_root = NULL;
				}
				else if (n->col == RED)
				{
					std::cout << "erasing a red leaf\n";
					if (n == p->LCHILD) p->LCHILD = NULL;
					else p->RCHILD = NULL;
					delete n;
				}
				else
				{
					std::cout << "erasing a block node\n";
					RBNode<T> *sib = n == p->LCHILD ? p->RCHILD : p->LCHILD;
					if (n == p->LCHILD) p->LCHILD = NULL;
					else p->RCHILD = NULL;
					delete n;
					delete_rebalance(sib);
				}
			}
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
				std::cout << "sibling " << sib->elem  << " is black\n";
				if (sib == p->RCHILD && (rneph && rneph->col == RED))
				{
					std::cout << "sib is RCHILD with RED right child" << "\n";
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
					std::cout << "sib is LCHILD with RED left child" << "\n";
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
					std::cout << "sib is RCHILD with RED left child" << "\n";
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
					std::cout << "sib is LCHILD with RED right child" << "\n";
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
					std::cout << "sib has no RED child" << "\n";
					sib->col = RED;
					if (p->col == RED) p->col = BLACK;
					else
					{
						if (p == _root) return ;
						else
						{
							RBNode<T> *gp = p->parent;
							RBNode<T> *s = s == gp->LCHILD ? gp->RCHILD : gp->LCHILD;
							delete_rebalance(s);
						}
					}
				}
			}
			else
			{
				std::cout << "sib is RED" << "\n";
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
					std::cout << "RECOLOR\n";
					n->parent->col = BLACK;
					uncle->col = BLACK;
					if (Gparent->parent) Gparent->col = RED;
					rebalance(Gparent);
					std::cout << "GP: " << Gparent->elem << "\n";
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
			y->parent = x;
			std::cout << "LEFT_ROTATE (" << x->elem << " <-> " << y->elem << ")\n";
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
			y->parent = x;
			std::cout << "RIGHT_ROTATE (" << x->elem << " <-> " << y->elem << ")\n";
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

		/*
		   RBNode<T>	*recolor(RBNode<T> *n)
		   {
		// RECOLR
		if (!n->parent) return NULL;
		else if (!n->parent->parent)
		{
		if (n->parent->col == RED)
		n->parent->col = BLACK;
		return NULL;
		}
		else
		{
		RBNode<T> *Gparent = n->parent->parent;
		RBNode<T> *uncle = n->parent == Gparent->LCHILD ? Gparent->RCHILD : Gparent->LCHILD;
		if (n->parent->col == BLACK) return NULL;
		else if (uncle && uncle->col == RED)
		{
		std::cout << "RECOLOR\n";
		n->parent->col = BLACK;
		uncle->col = BLACK;
		if (Gparent->parent) Gparent->col = RED;
		recolor(Gparent);
		std::cout << "GP: " << Gparent->elem << "\n";
		return Gparent;
		}
		std::cout << "=======\n";
		}
		return n;
		// ENDRECOLOR
		}*/
};

#endif
