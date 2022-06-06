/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:57:36 by rcabezas          #+#    #+#             */
/*   Updated: 2022/06/06 12:03:02 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace	ft
{
	template<class It>
	typename ft::iterator_traits<It>::difference_type	distance(It first, It last)
	{
		typename ft::iterator_traits<It>::difference_type result = 0;
		while (first != last)
		{
			++first;
			++result;
		}
		return result;
	}
};
