/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:41:14 by rcabezas          #+#    #+#             */
/*   Updated: 2022/02/25 11:14:50 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "iterator_traits.hpp"

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct Iter
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template <typename T>
	class random_access_iterator : public ft::Iter<std::random_access_iterator_tag, T>
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
			random_access_iterator(void) : _ptr(nullptr) {}
			random_access_iterator(const random_access_iterator &copy) : _ptr(copy._ptr) {}
			random_access_iterator(pointer p) : _ptr(p) {}

			random_access_iterator &operator=(const random_access_iterator &op)
			{
				if (this == &op)
					return *this;
				this->_ptr = op._ptr;
				return *this;
			}

			// virtual	~random_access_iterator(void);

			bool	operator==(const random_access_iterator &b) const { return this->_ptr == b._ptr; }
			
			bool	operator!=(const random_access_iterator &b) const { return this->_ptr != b._ptr; }

			reference	operator*(void) { return *(this->_ptr); }
			
			pointer		operator->(void) { return this->_ptr; }

			random_access_iterator	&operator++(void)
			{
				this->_ptr++;
				return *this;
			}
			
			random_access_iterator	&operator--(void)
			{
				this->_ptr--;
				return *this;
			}
			
			random_access_iterator	operator++(int)
			{
				random_access_iterator	pre = *this;
				
				this->_ptr++;
				return pre;
			}
			
			random_access_iterator	operator--(int)
			{
				random_access_iterator	pre = *this;
				
				this->_ptr--;
				return pre;
			}

			random_access_iterator operator+(difference_type n) const
			{
				random_access_iterator res(*this);

				res._ptr += n;
				return res;
			}
			
			random_access_iterator operator-(difference_type n) const
			{
				random_access_iterator res(*this);

				res._ptr -= n;
				return res;
			}

			bool	operator<(const random_access_iterator &b) const { return *this->_ptr < *b._ptr; }
			
			bool	operator>(const random_access_iterator &b) const { return *this->_ptr > *b._ptr; }

			bool	operator<=(const random_access_iterator &b) const { return *this->_ptr <= *b._ptr; }
			
			bool	operator>=(const random_access_iterator &b) const { return *this->_ptr >= *b._ptr; }

			random_access_iterator operator+=(difference_type n)
			{
				this->_ptr += n;
				return *this;
			}

			random_access_iterator operator-=(difference_type n)
			{
				this->_ptr -= n;
				return *this;
			}

			reference operator[](int n) { return this->_ptr[n]; }

			pointer	get_pointer(void) const { return this->_ptr; }
	};

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator														iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category		iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type				value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type			difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer					pointer;
			typedef typename ft::iterator_traits<Iterator>::reference				reference;

		private:
			pointer	_ptr;

		public:
			reverse_iterator(void) : _ptr(nullptr) {}
			explicit	reverse_iterator(iterator_type it) : _ptr(it._ptr) {}
			reverse_iterator(pointer p) : _ptr(p) {}

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it) : _ptr(rev_it._ptr) {}
			
			iterator_type		base(void) const
			{
				iterator_type	it(*this);

				return  it;
			}

			reference			operator*(void) const { return this->reference; }

			reverse_iterator	operator+(difference_type n) const
			{
				reverse_iterator res(*this);

				res._ptr += n;
				return res;
			}

			reverse_iterator	&operator++(void)
			{
				this->_ptr++;
				return *this;
			}

			reverse_iterator  	operator++(int)
			{
				reverse_iterator	pre = *this;
				
				this->_ptr++;
				return pre;
			}
			
			reverse_iterator	&operator+=(difference_type n)
			{
				this->_ptr += n;
				return *this;
			}
			
			reverse_iterator 	operator-(difference_type n) const
			{
				reverse_iterator res(*this);

				res._ptr -= n;
				return res;
			}
			
			reverse_iterator	&operator--(void)
			{
				this->_ptr--;
				return *this;
			}

			reverse_iterator 	operator--(int)
			{
				reverse_iterator	pre = *this;
				
				this->_ptr++;
				return pre;
			}

			reverse_iterator	&operator-=(difference_type n)
			{
				this->_ptr -= n;
				return *this;
			}
			
			pointer 			operator->(void) const  { return this->_ptr; }

			reference			operator[](difference_type n) const { return this->_ptr[n]; }
	};
};
