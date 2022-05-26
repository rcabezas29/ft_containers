/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:39:34 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/26 20:52:53 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "utils/binary_tree.hpp"
#include "utils/iterators/binarytree_iterator.hpp"
#include "utils/iterators/const_binarytree_iterator.hpp"
#include "utils/iterators/reverse_iterator.hpp"
#include "utils/enable_if.hpp"
#include "utils/is_integral.hpp"
#include "utils/lexicographical_compare.hpp"
#include "utils/pair.hpp"
#include "utils/equal.hpp"

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
			typedef typename ft::binarytree_iterator<value_type, value_compare, key_compare>			iterator;
			typedef typename ft::const_binarytree_iterator<value_type, value_compare, key_compare>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>												reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>										const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type								difference_type;
			typedef size_t																				size_type;

		private:
			allocator_type												_allocator;
			ft::binary_tree<value_type, value_compare, key_compare, allocator_type>	_btree;
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
				this->insert(first, last);
			}

			set(const set &x) {*this = x; }

			~set(void) {}

			set	&operator=(const set &x)
			{
				this->_allocator = x._allocator;
				this->clear();
				this->insert(x.begin(), x.end());
				this->_size = x._size;
				return *this;
			}


			iterator				begin(void)
			{
				return iterator(this->_btree.begin(), &this->_btree);
			}

			const_iterator			begin(void) const
			{
				return const_iterator(this->_btree.begin(), &this->_btree);
			}

			iterator				end(void)
			{
				return iterator(this->_btree.end(), &this->_btree);
			}

			const_iterator			end(void) const
			{
				return const_iterator(this->_btree.end(), &this->_btree);
			}

			reverse_iterator		rbegin(void)
			{
				return reverse_iterator(this->end());
			}

			const_reverse_iterator	rbegin(void) const
			{
				return const_reverse_iterator(this->end());
			}

			reverse_iterator		rend(void)
			{
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator	rend(void) const
			{
				return const_reverse_iterator(this->begin());
			}

			bool	empty(void) const {return this->_size == 0 ? true : false; }

			size_type	size(void) const { return this->_size; }

			size_type	max_size(void) const { return this->_allocator.max_size(); }

			ft::pair<iterator, bool>	insert(const value_type &val)
			{
				if (this->find(val) != this->end())
					return (ft::make_pair(this->find(val), false));
				this->_btree.insert_node(val);
				iterator it = this->find(val);
				++this->_size;
				return ft::make_pair(it, true);
			}

			iterator	insert(iterator position, const value_type &val)
			{
				position = this->insert(val);
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
				--this->_size;
			}

			size_type	erase(const value_type &val)
			{
				iterator	it = this->find(val);

				if (it == this->end())
					return 0;
				this->_btree.delete_val(*it);
				--this->_size;
				return 1;
			}

			void	erase(iterator first, iterator last)
			{
				iterator tmp_first = first;
				while (first != last)
				{
					tmp_first = first;
					++first;
					this->_btree.delete_val(*tmp_first);
					--this->_size;
				}
			}
			
			void	swap(set &x)
			{
				ft::binary_tree<value_type, value_compare, key_compare, allocator_type>	root_tmp;
				size_t					size_tmp;

				root_tmp = x._btree;
				size_tmp = x._size;

				x._btree = this->_btree;
				x._size = this->_size;

				this->_btree = root_tmp;
				this->_size = size_tmp;
			}

			void	clear(void)
			{
				while (this->_size > 0)
				{
					this->_btree.delete_node(this->_btree._root);
					--this->_size;
				}
			}

			key_compare	key_comp(void) const  { return key_compare(); }

			value_compare	value_comp(void) const  { return value_compare(key_comp()); }

			iterator	find(const value_type &val)
			{
				return iterator(this->_btree.find(val), &this->_btree);
			}

			const_iterator	find(const key_type &val) const
			{
				return const_iterator(this->_btree.find(val), &this->_btree);
			}

			size_type	count(const value_type &val) const
			{
				size_type	c = 0;

				for (iterator it = this->begin(); it != this->end(); it++)
					if ((*it).first == val)
						c++;
				return c;
			}

			iterator		lower_bound(const key_type &k)
			{
				if (this->value_comp()(k, *this->begin()))
					return this->begin();
				for (iterator it = this->find(k); it != this->end(); ++it)
				{
					if (this->value_comp()(*it, k))
						continue ;
					else
						return it;
				}
				return this->end();
			}
	
			const_iterator	lower_bound(const key_type &k) const
			{
				if (this->value_comp()(k, *this->begin()))
					return this->begin();
				for (const_iterator it = this->find(k); it != this->end(); ++it)
				{
					if (this->value_comp()(*it, k))
						continue ;
					else
						return it;
				}
				return this->end();
			}

			iterator		upper_bound(const key_type &k)
			{
				if (this->value_comp()(k, *this->begin()))
					return this->begin();
				for (iterator it = this->find(k); it != this->end(); ++it)
				{
					if (this->value_comp()(k, *it))
						return it;
					else
						continue ;
				}
				return this->end();
			}

			const_iterator	upper_bound(const key_type &k) const
			{
				if (this->value_comp()(k, *this->begin()))
					return this->begin();
				for (const_iterator it = this->find(k); it != this->end(); ++it)
				{
					if (this->value_comp()(k, *it))
						return it;
					else
						continue ;
				}
				return this->end();
			}
			

			pair<const_iterator, const_iterator>	equal_range(const key_type &k) const { return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
			pair<iterator, iterator>				equal_range(const key_type &k) { return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

			allocator_type	get_allocator(void) const { return this->_allocactor; }

	};

	template <class T, class Compare, class Allocator>
	bool operator==(const set< T, Compare, Allocator> &x, const set< T, Compare, Allocator> &y)
	{
		if (x.size() != y.size())
			return false;
		return ft::equal(x.begin(), x.begin(), y.end());
	}
	
	template < class T, class Compare, class Allocator>
	bool operator!=(const set<T,Compare,Allocator> &x, const set<T,Compare,Allocator> &y)
	{
		return !(x == y);
	}

	template <class T, class Compare, class Allocator>
	bool operator<(const set< T,Compare, Allocator> &x, const set< T, Compare, Allocator> &y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}
    
	template <class T, class Compare, class Allocator>
	bool operator<=(const set<T,Compare,Allocator> &x, const set<T,Compare,Allocator> &y)
	{
		return x < y || x == y;
	}

    template <class T, class Compare, class Allocator>
	bool operator>(const set< T, Compare, Allocator> &x, const set<T,Compare,Allocator> &y)
	{
		return !(x <= y);
	}

    template <class T, class Compare, class Allocator>
	bool operator>=(const set<T,Compare,Allocator> &x, const set<T,Compare,Allocator> &y)
	{
		return !(x < y);
	}

	template < class T, class Compare, class Alloc>
	void swap(set< T, Compare, Alloc> &x, set< T, Compare, Alloc> &y)
	{
		set<T,Compare,Alloc>	aux;

		aux = x;
		x = y;
		y = aux;
	}
};