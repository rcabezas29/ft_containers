/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:44:37 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/16 20:33:01 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"

namespace	ft
{
	typedef enum	node_color
	{
		BLACK,
		RED
	};

	template <class T>
	struct	node
	{
		T			value;
		struct node	*lhs;
		struct node	*rhs;
		node_color	color;

		node(void): _lhs(NULL), _rhs(NULL), color(BLACK) {}
		node(const T value): value(value), lhs(NULL), rhs(NULL), color(BLACK) {}
	};

	template <class T, class Comp, class Alloc>
	class	binary_tree
	{
		public:
			typedef typename std::allocator_traits<Alloc>::rebind_alloc<ft::node<T> >::other	allocator_type; // Alloc::rebind<ft::node<T> >::other

		private:
			struct node			*_root;
			allocator_type		_allocator;

		public:
			binary_tree(const allocator_type &alloc = allocator_type()) : _root(NULL), _allocator(alloc) {}
			binary_tree(const T &val, const allocator_type &alloc = allocator_type()) : _allocator(alloc)
			{
				this->_root = this->_allocator.allocate(1);
				this->_root(val); 
			}
			binary_tree(node<T> node, const allocator_type &alloc = allocator_type()) :  _root(node), _allocator(alloc) {}
			virtual ~binary_tree(void);

			void	insert_node(const node<T> &node)
			{
				
			}

			void	delete_node(const node<T> *node)
			{
				
			}

	};

};
