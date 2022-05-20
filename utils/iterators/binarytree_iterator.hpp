/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarytree_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 08:02:15 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/20 15:20:31 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include "../binary_tree.hpp"

namespace ft
{
	template <class T, class Compare>
	class	binarytree_iterator
	{
		public:
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::node<value_type>*												node_pointer;
			typedef typename ft::binary_tree<T, Compare>*										bt_pointer;

		private:
			bt_pointer		_tree;
			node_pointer	_ptr;
		
		public:
			binarytree_iterator(void) :_tree(NULL), _ptr(NULL) {}

			template <typename U, class C>
			binarytree_iterator(const binarytree_iterator<U, C> &copy) : _tree(copy.get_tree()), _ptr(copy.get_pointer()) {}
			binarytree_iterator(node_pointer p, bt_pointer t) : _tree(t), _ptr(p) {}

			binarytree_iterator &operator=(const binarytree_iterator &op)
			{
				if (this == &op)
					return *this;
				this->_ptr = op.get_pointer();
				this->_tree = op.get_tree();
				return *this;
			}

			bool	operator==(const binarytree_iterator &b) const { return this->_ptr == b.get_pointer(); }
			
			bool	operator!=(const binarytree_iterator &b) const { return this->_ptr != b.get_pointer(); }

			reference	operator*(void) { return this->_ptr->value; }
			
			pointer		operator->(void) { return &(this->_ptr->value); }

			binarytree_iterator	&operator++(void)
			{
				this->_ptr = this->_tree->inorder_next(this->_ptr);
				return *this;
			}

			binarytree_iterator	&operator--(void)
			{
				this->_ptr = this->_tree->inorder_prev(this->_ptr);
				return *this;
			}
			
			binarytree_iterator	operator++(int)
			{
				binarytree_iterator	pre = *this;
				
				this->_ptr = this->_tree->inorder_next(this->_ptr);
				return pre;
			}
			
			binarytree_iterator	operator--(int)
			{
				binarytree_iterator	pre = *this;
				
				this->_ptr = this->_tree->inorder_prev(this->_ptr);
				return pre;
			}

			node_pointer	get_pointer(void) const { return this->_ptr; }
			bt_pointer		get_tree(void) const { return this->_tree; }
	};
};

