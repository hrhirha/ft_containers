/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:03:16 by hrhirha           #+#    #+#             */
/*   Updated: 2021/10/30 18:32:10 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_H
# define RBTREE_H
# include <iostream>
# include <algorithm>
# include "../tools/Utility.hpp"

# define BLACK 0
# define RED 1

# define LCHILD child[0]
# define RCHILD child[1]

namespace ft
{

	template <class T>
		struct RBNode
		{
			RBNode	*parent;
			RBNode	*child[2];
			T		*elem;
			int		col;
		};

	template <class K, class T, class Compare, class Alloc >
		class RBTree
		{
			public:
				RBTree() : _root(NULL) { _end = _alloc.allocate(1); }
				RBTree(RBTree const &x) { *this = x; }
				RBTree &operator =(const RBTree &x)
				{
					_root = x._root;
					_end = x._end;
					_alloc_elem = x._alloc_elem;
					_comp = x._comp;
					return *this;
				}

				~RBTree() { _alloc.deallocate(_end, 1); }

				RBNode<T> *getRoot() const { return _root; }
				RBNode<T> *getEnd() const { return _end; }
				RBNode<T> *right_most() const
				{
					RBNode<T> *tmp = _root;
					if (!tmp) return _end;
					while (tmp->RCHILD) tmp = tmp->RCHILD;
					return tmp;
				}
				RBNode<T> *left_most() const
				{
					RBNode<T> *tmp = _root;
					if (!tmp) return _end;
					while (tmp->LCHILD) tmp = tmp->LCHILD;
					return tmp;
				}

				RBNode<T> *find(const K &elem) const
				{
					RBNode<T> *tmp = _root;

					while (tmp)
					{
						if (!_comp(elem, tmp->elem->first) && !_comp(tmp->elem->first, elem))
							return tmp;
						else if (_comp(elem, tmp->elem->first))
							tmp = tmp->LCHILD;
						else
							tmp = tmp->RCHILD;
					}
					return NULL;
				}

				RBNode<T> *lower_bound (const K &k, RBNode<T> *n) const
				{
					RBNode<T> *ret = NULL;
					if (!n) return NULL;
					if (_comp(right_most()->elem->first, k))
						return _end;
					if (_comp(k, n->elem->first))
					{
						ret = lower_bound(k, n->LCHILD);
						if (!ret) ret = n;
					}
					else if (_comp(n->elem->first, k))
					{
						if (!n->RCHILD)
						{
							while (_comp(n->elem->first, k))
								n = n->parent;
							return n;
						}
						ret = lower_bound(k, n->RCHILD);
					}
					else
						ret = n;
					return ret;
				}

				RBNode<T> *upper_bound (const K &k, RBNode<T> *n) const
				{
					RBNode<T> *ret = NULL;
					if (!n) return NULL;
					if (!_comp(k, right_most()->elem->first))
						return _end;
					if (_comp(k, n->elem->first))
					{
						ret = upper_bound(k, n->LCHILD);
						if (!ret) ret = n;
					}
					else
					{
						if (!n->RCHILD)
						{
							while (!_comp(k, n->elem->first))
								n = n->parent;
							return n;
						}
						ret = upper_bound(k, n->RCHILD);
					}
					return ret;
				}

				// insertion

				ft::pair<RBNode<T>*, bool>	insert(const T &new_elem)
				{
					RBNode<T> *new_node = _alloc.allocate(1);
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
						return ft::make_pair(_root, true);
					}
					RBNode<T> *ins_node = insert_node(_root, new_node);
					if (ins_node != new_node)
					{
						_alloc_elem.destroy(new_node->elem);
						_alloc_elem.deallocate(new_node->elem, 1);
						_alloc.deallocate(new_node, 1);
						return ft::make_pair(ins_node, false);
					}
					return ft::make_pair(ins_node, true);
				}

				RBNode<T> *insert_node(RBNode<T> *node, RBNode<T> *new_node)
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
							new_node = insert_node(node->LCHILD, new_node);
					}
					else if (_comp(node->elem->first, new_node->elem->first))
					{
						if (!node->RCHILD)
						{
							node->RCHILD = new_node;
							new_node->parent = node;
							rebalance(new_node);
						}
						else
							new_node = insert_node(node->RCHILD, new_node);
					}
					else
						return node;
					return new_node;
				}

				// Deletion

				size_t	erase(const K &elem)
				{
					RBNode<T> *tmp = _root;

					while (tmp)
					{
						if (!_comp(elem, tmp->elem->first) && !_comp(tmp->elem->first, elem))
						{
							erase_node(tmp);
							return 1;
						}
						if (_comp(elem, tmp->elem->first))
						{
							tmp = tmp->LCHILD;
						}
						else
						{
							tmp = tmp->RCHILD;
						}
					}
					return 0;
				}

				size_t	erase_node(RBNode<T> *n)
				{
					size_t ret = 0;
					RBNode<T> *p = n->parent;
					if (n->LCHILD)
					{
						RBNode<T> *lmr = left_successor(n);
						_alloc_elem.destroy(n->elem);
						_alloc_elem.construct(n->elem, *lmr->elem);
						ret = erase_node(lmr);
					}
					else if (n->RCHILD)
					{
						RBNode<T> *rml = right_successor(n);
						_alloc_elem.destroy(n->elem);
						_alloc_elem.construct(n->elem, *rml->elem);
						ret = erase_node(rml);
					}
					else
					{
						if (n == _root)
						{
							_alloc_elem.destroy(n->elem);
							_alloc_elem.deallocate(n->elem, 1);
							_alloc.deallocate(n, 1);
							_root = NULL;
						}
						else if (n->col == RED)
						{
							if (n == p->LCHILD) p->LCHILD = NULL;
							else p->RCHILD = NULL;
							_alloc_elem.destroy(n->elem);
							_alloc_elem.deallocate(n->elem, 1);
							_alloc.deallocate(n, 1);
						}
						else
						{
							RBNode<T> *sib = n == p->LCHILD ? p->RCHILD : p->LCHILD;
							if (n == p->LCHILD) p->LCHILD = NULL;
							else p->RCHILD = NULL;
							_alloc_elem.destroy(n->elem);
							_alloc_elem.deallocate(n->elem, 1);
							_alloc.deallocate(n, 1);
							delete_rebalance(sib);
						}
						return 1;
					}
					return ret;
				}

			private:
				RBNode<T>											*_root;
				RBNode<T>											*_end;
				typename Alloc::template rebind<RBNode<T> >::other	_alloc;
				Alloc												_alloc_elem;
				Compare												_comp;

				// Rebalance Tree after Deletion

				void delete_rebalance(RBNode<T> *sib)
				{
					if (!sib) return;
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
		};

	// Get Successor

	template <class T>
		RBNode<T> *left_successor(RBNode<T> *n)
		{
			RBNode<T> *tmp = n->LCHILD;
			while (tmp->RCHILD) tmp = tmp->RCHILD;
			return tmp;
		}

	template <class T>
		RBNode<T> *right_successor(RBNode<T> *n)
		{
			RBNode<T> *tmp = n->RCHILD;
			while (tmp->LCHILD) tmp = tmp->LCHILD;
			return tmp;
		}

	// Rotate

	template <class T>
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

	template <class T>
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
}

#endif
