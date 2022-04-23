/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:39:34 by rcabezas          #+#    #+#             */
/*   Updated: 2022/04/12 09:03:41 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "utils/binary_tree.hpp"
#include "utils/iterators/binarytree_iterator.hpp"
#include "utils/enable_if.hpp"
#include "utils/is_integral.hpp"
#include "utils/iterators/reverse_iterator.hpp"

namespace	ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T														key_type;
			typedef T														value_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename ft::binarytree_iterator<value_type>			iterator;
			typedef typename ft::binarytree_iterator<const value_type>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

		private:
			allocator_type												_allocator;
			ft::binary_tree<value_type, key_compare, allocator_type>	_btree;
			size_type													_size;

		public:	
			explicit set(const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type())
			: _allocator(alloc), _btree(comp), _size(0) {}

			template <class InputIterator>
			set(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type())
				: _allocator(alloc), _btree(comp), _size(0)
			{
				while (first != last)
				{
					_btree.insert_node(*first++);
					++_size;
				}
			}

			set(const set &x) {*this = x; }

			~set(void) {}

			set	&operator=(const set &x)
			{
				this->_allocator = x._allocator;
				this->_btree = x._btree;
				this->_size = x._size;
				return *this;
			}


			iterator				begin(void)
			{
				return iterator(this->_btree.begin());
			}

			const_iterator			begin(void) const
			{
				return const_iterator(this->_btree.begin());
			}

			iterator				end(void)
			{
				return iterator(this->_btree.end());
			}

			const_iterator			end(void) const
			{
				return const_iterator(this->_btree.end());
			}

			reverse_iterator		rbegin(void)
			{
				return reverse_iterator(this->_btree.rbegin());
			}

			const_reverse_iterator	rbegin(void) const
			{
				return const_reverse_iterator(this->_btree.rbegin());
			}

			reverse_iterator		rend(void)
			{
				return iterator(this->_btree.rend());
			}

			const_reverse_iterator	rend(void) const
			{
				return const_iterator(this->_btree.rend());
			}

			bool	empty(void) const {return this->_size == 0 ? true : false; }

			size_type	size(void) const { return this->_size; }

			size_type	max_size(void) const { return this->_allocactor.max_size(); }

			ft::pair<iterator, bool>	insert(const value_type &val)
			{
				this->_btree.insert_node(val);
				iterator it = this->find(val.first);
				++this->_size;
				return ft::make_pair(it, true);
			}

			iterator	insert(iterator position, const value_type &val)
			{
				position = this->insert(val).first;
				return position;
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					this->insert(*first++);
			}

			void	erase(iterator position)
			{
				this->_btree.delete_val(*position);
			}

			size_type	erase(const value_type &val)
			{
				iterator	it = this->find(val);
				this->_btree.delete_val(*it);
				return (1);
			}

			void	erase(iterator first, iterator last)
			{
				while (first++ != last)
					this->_btree.delete_val(*first);
			}
			
			void	swap(set &x)
			{
				set aux = *this;
				*this = x;
				x = aux;
			}

			void	clear(void)
			{
				while (this->_size != 0)
					this->_btree.delete_node(this->_btree._root);
			}

			key_compare	key_comp(void) const  { return key_compare(); }

			value_compare	value_comp(void) const  { return value_compare(key_comp()); }

			iterator	find(const value_type &val) const
			{
				return iterator(this->_btree.find(val));
			}

			size_type	count(const value_type &val) const
			{
				size_type	c = 0;

				for (iterator it = this->begin(); it != this->end(); it++)
					if ((*it).first == val)
						c++;
				return c;
			}

			iterator	lower_bound(const value_type &val) const;

			iterator	upper_bound(const value_type &val) const;

			ft::pair<iterator,iterator>	equal_range(const value_type &val) const;

			allocator_type	get_allocator(void) const { return this->_allocactor; }

	};
};