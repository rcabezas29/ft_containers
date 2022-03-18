/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:44:37 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/18 16:18:16 by rcabezas         ###   ########.fr       */
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
			this->parent = op.parent;
			this->lhs = op.lhs;
			this->rhs = op.rhs;
			this->color = op.color;
			return *this;
		}

		node	*uncle(void) { return this->parent->parent->lhs == this->parent ? this->parent->parent->rhs : this->parent->parent->lhs; }
		void	swap(node &b)
		{
			T	aux = b->value;

			b->value = this->value;
			this->value = aux;
		}
	};

	template <class T, class Comp, class Alloc = std::allocator<T> >
	class	binary_tree
	{
		public:
			typedef typename Alloc::template rebind<ft::node<T> >::other	allocator_type;

		private:
			node<T>			*_root;
			allocator_type	_allocator;

		public:
			binary_tree(const allocator_type &alloc = allocator_type()) : _root(NULL), _allocator(alloc) {}
			binary_tree(const T &val, const allocator_type &alloc = allocator_type()) : _allocator(alloc)
			{
				this->_root = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root, val);
			}
			binary_tree(ft::node<T> node, const allocator_type &alloc = allocator_type()) :  _root(node), _allocator(alloc) {}
			virtual ~binary_tree(void) {}

			void	insert_node(const ft::node<T> &node)
			{
				ft::node<T>	*aux = this->_root;
				while (aux)
				{
					if (aux->value > node.value)
						aux = aux->rhs;
					else
						aux = aux->lhs;
				}
				aux = this->_allocator.allocate(1);
				*aux = node;
			}

			void	delete_node(const node<T> *node)
			{
				ft::node<T>	*aux = this->_root;
				while (aux)
				{
					if (aux->value > node->value)
						aux = aux->rhs;
					else
						aux = aux->lhs;
				}
				if (aux->lhs)
				{
					aux->swap(aux->lhs);
					this->_allocator.destroy(aux->lhs);
				}
				else if (aux->rhs)
				{
					aux->swap(aux->rhs);
					this->_allocator.destroy(aux->rhs);
				}
				else
					this->_allocator.destroy(aux);
			}

	};

};
