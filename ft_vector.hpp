/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:52:17 by rcabezas          #+#    #+#             */
/*   Updated: 2022/01/05 11:41:00 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

namespace ft
{
	template <typename T, class >
	class vector
	{
		private:
			T			*_array;
			int			_size;
			int			_capacity;
			allocator_t	_alloc;
			
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

			const_iterator			cbegin(void) const noexcept;

			const_iterator			cend(void) const noexcept;

			const_reverse_iterator	crbegin(void) const noexcept;

			const_reverse_iterator	crend(void) const noexcept;

			//capacity
			size_type	size(void) const;

			size_type	max_size(void) const;

			void		resize (size_type n, value_type val = value_type());

			size_type	capacity(void) const;

			bool		empty(void) const;

			void		reserve(size_type n);

			void		shrink_to_fit(void);

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
			void		assign(InputIterator first, InputIterator last);
			void		assign(size_type n, const value_type &val);

			void		push_back(const value_type &val);

			void		pop_back(void);

			iterator		insert(iterator position, const value_type &val);
			void			insert(iterator position, size_type n, const value_type &val);
			void			insert (iterator position, InputIterator first, InputIterator last);

			iterator		erase(iterator position);
			iterator		erase(iterator first, iterator last);

			void			swap(vector &x);

			void			clear(void);

			iterator		emplace(const_iterator position, Args&&... args);

			void			emplace_back(Args&&... args);

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
