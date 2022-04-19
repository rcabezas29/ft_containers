/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:35:59 by rcabezas          #+#    #+#             */
/*   Updated: 2022/04/19 18:11:58 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <functional>
#include "utils/binary_tree.hpp"
#include "utils/iterators/binarytree_iterator.hpp"
#include "utils/iterators/reverse_iterator.hpp"
#include "utils/enable_if.hpp"
#include "utils/is_integral.hpp"
#include "utils/lexicographical_compare.hpp"
#include "utils/pair.hpp"

namespace	ft
{	
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef typename ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare													key_compare;
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

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool	operator()(const value_type &x, const value_type &y) const { return comp(x.first, y.first); }
			};

		private:
			allocator_type												_allocator;
			ft::binary_tree<value_type, key_compare, allocator_type>	_btree;
			size_type													_size;

		public:
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _allocator(alloc), _btree(comp), _size(0) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value,
					InputIterator>::type* = NULL)
				: _allocator(alloc), _btree(comp), _size(0)
			{
				while (first != last)
				{
					_btree.insert_node(*first++);
					++_size;
				}
			}

			map(const map& x) { *this = x; }

			virtual	~map(void) {}

			map	&operator=(const map &x)
			{
				this->_allocator = x._allocator;
				this->_btree = x._btree;
				this->_size = x._size;
				return *this;
			}

			iterator begin(void)
			{
				return iterator(this->_btree.begin());
			}

			const_iterator begin(void) const
			{
				return const_iterator(this->_btree.begin());
			}

			iterator end(void)
			{
				return iterator(this->_btree.end());
			}

			const_iterator end(void) const
			{
				return const_iterator(this->_btree.end());
			}

			reverse_iterator rbegin(void)
			{
				return reverse_iterator(this->_btree.rbegin());
			}
			
			const_reverse_iterator rbegin(void) const
			{
				return const_reverse_iterator(this->_btree.rbegin());
			}

			reverse_iterator rend(void)
			{
				return iterator(this->_btree.rend());
			}

			const_reverse_iterator rend(void) const
			{
				return const_iterator(this->_btree.rend());
			}

			bool empty(void) const {return this->_size == 0 ? true : false; }
			size_type size(void) const { return this->_size; }
			size_type max_size(void) const { return this->_allocator.max_size(); }

			mapped_type	&operator[](const key_type &k)
			{
				iterator aux = this->find(k);

				if (aux == this->end())
					this->insert(ft::make_pair(k, mapped_type()));
				aux = this->find(k);
				return ((*aux).second);
			}

			pair<iterator, bool>	insert(const value_type &val)
			{
				this->_btree.insert_node(val);
				iterator it = this->find(val.first);
				++this->_size;
				return ft::make_pair(it, true);
			}

			iterator insert(iterator position, const value_type &val);
			
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value,
					InputIterator>::type* = NULL);

			void erase(iterator position)
			{
				this->_btree.delete_val(*position);
			}

			size_type erase(const key_type &k)
			{
				iterator	it = this->find(k);
				this->_btree.delete_val(*it);
				return (1);
			}

			void erase(iterator first, iterator last)
			{
				while (first++ != last)
					this->_btree.delete_val(*first);
			}

			void swap(map& x)
			{
				map aux = *this;
				*this = x;
				x = aux;
			}

			void clear(void)
			{
				while (this->_size != 0)
					this->_btree.delete_node(this->_btree._root);
			}

			key_compare		key_comp(void) const;
			value_compare	value_comp(void) const;

			iterator		find(const key_type &k)
			{
				return iterator(this->_btree.find(ft::make_pair(k, mapped_type())));
			}

			const_iterator	find(const key_type &k) const;

			size_type	count(const key_type &k) const
			{
				size_type	c = 0;

				for (iterator it = this->begin(); it != this->end(); it++)
					if (*it.first == k)
						c++;
				return c;
			}

			iterator		lower_bound(const key_type &k)
			{
				iterator	it = find(k);
				return --it;
			}

			const_iterator	lower_bound(const key_type &k) const;

			iterator		upper_bound(const key_type &k)
			{
				iterator	it = find(k);
				return ++it;
			}

			const_iterator	upper_bound(const key_type &k) const;

			pair<const_iterator, const_iterator>	equal_range(const key_type &k) const;
			pair<iterator, iterator>				equal_range(const key_type &k);

			allocator_type	get_allocator(void) const { return this->_allocator; }
	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key,T,Compare,Allocator> &x, const map<Key,T,Compare,Allocator> &y)
	{
		if (x.size() != y.size())
			return false;
		for (typename map<Key,T,Compare,Allocator>::iterator it = x.begin(), ite = y.begin(); it != x.end(); it++, ite++)
			if (it != ite)
				return false;
		return true;
	}
	
	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator> &x, const map<Key,T,Compare,Allocator> &y)
	{
		return !(x == y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<(const map<Key,T,Compare,Allocator> &x, const map<Key,T,Compare,Allocator> &y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}
    
	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator> &x, const map<Key,T,Compare,Allocator> &y)
	{
		return x < y || x == y;
	}

    template <class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key,T,Compare,Allocator> &x, const map<Key,T,Compare,Allocator> &y)
	{
		return !(x <= y);
	}

    template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator> &x, const map<Key,T,Compare,Allocator> &y)
	{
		return !(x < y);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key,T,Compare,Alloc> &x, map<Key,T,Compare,Alloc> &y)
	{
		map<Key,T,Compare,Alloc>	aux;

		aux = x;
		x = y;
		y = aux;
	}
};
		