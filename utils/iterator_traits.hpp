/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:00:32 by rcabezas          #+#    #+#             */
/*   Updated: 2022/01/10 13:45:47 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
};
