/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:05:17 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/18 11:51:45 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "random_access_iterator.hpp"

namespace ft
{
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
			iterator_type	_base;

		public:
			reverse_iterator(void) : _base(iterator_type()) {}
			explicit	reverse_iterator(iterator_type it) : _base(it) {}
			reverse_iterator(pointer p) : _base(p) {}

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it) : _base(rev_it.base()) {}
			
			iterator_type		base(void) const
			{
				return  iterator_type(this->_base);
			}

			bool	operator==(const reverse_iterator &b) const { return this->_base == b.base(); }
			
			bool	operator!=(const reverse_iterator &b) const { return this->_base != b.base(); }

			reference			operator*(void) const
			{
				iterator_type ret = this->_base;
				return (*(--ret));
			}

			reverse_iterator	operator+(difference_type n) const
			{
				return reverse_iterator(this->_base - n);
			}

			reverse_iterator	&operator++(void)
			{
				this->_base--;
				return *this;
			}

			reverse_iterator  	operator++(int)
			{
				reverse_iterator	pre = *this;
				
				this->_base--;
				return pre;
			}
			
			reverse_iterator	&operator+=(difference_type n)
			{
				this->_base -= n;
				return *this;
			}
			
			reverse_iterator 	operator-(difference_type n) const
			{
				return reverse_iterator(this->_base + n);
			}
			
			reverse_iterator	&operator--(void)
			{
				this->_base++;
				return *this;
			}

			reverse_iterator 	operator--(int)
			{
				reverse_iterator	pre = *this;
				
				this->_base++;
				return pre;
			}

			reverse_iterator	&operator-=(difference_type n)
			{
				this->_base += n;
				return *this;
			}

			bool	operator<(const reverse_iterator &b) const { return this->base() > b.base(); }
			
			bool	operator>(const reverse_iterator &b) const { return this->base() < b.base(); }

			bool	operator<=(const reverse_iterator &b) const { return this->base() >= b.base(); }
			
			bool	operator>=(const reverse_iterator &b) const { return this->base() <= b.base(); }
			
			pointer 			operator->(void) const  { return &operator*(); }

			reference			operator[](difference_type n) const { return base()[ -n - 1]; }

			pointer				get_pointer(void) const { return this->_ptr; }
	};

	template <class It1, class It2>
	bool	operator==(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class It1, class It2>
	bool	operator!=(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class It1, class It2>
	bool	operator>(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class It1, class It2>
	bool	operator<(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class It1, class It2>
	bool	operator>=(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class It1, class It2>
	bool	operator<=(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename T, typename U>
	typename reverse_iterator<T>::difference_type operator+(const reverse_iterator<T> &a, const reverse_iterator<U> &b)
	{
		return a.base() + b.base();
	}

	template <typename T, typename U>
	typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T> &a, const reverse_iterator<U> &b)
	{
		return b.base() - a.base();
	}

	template <typename T>
	reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type a, const reverse_iterator<T> &b)
	{
		return b + a;
	}

	template <typename T>
	reverse_iterator<T> operator-(typename reverse_iterator<T>::difference_type a, const reverse_iterator<T> &b)
	{
		return b - a;
	}

	template <typename T>
	reverse_iterator<T> operator-(const reverse_iterator<T> &a, typename reverse_iterator<T>::difference_type &b)
	{
		return a.base() - b;
	}
};
