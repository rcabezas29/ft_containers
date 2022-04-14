/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarytree_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 08:02:15 by rcabezas          #+#    #+#             */
/*   Updated: 2022/04/14 19:44:18 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include "../binary_tree.hpp"

namespace ft
{
	template <typename T>
	class binarytree_iterator
	{
		public:
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::iterator_category	iterator_category;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::value_type		value_type;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::difference_type	difference_type;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::pointer			pointer;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::reference			reference;

		private:
			pointer	_ptr;

		public:
			binarytree_iterator(void) : _ptr(NULL) {}

			template <typename U>
			binarytree_iterator(const binarytree_iterator<U> &copy) : _ptr(copy.get_pointer()) {}
			binarytree_iterator(pointer p) : _ptr(p) {}

			binarytree_iterator &operator=(const binarytree_iterator &op)
			{
				if (this == &op)
					return *this;
				this->_ptr = op.get_pointer();
				return *this;
			}

			bool	operator==(const binarytree_iterator &b) const { return this->_ptr == b._ptr; }
			
			bool	operator!=(const binarytree_iterator &b) const { return this->_ptr != b._ptr; }

			reference	operator*(void) { return *(this->_ptr); }
			
			pointer		operator->(void) { return this->_ptr; }

			binarytree_iterator	&operator++(void)
			{
				this->_ptr = inorder_next(this->_ptr);
				return *this;
			}
			
			binarytree_iterator	&operator--(void)
			{
				this->_ptr = inorder_prev(this->_ptr);
				return *this;
			}
			
			binarytree_iterator	operator++(int)
			{
				binarytree_iterator	pre = *this;

				this->_ptr = inorder_next(this->_ptr);
				return pre;
			}
			
			binarytree_iterator	operator--(int)
			{
				binarytree_iterator	pre = *this;
				
				this->_ptr = inorder_prev(this->_ptr);
				return pre;
			}

			pointer	get_pointer(void) const { return this->_ptr; }

	};
};

