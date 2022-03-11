/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:41:14 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/11 11:40:39 by rcabezas         ###   ########.fr       */
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
			random_access_iterator(void) : _ptr(NULL) {}

			template <typename U>
			random_access_iterator(const random_access_iterator<U> &copy) : _ptr(copy.get_pointer()) {}
			random_access_iterator(pointer p) : _ptr(p) {}

			random_access_iterator &operator=(const random_access_iterator &op)
			{
				if (this == &op)
					return *this;
				this->_ptr = op.get_pointer();
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

			bool	operator<(const random_access_iterator &b) const { return this->_ptr < b.get_pointer(); }
			
			bool	operator>(const random_access_iterator &b) const { return this->_ptr > b.get_pointer(); }

			bool	operator<=(const random_access_iterator &b) const { return this->_ptr <= b.get_pointer(); }
			
			bool	operator>=(const random_access_iterator &b) const { return this->_ptr >= b.get_pointer(); }

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

	template <typename T, typename U>
	bool operator<(const random_access_iterator<T> &a, const random_access_iterator<U> &b)
	{
		return a.get_pointer() < b.get_pointer();
	}

	template <typename T, typename U>
	bool operator>(const random_access_iterator<T> &a, const random_access_iterator<U> &b)
	{
		return a.get_pointer() > b.get_pointer();
	}
	
	template <typename T, typename U>
	bool operator<=(const random_access_iterator<T> &a, const random_access_iterator<U> &b)
	{
		return a.get_pointer() <= b.get_pointer();
	}

	template <typename T, typename U>
	bool operator>=(const random_access_iterator<T> &a, const random_access_iterator<U> &b)
	{
		return a.get_pointer() >= b.get_pointer();
	}

	template <typename T, typename U>
	typename random_access_iterator<T>::difference_type operator+(const random_access_iterator<T> &a, const random_access_iterator<U> &b)
	{
		return a.get_pointer() + b.get_pointer();
	}

	template <typename T, typename U>
	typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &a, const random_access_iterator<U> &b)
	{
		return a.get_pointer() - b.get_pointer();
	}

	template <typename T>
	ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type a, const random_access_iterator<T> &b)
	{
		return a + b.get_pointer();
	}

	template <typename T, typename U>
	bool operator!=(const random_access_iterator<T> &a, const random_access_iterator<U> &b)
	{
		return a.get_pointer() != b.get_pointer();
	}

	template <typename T, typename U>
	bool operator==(const random_access_iterator<T> &a, const random_access_iterator<U> &b)
	{
		return a.get_pointer() == b.get_pointer();
	}

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
