/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarytree_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 08:02:15 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/17 19:35:30 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include "../binary_tree.hpp"

namespace ft
{
	template <typename T, class Compare = std::less<T> >
	class binarytree_iterator
	{
		public:
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::iterator_category	iterator_category;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::value_type		value_type;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::difference_type	difference_type;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::pointer			node_pointer;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::reference			node_reference;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, T>::pointer						pointer;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, T>::reference					reference;
			typedef typename ft::binary_tree<T, Compare>*												bt_pointer;

		private:
			bt_pointer		_tree;
			node_pointer	_ptr;

		public:
			binarytree_iterator(void) : _tree(NULL), _ptr(NULL) {}

			template <typename U>
			binarytree_iterator(const binarytree_iterator<U> &copy) : _tree(copy.get_tree()), _ptr(copy.get_pointer()) {}

			binarytree_iterator(node_pointer p, bt_pointer t) : _tree(t), _ptr(p) {}

			~binarytree_iterator(void) {}

			binarytree_iterator &operator=(const binarytree_iterator &op)
			{
				if (this == &op)
					return *this;
				this->_ptr = op.get_pointer();
				this->_tree = op.get_tree();
				return *this;
			}

			bool	operator==(const binarytree_iterator &b) const { return this->_ptr == b._ptr; }

			bool	operator!=(const binarytree_iterator &b) const { return this->_ptr != b._ptr; }

			reference	operator*(void) const { return this->_ptr->value; }

			pointer		operator->(void) const { return &(this->_ptr->value); }

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

	template <typename T, typename U>
	bool operator<(const binarytree_iterator<T> &a, const binarytree_iterator<U> &b)
	{
		return a.get_pointer() < b.get_pointer();
	}

	template <typename T, typename U>
	bool operator>(const binarytree_iterator<T> &a, const binarytree_iterator<U> &b)
	{
		return a.get_pointer() > b.get_pointer();
	}
	
	template <typename T, typename U>
	bool operator<=(const binarytree_iterator<T> &a, const binarytree_iterator<U> &b)
	{
		return a.get_pointer() <= b.get_pointer();
	}

	template <typename T, typename U>
	bool operator>=(const binarytree_iterator<T> &a, const binarytree_iterator<U> &b)
	{
		return a.get_pointer() >= b.get_pointer();
	}

	template <typename T, typename U>
	typename binarytree_iterator<T>::difference_type operator+(const binarytree_iterator<T> &a, const binarytree_iterator<U> &b)
	{
		return a.get_pointer() + b.get_pointer();
	}

	template <typename T, typename U>
	typename binarytree_iterator<T>::difference_type operator-(const binarytree_iterator<T> &a, const binarytree_iterator<U> &b)
	{
		return a.get_pointer() - b.get_pointer();
	}

	template <typename T>
	ft::binarytree_iterator<T> operator+(typename ft::binarytree_iterator<T>::difference_type a, const binarytree_iterator<T> &b)
	{
		return a + b.get_pointer();
	}

	template <typename T, typename U>
	bool operator!=(const binarytree_iterator<T> &a, const binarytree_iterator<U> &b)
	{
		return a.get_pointer() != b.get_pointer();
	}

	template <typename T, typename U>
	bool operator==(const binarytree_iterator<T> &a, const binarytree_iterator<U> &b)
	{
		return a.get_pointer() == b.get_pointer();
	}
};

