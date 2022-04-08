/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:44:37 by rcabezas          #+#    #+#             */
/*   Updated: 2022/04/08 18:01:21 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include <functional>

namespace	ft
{
	enum	node_color
	{
		BLACK,
		RED
	};

	template <class T>
	struct	node
	{
		T			value;
		struct node	*parent;
		struct node	*lhs;
		struct node	*rhs;
		node_color	color;

		node(void) : parent(NULL), lhs(NULL), rhs(NULL), color(RED) {}
		node(const T value) : value(value), parent(NULL), lhs(NULL), rhs(NULL), color(RED) {}
		node	&operator=(const node &op)
		{
			this->value = op.value;
			return *this;
		}

		node	*uncle(void) { return this->parent->parent->lhs == this->parent ? this->parent->parent->rhs : this->parent->parent->lhs; }
		
		node	*sibling(void)
		{
			if (this->parent)
				return this->parent->rhs == this ? this->parent->lhs : this->parent->rhs;
			return NULL;
		}
		
		node	*closest_nephew(void)
		{
			if (this->sibling())
				return this == this->parent->lhs ? this->sibling()->lhs : this->sibling()->rhs;
			return NULL;
		}

		node	*farthest_nephew(void)
		{
			if (this->sibling())
				return this == this->parent->lhs ? this->sibling()->rhs : this->sibling()->lhs;
			return NULL;
		}

		void	swap(ft::node<T> &b)
		{
			T	aux = b.value;

			b.value = this->value;
			this->value = aux;
		}
	};

	template <class T, class Comp, class Alloc = std::allocator<T> >
	class	binary_tree
	{
		public:
			typedef typename Alloc::template rebind<ft::node<T> >::other	allocator_type;

		public:
			node<T>			*_root;
			allocator_type	_allocator;

		public:
			binary_tree(const allocator_type &alloc = allocator_type()) : _root(NULL), _allocator(alloc) {}
			binary_tree(const T &val, const allocator_type &alloc = allocator_type()) : _allocator(alloc)
			{
				this->_root = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root, val);
				this->_root->color = BLACK;
			}
			binary_tree(ft::node<T> node, const allocator_type &alloc = allocator_type()) :  _root(node), _allocator(alloc) {}
			virtual ~binary_tree(void) {}

			binary_tree	&operator=(const binary_tree &x)
			{
				this->_root = x._root;
				this->_allocator = x._allocator;
			}

			void	insert_node(const T &val)
			{
				ft::node<T>	*par;
				ft::node<T> *aux = this->_root;
				ft::node<T>	*inserted = this->_allocator.allocate(1);
				
				this->_allocator.construct(inserted, ft::node<T>(val));
				if (!this->_root)
				{
					this->_root = inserted;
					this->_root->color = BLACK;
					return ;
				}
				while (aux != NULL)
				{
					par = aux;
					if (val >= aux->value)
						aux = aux->rhs;
					else
						aux = aux->lhs;
				}
				if (val >= par->value)
					par->rhs = inserted;
				else
					par->lhs = inserted;
				inserted->parent = par;
				this->insertFix(inserted);
			}

			void	insertFix(ft::node<T> *k)
			{
				ft::node<T>	*u;
				while (k->parent->color == RED)
				{
					if (k->parent == k->parent->parent->rhs)
					{
						u = k->uncle();
						if (u && u->color == RED)
						{
							this->recolor(k);
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->lhs)
							{
								k = k->parent;
								rightRotate(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							leftRotate(k->parent->parent);
						}
					}
					else
					{
						u = k->uncle();

						if (u && u->color == RED)
						{
							this->recolor(k);
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->rhs)
							{
								k = k->parent;
								leftRotate(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							rightRotate(k->parent->parent);
						}
					}
					if (k == this->_root)
						break;
				}
				this->_root->color = BLACK;
			}

			void	recolor(ft::node<T> *node)
			{
				node->uncle()->color = BLACK;
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
			}

			void	rightRotate(ft::node<T> *node)
			{
				ft::node<T> *y = node->lhs;
	
				node->lhs = y->rhs;
				if (y->rhs != NULL)
					y->rhs->parent = node;
				y->parent = node->parent;
				if (node->parent == NULL)
					this->_root = y;
				else if (node == node->parent->rhs)
					node->parent->rhs = y;
				else
					node->parent->lhs = y;
				y->rhs = node;
				node->parent = y;
			}

			void	leftRotate(ft::node<T> *node)
			{
				ft::node<T> *y = node->rhs;

				node->rhs = y->lhs;
				if (y->lhs != NULL)
					y->lhs->parent = node;
				y->parent = node->parent;
				if (node->parent == NULL)
					this->_root = y;
				else if (node == node->parent->lhs)
					node->parent->lhs = y;
				else
					node->parent->rhs = y;
				y->lhs = node;
				node->parent = y;
			}
			
			void	delete_val(const T &val)
			{
				ft::node<T>	*node = find(val);
				delete_node(node);
			}

			void	delete_node(ft::node<T>	*node)
			{
				ft::node<T>	*p = node->parent;
				ft::node<T>	*s = node->sibling();
				ft::node<T>	*x = node;
				node_color	check_color = node->color;

				if (node->lhs == NULL && node->rhs == NULL)
				{
					p->rhs == node ? p->rhs = NULL : p->lhs = NULL;
					check_color = node->color;
					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
				}
				else if ((node->lhs == NULL && node->rhs != NULL) || (node->rhs == NULL && node->lhs != NULL))
				{
					node->rhs ? x = node->rhs : x = node->lhs;
					node == p->rhs ? p->rhs = x : p->lhs = x;
					x->parent = p;
					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
					return ;
				}
				else
				{
					x = maximum(node->lhs);
					check_color = x->color;
					node->swap(*x);
					x->parent->rhs == x ? x->parent->rhs = NULL : x->parent->lhs = NULL;
				}
				if (check_color == BLACK)
					deleteFix(node, p, s);
			}

			void	deleteFix(ft::node<T> *n, ft::node<T> *p, ft::node<T> *s)
			{
				ft::node<T>	*c;
				ft::node<T>	*d;
				
				s == p->lhs ? c = p->rhs : c = p->lhs;
				s == p->lhs ? d = p->lhs : d = p->rhs;
				while (p != NULL && n->color != BLACK)
				{
					if (s && s->color == RED)
					{
						n == p->lhs ? leftRotate(p) : rightRotate(p);
						p->color = RED;
						s->color = BLACK;
						s = c;
					}
					else if (p->color == BLACK && (s && s->color == BLACK)
						&& (!c || c->color == BLACK) && (!d || d->color))
					{
						s->color = RED;
						n = p;
						p = n->parent;
						s = n->sibling();
						c = n->closest_nephew();
						d = n->farthest_nephew();
					}
					else if (p->color == RED && (!c || c->color == BLACK)
						&& (!d || d->color == BLACK))
					{
						s->color = RED;
						p->color = BLACK;
						return ;
					}
					if ((c && c->color == RED) && (s && s->color == BLACK)
						&& (!d || d->color == BLACK))
					{
						n == p->lhs ? rightRotate(s) : leftRotate(s);
						s->color = RED;
						c->color = BLACK;
						d = s;
						s = c;
					}
					if ((d && d->color == RED) && (!s || s->color == BLACK))
					{
						n == p->lhs ? leftRotate(p) : rightRotate(p);
						s->color = p->color;
						p->color = BLACK;
						d->color = BLACK;
						return ;
					}
				}
			}

			ft::node<T>	*minimum(ft::node<T> *node)
			{
				ft::node<T>	*aux = node;

				while (aux->lhs != NULL)
					aux = aux->lhs;
				return aux;
			}

			ft::node<T>	*maximum(ft::node<T> *node)
			{
				ft::node<T>	*aux = node;

				while (aux->rhs != NULL)
					aux = aux->rhs;
				return aux;
			}

			void	transplant(ft::node<T> *u, ft::node<T> *v)
			{
				if (u->parent == NULL)
					this->_root = v;
				else if (u == u->parent->lhs)
					u->parent->lhs = v;
				else
					u->parent->rhs = v;
				v->parent = u->parent;
			}

			ft::node<T>	*find(const T val)
			{
				ft::node<T>	*node = this->_root;
	
				while (node != NULL)
				{
					if (node->value == val)
					{
						return node;
					}
					else if (node->value < val)
						node = node->rhs;
					else
						node = node->lhs;
				}
				std::cout << "Node not found" << std::endl;
				// throw NodeNotFoud();
				return NULL;
			}

			class	NodeNotFoud : public std::exception
			{
				virtual const char * what() const throw()
				{
					return "The node wasn't found";
				}
			};
	};
}
