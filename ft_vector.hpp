/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:52:17 by rcabezas          #+#    #+#             */
/*   Updated: 2022/01/05 19:05:26 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "utils/iterator.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T										value_type;
			typedef Alloc									allocator_type;
			typedef typename allocator_type::reference		reference;
			typedef typename allocator_type::const_referece	const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef ptrdiff_t								difference_type;
			typedef size_t									size_type;
			
		protected:
			allocator_type		_allocator;
			pointer				_array;
			size_type			_size;
			size_type			_capacity;
			
		public:
			//construction & destruction
			explicit	vector(const allocator_type &alloc = allocator_type());
			explicit	vector (size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type());
			vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type());
			vector(const vector &copy);
			~vector(void);
			vector	&operator=(const vector &op);

			//iterators
			iterator				begin(void);
			const_iterator			begin(void) const;

			iterator				end(void);
			const_iterator			end(void) const;

			reverse_iterator		rbegin(void);
			const_reverse_iterator	rbegin(void) const;

			reverse_iterator		rend(void);
			const_reverse_iterator	rend(void) const;

			//capacity
			size_type	size(void) const {return _size;};

			size_type	max_size(void) const {return _allocator.max_size();};

			void		resize (size_type n, value_type val = value_type());

			size_type	capacity(void) const {return _capacity};

			bool		empty(void) const {return (_size == 0)};

			void		reserve(size_type n);

			//element access
			reference			operator[](size_type n);
			const_reference		operator[](size_type n) const;

			reference			at(size_type n);
			const_reference		at(size_type n) const;

			reference			front(void);
			const_reference		front(void) const;

			reference			back(void);
			const_reference		back(void) const;

			value_type			*data(void) noexcept;
			const value_type	*data(void) const noexcept;

			//modifiers
			void			assign(InputIterator first, InputIterator last);
			void			assign(size_type n, const value_type &val);

			void			push_back(const value_type &val);

			void			pop_back(void);

			iterator		insert(iterator position, const value_type &val);
			void			insert(iterator position, size_type n, const value_type &val);
			void			insert (iterator position, InputIterator first, InputIterator last);

			iterator		erase(iterator position);
			iterator		erase(iterator first, iterator last);

			void			swap(vector &x);

			void			clear(void);

			allocator_type	get_allocator(void) const;
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
}
