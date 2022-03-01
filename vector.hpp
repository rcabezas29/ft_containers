/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:52:17 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/01 12:21:10 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include "utils/iterator.hpp"
#include "utils/lexicographical_compare.hpp"
#include "utils/is_integral.hpp"
#include "utils/enable_if.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef	typename ft::random_access_iterator<value_type>			iterator;
			typedef	typename ft::random_access_iterator<value_type>			const_iterator;
			typedef	typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef ptrdiff_t												difference_type;
			typedef size_t													size_type;

		private:
			allocator_type		_allocator;
			pointer				_array;
			size_type			_size;
			size_type			_capacity;
			pointer				_end;
			pointer				_begin;

		public:
			//construction & destruction
			explicit	vector(const allocator_type &alloc = allocator_type())
			{
				this->_allocator = alloc;
				this->_array = NULL;
				this->_size = 0;
				this->_capacity = 0;
				this->_end = this->_array;
				this->_begin = this->_array;
			}

			explicit	vector(size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type())
			{
				this->_allocator = alloc;
				this->_array = this->_allocator.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_array[i] = val;
				this->_size = n;
				this->_capacity = n;
				this->_begin = &this->_array[0];
				this->_end = &this->_array[this->_size];
			}
			
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
					: _allocator(alloc),
					_array(NULL),
					_size(0),
					_capacity(0)
			{
				InputIterator	it = first;

				while (it++ != last)
					this->_capacity++;

				this->_array = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; i < this->_capacity; i++)
				{
					this->_allocator.construct(&this->_array[i], *first++);
					++this->_size;
				}
				this->_begin = &this->_array[0];
				this->_end = &this->_array[this->_size];
			}

			vector(const vector &copy) : _allocator(copy._allocator), 
				_size(copy.size()), _capacity(copy.capacity())
			{
				*this = copy;
			}
			
			virtual ~vector(void)
			{
				this->_allocator.destroy(this->_array);
			}

			vector	&operator=(const vector &op)
			{
				if (this == &op)
					return *this;
				this->_allocator = op._allocator;
				this->_array = this->_allocator.allocate(op._capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_array[i] = op._array[i];
				this->_capacity = op._capacity;
				this->_size = op._size;
				return *this;
			}

			//iterators
			iterator				begin(void)
			{
				iterator	it(&this->_array[0]);
				return it;
			}
			
			const_iterator			begin(void) const
			{
				const_iterator	it(&this->_array[0]);
				return it;
			}

			iterator				end(void)
			{
				//iterator	it(&this->_array[this->_size]);
				return iterator(&this->_array[this->_size]);
			}

			const_iterator			end(void) const
			{
				const_iterator	it(&this->_array[this->_size]);
				return it;
			}

			reverse_iterator		rbegin(void)
			{
				reverse_iterator	it(&this->_array[0]);
				return it;
			}
			
			const_reverse_iterator	rbegin(void) const
			{
				const_reverse_iterator	it(&this->_array[0]);
				return it;
			}

			reverse_iterator		rend(void)
			{
				reverse_iterator	it(&this->_array[this->_size]);
				return it;
			}

			const_reverse_iterator	rend(void) const
			{
				const_reverse_iterator	it(&this->_array[this->_size]);
				return it;
			}

			//capacity
			size_type	size(void) const {return this->_size;}

			size_type	max_size(void) const {return this->_allocator.max_size();}

			void		resize(size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					for (iterator it = this->end(); this->size() > n; it--)
						this->erase(it);
				}
				else if (n > this->_size)
				{
					for (iterator it = this->end(); this->size() <= n; it++)
						this->insert(it, val);
				}
				this->_size = n;
			}

			size_type	capacity(void) const { return this->_capacity; }

			bool		empty(void) const { return (this->_size == 0); }

			void		reserve(size_type n)
			{
				if (this->_capacity < n)
				{
					pointer	new_array;

					new_array = this->_allocator.allocate(n);
					if (this->_size > 0)
					{
						for (size_type i = 0; i < this->_size; i++)
							new_array[i] = this->_array[i];
					}
					this->_array = new_array;
					this->_begin = &this->_array[0];
					this->_begin = &this->_array[this->_size];
					this->_capacity = n;
				}
			}

			//element access
			reference			operator[](size_type n) { return this->_array[n]; }
			const_reference		operator[](size_type n) const { return this->_array[n]; }

			reference			at(size_type n) { return this->_array[n]; }
			const_reference		at(size_type n) const { return this->_array[n]; }

			reference			front(void) { return this->_array[0]; }
			const_reference		front(void) const { return this->_array[0]; }

			reference			back(void) { return this->_array[this->_size - 1]; }
			const_reference		back(void) const { return this->_array[this->_size - 1]; }

			//modifiers
			template <class InputIterator>
			void			assign(InputIterator first, InputIterator last)
			{
				difference_type	i;
				T	*tmp = this->_array;
				const value_type &val = value_type();
				

				i = 0;
				while (first++ != last)
				{
					this->_allocator.construct(tmp, val);
					tmp++;
					i++;
				}
				this->_size = i;
			}

			void			assign(size_type n, const value_type &val)
			{
				iterator	it = this->begin();

				for (int i = 0; i < n; i++)
					this->_allocator.construct(it++, val);
			}

			void			push_back(const value_type &val)
			{
				if (this->_size == this->_capacity)
				{
					this->reserve(this->_capacity > 0 ? this->_capacity * 2 : 1);
				}
				this->_allocator.construct(this->_array + this->_size, val);
				++this->_size;
			}

			void			pop_back(void)
			{
				this->_allocator.destroy(&this->_array[--this->_size]);
				--this->_end;
			}

			iterator		insert(iterator position, const value_type &val)
			{
				iterator	it = this->begin();
				size_type	pos = 0;
				size_type	i = 0;
				bool		inserted = false;
				value_type	aux;

				if (this->_capacity == this->_size)
				{
					pointer	aux_array = this->_array;

					this->_allocator.deallocate(this->_array, this->_capacity);
					this->_array = this->_allocator.allocate(this->_capacity > 0 ? this->_capacity * 2 : 1);
					for (size_type j = 0; j < this->_size; j++)
						this->_array[j] = aux_array[j];
					this->_capacity = this->_capacity > 0 ? this->_capacity * 2 : 1;
				}
				while (i < this->_size + 1)
					{
						aux = this->_array[i];
						if (it == position)
						{
							this->_array[i] = val;
							inserted = true;
							pos = i;
						}
						i++;
						if (inserted == true)
							this->_array[i] = aux;
					}
				++this->_size;
				return iterator(this->_array + pos);
			}

			void			insert(iterator position, size_type n, const value_type &val)
			{
				while (n-- > 0)
					insert(position++, val);
			}

			template <class InputIterator>
			void			insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				while (first++ != last)
					this->insert(position++, *first);
			}

			iterator		erase(iterator position)
			{
				iterator	it = this->begin();
				while (it != position)
					it++;
				this->_allocator.destroy(&(*it));
				this->_size--;
				return it;
			}
			
			iterator		erase(iterator first, iterator last)
			{
				iterator	it = first;

				while (it != last)
				{
					this->_allocator.destroy(&(*(it - 1)));
					it++;
					this->_size--;
				}
				return &(*(it - 1));
			}

			void			swap(vector &x)
			{
				vector	aux(*this);
				*this = x;
				x = aux;
			}

			void			clear(void)
			{
				while (this->_size != 0)
					pop_back();
			}

			allocator_type	get_allocator(void) const;
	};

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		ft::random_access_iterator<T>	lit = lhs.begin();
		ft::random_access_iterator<T>	rit = rhs.begin();

		while (lit != lhs.end())
		{
			if (*lit != *rit || rit == rhs.end())
				return false;
			++lit;
			++rit;
		}
		if (rit != rhs.end())
			return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare<ft::random_access_iterator<T>, ft::random_access_iterator<T> >(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return lhs < rhs || lhs == rhs;
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs <= rhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		vector<T, Alloc>	aux;

		aux = x;
		x = y;
		y = aux;
	}
}
