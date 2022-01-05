/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:47:46 by rcabezas          #+#    #+#             */
/*   Updated: 2022/01/05 11:56:47 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

template <class T, class Container = std::vector<T> >
class stack
{
	protected:
		Container c;

	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;
		typedef typename Container::size_type size_type;
		typedef Container container_type;

		explicit stack(const container_type &ctnr = container_type());
		~stack(void);

		bool empty(void) const {return c.empty()}
		size_type size(void) const {return c.size()}
		reference top(void) {return c.back()}
		const_reference top(void) const {return c.back()}
		void push(const value_type& x) {c.push_back(x)}
		void push(value_type&& x) {c.push_back(std::move(x))}
		template <class... Args> void emplace(Args&&... args) {c.emplace_back(std::forward<Args>(args)...)}
		void pop(void) {c.pop_back()}
		void swap(stack& s) noexcept(noexcept(swap(c, s.c))) {std::swap(c, s.c)}
};