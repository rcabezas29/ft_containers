/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:41:14 by rcabezas          #+#    #+#             */
/*   Updated: 2022/01/28 19:34:54 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct Iter
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	referece;
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class random_access_iterator : public ft::Iter<Category, T, Distance, Pointer, Reference>
	{
		public:
			random_access_iterator(void);
			random_access_iterator(const random_access_iterator &copy);
			random_access_iterator &operator=(const random_access_iterator &op);
			virtual	~random_access_iterator(void);

			bool	operator==(const random_access_iterator &b) const;
			bool	operator!=(const random_access_iterator &b) const;
	};
};
