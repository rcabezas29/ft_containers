/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_binarytree_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:12:43 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/23 12:53:48 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include "../binary_tree.hpp"

namespace ft
{
	template <typename T, class Compare, class Comp>
	class	const_binarytree_iterator
	{
		public:
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::Iter<std::random_access_iterator_tag, const T>::pointer				pointer;
			typedef typename ft::Iter<std::random_access_iterator_tag, const T>::reference			reference;
			typedef const typename ft::node<value_type>*										node_pointer;
			typedef const typename ft::binary_tree<T, Compare, Comp>*									bt_pointer;

		private:
			bt_pointer		_tree;
			node_pointer	_ptr;

		public:
			const_binarytree_iterator(void) :_tree(NULL), _ptr(NULL) {}

			template <typename U, class C, class D>
			const_binarytree_iterator(const binarytree_iterator<U, C, D> &copy) : _tree(copy.get_tree()), _ptr(copy.get_pointer()) {}

			template <typename U, class C, class D>
			const_binarytree_iterator(const const_binarytree_iterator<U, C, D> &copy) : _tree(copy.get_tree()), _ptr(copy.get_pointer()) {}
			
			const_binarytree_iterator(node_pointer p, bt_pointer t) : _tree(t), _ptr(p) {}

			bool	operator==(const const_binarytree_iterator &b) const { return this->_ptr == b.get_pointer(); }
			
			bool	operator!=(const const_binarytree_iterator &b) const { return this->_ptr != b.get_pointer(); }

			reference	operator*(void) const { return this->_ptr->value; }
			
			pointer		operator->(void) const { return &(this->_ptr->value); }

			const_binarytree_iterator	&operator++(void)
			{
				this->_ptr = this->_tree->inorder_next(this->_ptr);
				return *this;
			}

			const_binarytree_iterator	&operator--(void)
			{
				this->_ptr = this->_tree->inorder_prev(this->_ptr);
				return *this;
			}
			
			const_binarytree_iterator	operator++(int)
			{
				const_binarytree_iterator	pre = *this;
				
				this->_ptr = this->_tree->inorder_next(this->_ptr);
				return pre;
			}
			
			const_binarytree_iterator	operator--(int)
			{
				const_binarytree_iterator	pre = *this;
				
				this->_ptr = this->_tree->inorder_prev(this->_ptr);
				return pre;
			}

			node_pointer	get_pointer(void) const { return this->_ptr; }
			bt_pointer		get_tree(void) const { return this->_tree; }
	};
};
