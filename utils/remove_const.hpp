/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_const.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:29:12 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/24 18:32:29 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace	ft
{
	template<class T>
	struct remove_const
	{
		typedef T type;
	};
	
	template<class T>
	struct remove_const<const T>
	{
		typedef T type;
	};	
};