/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:44:37 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/10 19:44:27 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include <functional>
#include <memory>
#include <iostream>

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

	template <class T, class Comp, class Compare, class Alloc = std::allocator<T> >
	class	binary_tree
	{
		public:
			typedef T																value_type;
			typedef typename Alloc::template rebind<ft::node<value_type> >::other	allocator_type;
			typedef typename ft::node<value_type>*									node_pointer;
			typedef Comp															compare;

		public:
			node<T>			*_root;
			allocator_type	_allocator;
			compare			_compare;

		public:
			binary_tree(void) : _root(NULL), _compare(Compare()) {}

			binary_tree(const compare &comp) : _root(NULL), _compare(comp) {}			
			
			binary_tree(const T &val, const compare &comp = compare()) : _compare(comp)
			{
				this->_root = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root, val);
				this->_root->color = BLACK;
			}
			
			binary_tree(ft::node<T> node, const compare &comp = compare()) :  _root(node), _compare(comp) {}
			
			virtual ~binary_tree(void) {}

			binary_tree	&operator=(const binary_tree &x)
			{
				this->_root = x._root;
				this->_allocator = x._allocator;
				return *this;
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
					if (_compare(par->value, val))
						aux = aux->rhs;
					else
						aux = aux->lhs;
				}
				if (_compare(par->value, val))
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
					node = NULL;
				}
				else if ((node->lhs == NULL && node->rhs != NULL) || (node->rhs == NULL && node->lhs != NULL))
				{
					node->rhs ? x = node->rhs : x = node->lhs;
					node == p->rhs ? p->rhs = x : p->lhs = x;
					x->parent = p;
					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
					node = NULL;
					return ;
				}
				else
				{
					x = maximum(node->lhs);
					check_color = x->color;
					// node->swap(*x);
					transplant(node, x);
					p = x->parent;
					s = x->sibling();
					node = x;
					if (node->lhs)
					{
						p->rhs = node->lhs;
						check_color = RED;
					}
					else
						node->parent->lhs == node ? node->parent->lhs = NULL : node->parent->rhs = NULL;
					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
					node = NULL;
				}
				if (!node)
				{
					ft::node<T>	*aux;
					aux = this->_allocator.allocate(1);
					aux->color = BLACK;
					node = aux;
				}
				if (check_color == BLACK)
					deleteFix(node, p, s);
			}

			void	deleteFix(ft::node<T> *n, ft::node<T> *p, ft::node<T> *s)
			{
				ft::node<T>	*c;
				ft::node<T>	*d;
				
				s == p->lhs ? c = s->rhs : c = s->lhs;
				s == p->lhs ? d = s->lhs : d = s->rhs;

				// std::cout << "Parent: " << p->value << " " << "color: " << p->color << std::endl;
				// std::cout << "Sibling: " << s->value << " " << "color: " << s->color << std::endl;
				// if (c) { std::cout << "Closest: " << c->value << " " << "color: " << c->color << std::endl;}
				// if (d) { std::cout << "Farthest: " << d->value << " " << "color: " << d->color << std::endl;}
				
				while (p != NULL && n->color == BLACK)
				{
					if (s && s->color == RED)
					{
						n == p->lhs ? leftRotate(p) : rightRotate(p);
						p->color = RED;
						s->color = BLACK;
						s = c;
					}
					else if (p->color == BLACK && (s && s->color == BLACK)
						&& (!c || c->color == BLACK) && (!d || d->color == BLACK))
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
					if ((c && c->color == RED) && (!s || s->color == BLACK)
						&& (!d || d->color == BLACK))
					{
						s == p->rhs ? rightRotate(s) : leftRotate(s);
						s->color = RED;
						c->color = BLACK;
						d = s;
						s = c;
					}
					if ((d && d->color == RED) && (!s || s->color == BLACK))
					{
						s == p->rhs ? leftRotate(p) : rightRotate(p);
						s->color = p->color;
						p->color = BLACK;
						d->color = BLACK;
						return ;
					}
				}
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

			ft::node<T>	*find(const T val) const
			{
				ft::node<T>	*node = this->_root;
	
				while (node != NULL)
				{
					if (_compare(val, node->value))
						node = node->lhs;
					else if (_compare(node->value, val))
						node = node->rhs;
					else
						return node;
				}
				return NULL;
			}

			ft::node<T>	*begin(void) const
			{
				ft::node<T>	*aux = this->_root;

				if (!aux)
					return this->_root;
				while (aux->lhs)
					aux = aux->lhs;
				return aux;
			}

			ft::node<T>	*end(void) const
			{
				ft::node<T>	*aux = this->_root;

				if (!aux)
					return this->_root;
				while (aux->rhs)
					aux = aux->rhs;
				return aux->rhs;
			}

			ft::node<T>	*rbegin(void) const
			{
				ft::node<T>	*aux = this->_root;

				if (!aux)
					return this->_root;
				while (aux->rhs)
					aux = aux->rhs;
				return aux;
			}

			ft::node<T>	*rend(void) const
			{
				ft::node<T>	*aux = this->_root;

				if (!aux)
					return this->_root;
				while (aux->lhs)
					aux = aux->lhs;
				return aux->lhs;
			}
	};
	
	template <typename T>
	ft::node<T>	*minimum(ft::node<T> *node)
	{
		ft::node<T>	*aux = node;

		while (aux->lhs != NULL)
			aux = aux->lhs;
		return aux;
	}

	template <typename T>
	ft::node<T>	*maximum(ft::node<T> *node)
	{
		ft::node<T>	*aux = node;

		while (aux->rhs != NULL)
			aux = aux->rhs;
		return aux;
	}

	template <typename T>
	ft::node<T>	*inorder_next(ft::node<T> *n)
	{
		ft::node<T>	*p = n->parent;

		if (n->rhs)
			return minimum(n->rhs);
		else
		{
			if (n == p->lhs)
				return p;
			else
			{
				while (p && n == p->rhs)
				{
					n = p;
					p = n->parent;
				}
				return n->parent;
			}
		}
	}

	template <typename T>
	ft::node<T>	*inorder_prev(ft::node<T> *n)
	{
		ft::node<T>	*p = n->parent;

		if (n->lhs)
			return maximum(n->lhs);
		else
		{
			if (n == p->rhs)
				return p;
			else
			{
				while (n == p->lhs)
				{
					n = p;
					p = n->parent;
				}
				return n->parent;
			}
		}
	}
}
