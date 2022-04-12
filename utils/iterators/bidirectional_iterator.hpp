/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:05:31 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/15 19:58:04 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{
	template <typename T>
	class	bidirectional_iterator
	{
		public:
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::Iter<std::random_access_iterator_tag, T>::reference			reference;

		private:
			pointer	_ptr;

		public:
			bidirectional_iterator(void) : _ptr(NULL) {}

			template <typename U>
			bidirectional_iterator(const bidirectional_iterator<U> &copy) : _ptr(copy.get_pointer()) {}
			bidirectional_iterator(pointer p) : _ptr(p) {}

			bidirectional_iterator &operator=(const bidirectional_iterator &op)
			{
				if (this == &op)
					return *this;
				this->_ptr = op.get_pointer();
				return *this;
			}

			bool	operator==(const bidirectional_iterator &b) const { return this->_ptr == b._ptr; }
			
			bool	operator!=(const bidirectional_iterator &b) const { return this->_ptr != b._ptr; }

			reference	operator*(void) { return *(this->_ptr); }
			
			pointer		operator->(void) { return this->_ptr; }

			bidirectional_iterator	&operator++(void)
			{
				this->_ptr++;
				return *this;
			}
			
			bidirectional_iterator	&operator--(void)
			{
				this->_ptr--;
				return *this;
			}
			
			bidirectional_iterator	operator++(int)
			{
				bidirectional_iterator	pre = *this;
				
				this->_ptr++;
				return pre;
			}
			
			bidirectional_iterator	operator--(int)
			{
				bidirectional_iterator	pre = *this;
				
				this->_ptr--;
				return pre;
			}

			pointer	get_pointer(void) const { return this->_ptr; }
	};
};
