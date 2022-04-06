/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:44:37 by rcabezas          #+#    #+#             */
/*   Updated: 2022/04/05 20:30:35 by rcabezas         ###   ########.fr       */
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
				ft::node<T>	*parent = NULL;
				ft::node<T>	*x = NULL;

				if (node->lhs == NULL && node->rhs == NULL)
				{
					parent = node->parent;
					parent->rhs = node ? parent->rhs = NULL : parent->lhs = NULL;
					node = NULL;
				}
				else if ((node->lhs == NULL && node->rhs != NULL) || (node->rhs == NULL && node->lhs != NULL))
				{
					parent = node->parent;
					node->rhs ? x = node->rhs : x = node->lhs;
					if (node == parent->rhs)
						parent->rhs = x;
					else
						parent->lhs = x;
					x->parent = parent;
					if (node->color == BLACK)
						x->color = BLACK;
					node = NULL;
				}
				else
				{
					x = maximum(node->lhs);
					node->swap(*x);
					delete_node(x);
				}
				// if (double_black)
				// 	deleteFix();
			}

			void	deleteFix(ft::node<T> *n)
			{
				ft::node<T>	*p = n->parent;
				ft::node<T>	*s = n->sibling();
				ft::node<T>	*c = n->closest_nephew();
				ft::node<T>	*d = n->farthest_nephew();
				

				while (p != NULL)
				{
					if ()
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
