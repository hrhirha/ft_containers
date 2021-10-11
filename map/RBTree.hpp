#ifndef RBTREE_H
# define RBTREE_H
# include <iostream>

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
	private:
		RBNode<T>	*_root;

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
			std::cout << "_root = " << _root->elem << " " << _root->col << '\n';
			RBNode<T> *ins_node = insert_node(_root, new_node);
			if (!ins_node) delete new_node;
			return ins_node;
		}

		RBNode<T> *insert_node(RBNode<T> *node, RBNode<T> *new_node)
		{
			if (new_node->elem < node->elem)
			{
				std::cout << "LEFT\n";
				std::cout << "new_elem = " << new_node->elem << '\n';
				std::cout << "old_elem = " << node->elem << " " << node->col << "\n\n";
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
				std::cout << "RIGHT\n";
				std::cout << "new_elem = " << new_node->elem << '\n';
				std::cout << "old_elem = " << node->elem << " " << node->col << "\n\n";
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

		// Rebalance

		void	rebalance(RBNode<T> *n)
		{
			n = recolor(n);
			if (!n || !n->parent || n->parent->col == BLACK) return ;
			RBNode<T> *Gparent = n->parent->parent;
			RBNode<T> *uncle = n->parent == Gparent->LCHILD ? Gparent->RCHILD : Gparent->LCHILD;
			if (uncle == Gparent->RCHILD)
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
					right_rotate(n, n->parent);
					if (_root == n->parent) _root = n;
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
					std::swap(n->col, n->parent->col);
					left_rotate(n, n->parent);
					if (_root == n->parent) _root = n;
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
		}

		// Recolor

		RBNode<T>	*recolor(RBNode<T> *n)
		{
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
					n->parent->col = BLACK;
					uncle->col = BLACK;
					if (Gparent->parent) Gparent->col = RED;
					recolor(Gparent);
					return Gparent;
				}
			}
			return n;
		}
};

#endif
