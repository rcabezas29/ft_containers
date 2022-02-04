/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:52:17 by rcabezas          #+#    #+#             */
/*   Updated: 2022/02/04 16:38:53 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "utils/iterator.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T													value_type;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_referece				const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef	typename random_access_iterator<value_type>			iterator;
			typedef	typename random_access_iterator<const value_type>	const_iterator;
			typedef	typename reverse_iterator<iterator>					reverse_iterator;
			typedef	typename reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;

		protected:
			allocator_type		_allocator;
			pointer				_array;
			size_type			_size;
			size_type			_capacity;

		public:
			//construction & destruction
			explicit	vector(const allocator_type &alloc = allocator_type())
			{
				this->_allocator = alloc;
				this->_array = NULL;
				this->_size = 0;
				this->_capacity = 0;
			}

			explicit	vector(size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type())
			{
				this->_allocator = alloc;
				this->_array = this->_allocator.allocate(n);
				for (int i = 0; i < n; i++)
					this->_array[i] = val;
				this->_capacity = n;
			}
			
			vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type())
					: _allocator(alloc),
					_array(nullptr),
					_size(0),
					_capacity(0)
			{
				while (first != last)
				{
					push_back(*first);
					first++;
				}
			}

			vector(const vector &copy) : _allocator(copy._allocator), 
				_size(copy.size()), _capacity(copy.capacity())
			{
				iterator	it(copy.begin());
				while (it != copy.end())
				{
					push_back(it);
					it++;
				}
			}
			
			~vector(void);

			vector	&operator=(const vector &op)
			{
				
			}

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
			size_type	size(void) const {return _size;}

			size_type	max_size(void) const {return _allocator.max_size();}

			void		resize (size_type n, value_type val = value_type());

			size_type	capacity(void) const {return _capacity}

			bool		empty(void) const {return (_size == 0)}

			void		reserve(size_type n);

			//element access
			reference			operator[](size_type n);
			const_reference		operator[](size_type n) const;

			reference			at(size_type n);
			const_reference		at(size_type n) const;

			reference			front(void  );
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

			void			clear(void)
			{
				while (this->_size != 0)
					pop_back();
			}

			allocator_type	get_allocator(void) const;
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
}
