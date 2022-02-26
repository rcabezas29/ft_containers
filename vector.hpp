/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:52:17 by rcabezas          #+#    #+#             */
/*   Updated: 2022/02/26 13:57:26 by rcabezas         ###   ########.fr       */
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
			typedef	typename ft::random_access_iterator<const value_type>	const_iterator;
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
				this->_end = NULL;
				this->_begin = NULL;
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
				this->_begin = &this->_array[this->_size];
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
					this->_size++;
				}
				this->_begin = &this->_array[0];
				this->_begin = &this->_array[this->_size];
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
				iterator	it(&this->_array[this->_size]);
				return it;
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
				this->_allocator.deallocate(this->_array);
				this->_array = this->_allocator.allocate(n, val);
				this->_size = n;
			}

			size_type	capacity(void) const { return this->_capacity; }

			bool		empty(void) const { return (this->_size == 0); }

			void		reserve(size_type n) { this->_array = this->_allocator.allocate(n); }

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
				if (this->_capacity > this->_size)
				{
					this->_allocator.construct(this->_end, val);
					++this->_size;
				}
				else
				{
					this->_array = this->_allocator.allocate(this->_capacity * 2);
					this->_allocator.construct(this->_end, val);
					++this->_size;
					this->_capacity *= 2;
				}
			}

			void			pop_back(void)
			{
				this->_allocator.destruct(this->_array[--this->_size]);
				--this->_end;
			}

			iterator		insert(iterator position, const value_type &val)
			{
				size_type	i = 0;
				if (this->_capacity < this->_size + 1)
				{
					pointer	new_array = this->_allocator.allocate(this->_capacity * 2);
					while (this->_array[i])
					{
						new_array[i] = this->_array[i];
						i++;
					}
					this->_array = new_array;
				}
				else
				{
					if (position == this->end())
						this->_allocator.construct(this->_end, val);
					else
					{
						iterator	it = this->begin();

						while (it++ != position)
							i++;
						value_type	aux = this->_array[i];
						this->_array[i] = val;
						while (it++ != this->end())
						{
							this->_array[++i] = aux;
							aux = this->_array[i + 1];
						}
					}
				}
				iterator ret(this->_array + i);
				return ret;
			}

			void			insert(iterator position, size_type n, const value_type &val)
			{
				while (n-- > 0)
					insert(position++, val);
			}

			template <class InputIterator>
			void			insert(iterator position, InputIterator first, InputIterator last)
			{
				while (first++ != last)
					this->insert(position++, first);
			}

			iterator		erase(iterator position)
			{
				iterator	it = this->begin();
				while (it != position)
					it++;
				it++;
				this->_allocator.destroy(*(it - 1));
				this->_size--;
				return it;
			}
			
			iterator		erase(iterator first, iterator last)
			{
				iterator	it = first;

				while (it != last)
				{
					this->_allocator.destroy(*(it - 1));
					it++;
					this->_size--;
				}
				return *(it + 1);
			}

			void			swap(vector &x);

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
		ft::random_access_iterator<T>	lit = lhs.first();
		ft::random_access_iterator<T>	rit = rhs.first();

		while (lit != lhs.end())
		{
			if (*lit != *rit || rit == rhs.last())
				return false;
			++lit;
			++rit;
		}
		if (rit != rhs.last())
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
		return ft::lexicographical_compare<ft::random_access_iterator, ft::random_access_iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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
