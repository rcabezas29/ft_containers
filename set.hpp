/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:39:34 by rcabezas          #+#    #+#             */
/*   Updated: 2022/04/11 18:01:28 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils/binary_tree.hpp"

namespace	ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T														key_type;
			typedef T														value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename std::bidirectional_iterator<value_type>		iterator;
			typedef typename std::bidirectional_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

		private:
			allocator_type												_allocactor;
			ft::binary_tree<value_type, key_compare, allocator_type>	_btree;
			size_type													_size;

		public:	
			explicit set(const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type());

			template <class InputIterator>
			set(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type());

			set(const set &x);

			~set(void);

			set	&operator=(const set &x);

			iterator				begin(void);
			const_iterator			begin(void) const;

			iterator				end(void);
			const_iterator			end(void) const;

			reverse_iterator		rbegin(void);
			const_reverse_iterator	rbegin(void) const;

			reverse_iterator		rend(void);
			const_reverse_iterator	rend(void) const;

			bool	empty(void) const;

			size_type	size(void) const;

			size_type	max_size(void) const;


			ft::pair<iterator, bool>	insert(const value_type &val);

			iterator	insert(iterator position, const value_type &val);

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last);

			void	erase(iterator position);

			size_type	erase(const value_type &val);

			void	erase(iterator first, iterator last);
			
			void	swap(set &x);

			void	clear(void);

			key_compare	key_comp(void) const;

			value_compare	value_comp(void) const;

			iterator	find(const value_type &val) const;

			size_type	count(const value_type &val) const;

			iterator	lower_bound(const value_type &val) const;

			iterator	upper_bound(const value_type &val) const;

			ft::pair<iterator,iterator>	equal_range(const value_type &val) const;

			allocator_type	get_allocator(void) const;

	};
};