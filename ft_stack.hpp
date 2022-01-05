/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:47:46 by rcabezas          #+#    #+#             */
/*   Updated: 2022/01/05 19:11:58 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

namespace ft
{
	template <class T, class Container = std::vector<T> >
	class stack
	{
		protected:
			Container c;

		public:
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;
			typedef Container container_type;

			explicit stack(const container_type &ctnr = container_type());
			~stack(void);

			bool empty(void) const {return c.empty();}
			size_type size(void) const {return c.size();}
			value_type &top(void) {return c.back();}
			const value_type &top(void) const {return c.back();}
			void push(const value_type& x) {c.push_back(x);}
			void pop(void) {c.pop_back();}
	};
};