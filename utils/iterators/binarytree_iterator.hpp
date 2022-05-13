/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarytree_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 08:02:15 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/13 10:56:49 by rcabezas         ###   ########.fr       */
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
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::pointer			node_pointer;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, ft::node<T> >::reference			node_reference;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, T>::pointer						pointer;
			typedef typename ft::Iter<std::bidirectional_iterator_tag, T>::reference					reference;

		private:
			node_pointer	_ptr;
			node_pointer	_root;

		public:
			binarytree_iterator(void) : _ptr(NULL), _root(NULL) {}

			template <typename U>
			binarytree_iterator(const binarytree_iterator<U> &copy) : _ptr(copy.get_pointer()), _root(copy.get_root()) {}

			binarytree_iterator(node_pointer p) : _ptr(p)
			{
				if (p)
				{
					while (p->parent)
						p = p->parent;
				}
				this->_root = p;
			}

			~binarytree_iterator(void) {}

			binarytree_iterator &operator=(const binarytree_iterator &op)
			{
				if (this == &op)
					return *this;
				this->_ptr = op.get_pointer();
				this->_root = op.get_root();
				return *this;
			}

			bool	operator==(const binarytree_iterator &b) const { return this->_ptr == b._ptr; }

			bool	operator!=(const binarytree_iterator &b) const { return this->_ptr != b._ptr; }

			reference	operator*(void) const { return this->_ptr->value; }

			pointer		operator->(void) const { return &(this->_ptr->value); }

			binarytree_iterator	&operator++(void)
			{
				if (!this->_ptr)
					this->_ptr = minimum(this->_root);
				else
					this->_ptr = inorder_next(this->_ptr);
				return *this;
			}
			
			binarytree_iterator	&operator--(void)
			{
				if (!this->_ptr)
					this->_ptr = maximum(this->_root);
				else
					this->_ptr = inorder_prev(this->_ptr);
				return *this;
			}
			
			binarytree_iterator	operator++(int)
			{
				binarytree_iterator	pre = *this;

				if (!this->_ptr)
					this->_ptr = minimum(this->_root);
				else
					this->_ptr = inorder_next(this->_ptr);
				return pre;
			}
			
			binarytree_iterator	operator--(int)
			{
				binarytree_iterator	pre = *this;
				
				if (!this->_ptr)
					this->_ptr = maximum(this->_root);
				else
					this->_ptr = inorder_prev(this->_ptr);
				return pre;
			}

			node_pointer	get_pointer(void) const { return this->_ptr; }
			node_pointer	get_root(void) const { return this->_root; }

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

