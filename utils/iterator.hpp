/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:41:14 by rcabezas          #+#    #+#             */
/*   Updated: 2022/02/01 14:08:00 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

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
			random_access_iterator(void);
			random_access_iterator(const random_access_iterator &copy)
				: iterator_category(copy.iterator_category),
					value_type(copy.value_type),
					difference_type(copy.difference_type),
					pointer(copy.pointer),
					reference(copy.reference);

			random_access_iterator &operator=(const random_access_iterator &op)
			{
				if (this == &op)
					return *this;
				this->iterator_category = op.iterator_category;
				this->value_type = op.value_type;
				this->difference_type = op.difference_type;
				this->pointer = op.pointer;
				this->reference = op.reference;
				return *this;
			};

			virtual	~random_access_iterator(void);

			bool	operator==(const random_access_iterator &b) const
			{
				return this->reference == b.reference ? true : false;
			}
			
			bool	operator!=(const random_access_iterator &b) const
			{
				return this->reference == b.reference ? false : true;
			}

			reference	operator*(void)
			{
				return this->reference;
			}
			
			pointer		operator->(void)
			{
				return this->pointer;
			}

			random_access_iterator	&random_access_iterator::operator++(void)
			{
				this->reference += this->difference_type;
				return *this;
			}
			
			random_access_iterator	&random_access_iterator::operator--(void)
			{
				this->reference -= this->difference_type;
				return *this;
			}
			
			random_access_iterator	random_access_iterator::operator++(int)
			{
				random_access_iterator	pre = *this;

				this->reference += this->difference_type;
				return pre;
			}
			
			random_access_iterator	random_access_iterator::operator--(int)
			{
				random_access_iterator	pre = *this;

				this->reference -= this->difference_type;
				return pre;
			}

			random_access_iterator operator+(difference_type n) const
			{
				return this->reference + n;
			}
			
			random_access_iterator operator-(difference_type n) const
			{
				return this->reference - n;
			}

			bool	operator<(const T &b) const
			{
				this->reference < b.reference ? true : false
			}
			
			bool	operator>(const T &b) const
			{
				this->reference > b.reference ? true : false
			}

			bool	operator<=(const T &b) const
			{
				this->reference <= b.reference ? true : false
			}
			
			bool	operator>=(const T &b) const
			{
				this->reference >= b.reference ? true : false
			}

			random_access_iterator operator+=(difference_type n)
			{
				return this->reference += n;
			}

			random_access_iterator operator-=(difference_type n)
			{
				return this->reference -= n;
			}

			reference operator[](int n)
			{
				random_access_iterator	it;

				it = *this;
				for (int i = 1; i < n; i++)
					it++;
				return it;
			}
	};

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

			reverse_iterator(void);
			explicit reverse_iterator(iterator_type it);

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it);
			
			iterator_type base(void) const;

			reference			operator*(void) const;
			reverse_iterator	operator+(difference_type n) const;
			reverse_iterator	&operator++(void);
			reverse_iterator  	operator++(int);
			reverse_iterator	&operator+=(difference_type n);
			reverse_iterator 	operator-(difference_type n) const;
			reverse_iterator	&operator--(void);
			reverse_iterator 	operator--(int);
			reverse_iterator	&operator-= (difference_type n);
			pointer 			operator->(void) const;
			reference			operator[](difference_type n) const;
	};
};
