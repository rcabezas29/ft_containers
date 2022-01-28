/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:00:32 by rcabezas          #+#    #+#             */
/*   Updated: 2022/01/28 19:15:36 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>

namespace ft
{
	template <class Iter>
	struct iterator_traits
	{
		typedef Iter::difference_types	difference_type;
		typedef Iter::value_type		value_type;
		typedef void					pointer;
		typedef Iter::reference			referece;
		typedef Iter::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								referece;
		typedef std::random_access_iterator_tag	iterator_category;
	};
	
	template <class T>
	class iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						referece;
		typedef std::random_access_iterator_tag	iterator_category;
	};
};
