/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:05:17 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/11 21:10:35 by rcabezas         ###   ########.fr       */
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
			pointer	_ptr;

		public:
			reverse_iterator(void) : _ptr(NULL) {}
			explicit	reverse_iterator(iterator_type it) : _ptr(it.get_pointer()) {}
			reverse_iterator(pointer p) : _ptr(p) {}

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it) : _ptr(rev_it.get_pointer()) {}
			
			iterator_type		base(void) const
			{
				return  iterator_type(this->_ptr);
			}

			bool	operator==(const reverse_iterator &b) const { return this->_ptr == b._ptr; }
			
			bool	operator!=(const reverse_iterator &b) const { return this->_ptr != b._ptr; }

			reference			operator*(void) const
			{
				iterator_type ret = this->_ptr;
				return (*(--ret));
			}

			reverse_iterator	operator+(difference_type n) const
			{
				return reverse_iterator(this->_ptr - n);
			}

			reverse_iterator	&operator++(void)
			{
				this->_ptr--;
				return *this;
			}

			reverse_iterator  	operator++(int)
			{
				reverse_iterator	pre = *this;
				
				this->_ptr--;
				return pre;
			}
			
			reverse_iterator	&operator+=(difference_type n)
			{
				this->_ptr -= n;
				return *this;
			}
			
			reverse_iterator 	operator-(difference_type n) const
			{
				return reverse_iterator(this->_ptr + n);
			}
			
			reverse_iterator	&operator--(void)
			{
				this->_ptr++;
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
				this->_ptr += n;
				return *this;
			}

			bool	operator<(const reverse_iterator &b) const { return this->get_pointer() > b.get_pointer(); }
			
			bool	operator>(const reverse_iterator &b) const { return this->get_pointer() < b.get_pointer(); }

			bool	operator<=(const reverse_iterator &b) const { return this->get_pointer() >= b.get_pointer(); }
			
			bool	operator>=(const reverse_iterator &b) const { return this->get_pointer() <= b.get_pointer(); }
			
			pointer 			operator->(void) const  { return &operator*(); }

			reference			operator[](difference_type n) const { return base()[ -n - 1]; }

			pointer				get_pointer(void) const { return this->_ptr; }
	};

	template <class It1, class It2>
	bool	operator==(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.get_pointer() == rhs.get_pointer();
	}

	template <class It1, class It2>
	bool	operator!=(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.get_pointer() != rhs.get_pointer();
	}

	template <class It1, class It2>
	bool	operator>(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.get_pointer() < rhs.get_pointer();
	}

	template <class It1, class It2>
	bool	operator<(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.get_pointer() > rhs.get_pointer();
	}

	template <class It1, class It2>
	bool	operator>=(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.get_pointer() <= rhs.get_pointer();
	}

	template <class It1, class It2>
	bool	operator<=(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{
		return lhs.get_pointer() >= rhs.get_pointer();
	}

	template <typename T, typename U>
	typename reverse_iterator<random_access_iterator<T> >::difference_type operator+(const reverse_iterator<random_access_iterator<T> > &a, const reverse_iterator<random_access_iterator<U> > &b)
	{
		return a.get_pointer() + b.get_pointer();
	}

	template <typename T, typename U>
	typename reverse_iterator<random_access_iterator<T> >::difference_type operator-(const reverse_iterator<random_access_iterator<T> > &a, const reverse_iterator<random_access_iterator<U> > &b)
	{
		return b.get_pointer() - a.get_pointer();
	}

	template <typename T>
	reverse_iterator<random_access_iterator<T> > operator+(typename reverse_iterator<random_access_iterator<T> >::difference_type a, const reverse_iterator<random_access_iterator<T> > &b)
	{
		return b + a;
	}

	template <typename T>
	reverse_iterator<T> operator-(typename reverse_iterator<random_access_iterator<T> >::difference_type a, const reverse_iterator<random_access_iterator<T> > &b)
	{
		return b - a;
	}

	template <typename T>
	reverse_iterator<T> operator-(const reverse_iterator<random_access_iterator<T> > &a, typename reverse_iterator<random_access_iterator<T> >::difference_type &b)
	{
		return a.get_pointer() - b;
	}
};
