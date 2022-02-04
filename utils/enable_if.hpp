/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:26:04 by rcabezas          #+#    #+#             */
/*   Updated: 2022/02/04 16:38:36 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template<bool Cond, class T = void>
	struct enable_if
	{
		
	};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
};
