/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:44:37 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/17 17:29:57 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
		T				value;
		struct node		*parent;
		struct node		*lhs;
		struct node		*rhs;
		node_color		color;

		node(void) : parent(NULL), lhs(NULL), rhs(NULL), color(RED) {}
		node(const T value) : value(value), parent(NULL), lhs(NULL), rhs(NULL), color(RED) {}
		node	&operator=(const node &op)
		{
			this->value = op.value;
			return *this;
		}

		node	*uncle(void) { return this->parent->parent->lhs == this->parent ? this->parent->parent->rhs : this->parent->parent->lhs; }
		
		node	*sibling(void) { return this->parent->rhs == this ? this->parent->lhs : this->parent->rhs; }
		
		node	*closest_nephew(void) { return this == this->parent->lhs ? this->sibling()->lhs : this->sibling()->rhs; }

		node	*farthest_nephew(void) { return this == this->parent->lhs ? this->sibling()->rhs : this->sibling()->lhs; }

		void	swap(ft::node<T> &b)
		{
			T	aux = b.value;

			b.value = this->value;
			this->value = aux;
		}
	};

	template <class T, class Compare, class Alloc = std::allocator<T> >
	class	binary_tree
	{
		public:
			typedef T																value_type;
			typedef typename Alloc::template rebind<ft::node<value_type> >::other	allocator_type;
			typedef typename ft::node<value_type>*									node_pointer;
			typedef Compare															compare;

		public:
			node_pointer	_root;
			allocator_type	_allocator;
			compare			_compare;

		public:
			binary_tree(void) : _root(NULL), _allocator(allocator_type()), _compare(std::less<int>()) {}

			binary_tree(const compare &comp) : _root(NULL), _allocator(allocator_type()), _compare(comp) {}
			
			binary_tree(const T &val, const compare &comp = compare()) : _allocator(allocator_type()), _compare(comp)
			{
				this->_root = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root, val);
				this->_root->color = BLACK;
				this->_root->parent = NULL;
				this->_root->rhs = NULL;
				this->_root->lhs = NULL;
			}
			
			binary_tree(node_pointer node, const compare &comp = compare()) :  _root(node), _allocator(allocator_type()), _compare(comp)
			{
				this->_root->color = BLACK;
				this->_root->parent = NULL;
				this->_root->rhs = NULL;
				this->_root->lhs = NULL;
			}
			
			virtual ~binary_tree(void) {}

			binary_tree	&operator=(const binary_tree &x)
			{
				this->_root = x._root;
				this->_allocator = x._allocator;
				this->_compare = x._compare;
				return *this;
			}

			void	recolor(ft::node<T> *node)
			{
				node->uncle()->color = BLACK;
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
			}

			void	rightRotate(node_pointer node)
			{
				node_pointer	y = node->lhs;
	
				node->lhs = y->rhs;
				if (y->rhs)
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

			void	leftRotate(node_pointer node)
			{
				node_pointer	y = node->rhs;

				node->rhs = y->lhs;
				if (y->lhs)
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

			node_pointer find(const T val) const
			{
				node_pointer node = this->_root;
	
				while (node)
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

			node_pointer minimum(node_pointer node) const
			{
				node_pointer aux = node;

				while (aux->lhs)
					aux = aux->lhs;
				return aux;
			}

			node_pointer maximum(node_pointer node) const
			{
				node_pointer aux = node;

				while (aux->rhs)
					aux = aux->rhs;
				return aux;
			}



			/*
				INSERTION
			*/
			void	insert_node(const T &val)
			{
				node_pointer par;
				node_pointer aux = this->_root;
				node_pointer inserted = this->_allocator.allocate(1);

				this->_allocator.construct(inserted, ft::node<T>(val));
				if (!this->_root)
				{
					this->_root = inserted;
					this->_root->color = BLACK;
					this->_root->parent = this->_root->lhs = this->_root->rhs = NULL;
					return ;
				}
				while (aux)
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
				inserted->rhs = NULL;
				inserted->lhs = NULL;
				this->insertFix(inserted);
			}

			void	insertFix(ft::node<T> *k)
			{
				node_pointer u;
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
						break ;
				}
				this->_root->color = BLACK;
			}

			/*
				DELETION
			*/

			void	delete_val(const T &val)
			{
				node_pointer node = find(val);
				delete_node(node);
			}

			void	delete_node(node_pointer node)
			{
				node_pointer p = node->parent;
				node_pointer s = node->sibling();
				node_pointer x = node;
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
					node->swap(*x);
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
				if (check_color == BLACK)
					deleteFix(node, p, s);
			}

			void	deleteFix(node_pointer n, node_pointer p, node_pointer s)
			{
				node_pointer	c;
				node_pointer	d;

				s == p->lhs ? c = s->rhs : c = s->lhs;
				s == p->lhs ? d = s->lhs : d = s->rhs;

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

			node_pointer inorder_next(node_pointer n)
			{
				if (n == NULL)
					return this->begin();
				if (n->rhs != NULL)
					return this->minimum(n->rhs);
				else
				{
					node_pointer	p = n->parent;
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

			node_pointer	inorder_prev(node_pointer n)
			{
				if (n == NULL)
					return this->rbegin();
				if (n->lhs != NULL)
					return this->maximum(n->lhs);
				else
				{
					node_pointer	p = n->parent;
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

			node_pointer	begin(void) const
			{
				node_pointer	aux = this->_root;

				if (!aux)
					return this->_root;
				while (aux->lhs)
					aux = aux->lhs;
				return aux;
			}

			node_pointer	end(void) const
			{
				node_pointer	aux = this->_root;

				if (!aux)
					return this->_root;
				while (aux->rhs)
					aux = aux->rhs;
				return aux->rhs;
			}

			node_pointer	rbegin(void) const
			{
				node_pointer	aux = this->_root;

				if (!aux)
					return this->_root;
				while (aux->rhs)
					aux = aux->rhs;
				return aux;
			}

			node_pointer	rend(void) const
			{
				node_pointer	aux = this->_root;

				if (!aux)
					return this->_root;
				while (aux->lhs)
					aux = aux->lhs;
				return aux->lhs;
			}
	};
};
