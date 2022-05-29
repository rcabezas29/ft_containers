	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:47:46 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/30 19:36:50 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef	T			value_type;
			typedef Container	container_type;
			typedef	size_t		size_type;

		protected:
			container_type c;

		public:
			explicit stack(const container_type &ctnr = container_type())
			{
				this->c = ctnr;
			}
			~stack(void) {}

			bool empty(void) const { return c.empty(); }
			size_type size(void) const { return c.size(); }
			value_type &top(void) { return c.back(); }
			const value_type &top(void) const { return c.back(); }
			void push(const value_type& x) { c.push_back(x); }
			void pop(void) { c.pop_back(); }

			container_type	get_container(void) const { return this->c; }
	};

	template <class T, class Container>
	bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.get_container() == rhs.get_container();
	}

	template <class T, class Container>
	bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.get_container() != rhs.get_container();
	}

	template <class T, class Container>
	bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.get_container() < rhs.get_container();
	}

	template <class T, class Container>
	bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.get_container() <= rhs.get_container();
	}

	template <class T, class Container>
	bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.get_container() > rhs.get_container();
	}
	
	template <class T, class Container>
	bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.get_container() >= rhs.get_container();
	}
}
