/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:05:05 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/14 17:16:48 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator.hpp"


namespace ft
{
	
	template <typename T>
	class random_access_iterator
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
};
