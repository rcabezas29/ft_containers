/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:05:31 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/11 21:13:36 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{
	template <typename T>
	class	bidirectional_iterator : public ft::Iter<std::random_access_iterator_tag, T>
	{
		public:
				
	};
};
