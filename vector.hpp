/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:52:17 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/26 17:56:36 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include "utils/iterators/random_access_iterator.hpp"
#include "utils/iterators/reverse_iterator.hpp"
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
			typedef std::ptrdiff_t											difference_type;
			typedef size_t													size_type;

		private:
			allocator_type		_allocator;
			size_type			_size;
			size_type			_capacity;
			pointer				_array;
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
					this->_allocator.construct(&this->_array[i], val);
				this->_size = n;
				this->_capacity = n;
				this->_begin = &this->_array[0];
				this->_end = &this->_array[this->_size];
			}
			
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
					: _allocator(alloc),
					_size(0),
					_capacity(0),
					_array(NULL)
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

			vector(const vector &copy)
			{
				*this = copy;
			}
			
			virtual ~vector(void) {}

			vector	&operator=(const vector &op)
			{
				if (this == &op)
					return *this;
				this->_allocator = op._allocator;
				this->_array = this->_allocator.allocate(op._capacity);
				this->_capacity = op._capacity;
				for (size_type i = 0; i < op.size(); i++)
					this->_allocator.construct(&this->_array[i], op._array[i]);
				this->_size = op._size;
				this->_begin = op._begin;
				this->_end = op._end;
				return *this;
			}

			//iterators
			iterator				begin(void)
			{
				return iterator(this->_array);
			}
			
			const_iterator			begin(void) const
			{
				return const_iterator(this->_array);
			}

			iterator				end(void)
			{
				return iterator(this->_array + this->_size);
			}

			const_iterator			end(void) const
			{
				return const_iterator(this->_array + this->_size);
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

			//capacity
			size_type	size(void) const { return this->_size; }

			size_type	max_size(void) const { return this->_allocator.max_size(); }

			void		resize(size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					for (size_type i = this->size(); i > n; i--)
						this->pop_back();
				}
				else if (n > this->_size)
				{
					for (size_type i = this->size(); i < n; i++)
						this->push_back(val);
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
							this->_allocator.construct(&new_array[i], this->_array[i]);
					}
					this->_array = new_array;
					this->_begin = &this->_array[0];
					this->_end = &this->_array[this->_size];
					this->_capacity = n;
				}
			}

			//element access
			reference			operator[](size_type n) { return this->_array[n]; }
			const_reference		operator[](size_type n) const { return this->_array[n]; }

			reference			at(size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return this->_array[n];
			}
			const_reference		at(size_type n) const
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return this->_array[n];
			}

			reference			front(void) { return this->_array[0]; }
			const_reference		front(void) const { return this->_array[0]; }

			reference			back(void) { return this->_array[this->_size - 1]; }
			const_reference		back(void) const { return this->_array[this->_size - 1]; }

			//modifiers
			template <class InputIterator>
			void			assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				this->clear();
				while (first != last)
				{
					this->push_back(*first);
					++first;
				}
			}

			void			assign(size_type n, const value_type &val)
			{
				this->clear();
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			void			push_back(const value_type &val)
			{
				if (this->_size == this->_capacity)
					this->reserve(this->_capacity > 0 ? this->_capacity * 2 : 1);
				this->_allocator.construct(this->end().get_pointer(), val);
				++this->_size;
			}

			void			pop_back(void)
			{
				this->_allocator.destroy(&this->_array[--this->_size]);
				--this->_end;
			}

			iterator		insert(iterator position, const value_type &val)
			{
				vector	temp(this->_capacity + 1, 0);
				iterator	it = this->begin();
				size_type	pos = 0;

				while (it != position)
				{
					temp[pos] = *it;
					it++;
					pos++;
				}
				size_type ret = pos;
				temp[pos++] = val;
				while (it != this->end())
				{
					temp[pos] = *it;
					it++;
					pos++;
				}
				this->swap(temp);
				for (size_type j = 0; j < temp.size(); j++)
					this->_allocator.destroy(&temp[j]);
				return this->begin() + ret;
			}
			

			void			insert(iterator position, size_type n, const value_type &val)
			{
				vector	temp(this->_capacity + (n - (this->_capacity - this->_size)), 0);
				iterator	it = this->begin();
				size_type	pos = 0;

				while (it != position)
				{
					temp[pos] = *it;
					it++;
					pos++;
				}
				while (n--)
				{
					temp[pos] = val;
					pos++;
					++this->_size;
				}
				while (it != this->end())
				{
					temp[pos] = *it;
					it++;
					pos++;
				}
				this->swap(temp);
				for (size_type j = 0; j < temp.size(); j++)
					this->_allocator.destroy(&temp[j]);
			}

			template <class InputIterator>
			void			insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				// distance creo que es de c17
				vector	temp(this->_capacity + (std::distance(first, last) - (this->_capacity - this->_size)), 0);
				iterator	it = this->begin();
				size_type	pos = 0;

				while (it != position)
				{
					temp[pos] = *it;
					it++;
					pos++;
				}
				while (first != last)
				{
					temp[pos] = *first;
					first++;
					pos++;
				}
				while (it != this->end())
				{
					temp[pos] = *it;
					it++;
					pos++;
				}
				this->swap(temp);
				for (size_type j = 0; j < temp.size(); j++)
					this->_allocator.destroy(&temp[j]);
			}

			iterator		erase(iterator position)
			{
				for (size_type i = 0; position + i + 1 != this->end(); i++)
				{
					this->_allocator.destroy(&(*(position + i)));
					this->_allocator.construct(&(*(position + i)), *(position + i + 1));
				}
				--this->_size;
				return position;
			}
			
			iterator		erase(iterator first, iterator last)
			{	
				for (size_type i = 0; last + i != this->end(); i++)
				{
					this->_allocator.destroy(&(*(first + i)));
					this->_allocator.construct(&(*(first + i)), *(last + i));
				}
				this->_size -= last - first;
				return first;
			}

			void			swap(vector &x)
			{
				vector	aux = x;
				aux._array = x._array;

				x = *this;
				x._array = this->_array;
				*this = aux;
				this->_array = aux._array;
			}

			void			clear(void)
			{
				while (this->_size > 0)
					this->pop_back();
			}

			allocator_type	get_allocator(void) const { return this->_allocator; }
	};

	template <typename T, typename U, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<U, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <typename T, typename U, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<U, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename U, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<U, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, typename U, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<U, Alloc> &rhs)
	{
		return lhs < rhs || lhs == rhs;
	}

	template <typename T, typename U, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<U, Alloc> &rhs)
	{
		return !(lhs <= rhs);
	}

	template <typename T, typename U, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<U, Alloc> &rhs)
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
