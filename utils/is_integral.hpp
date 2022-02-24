/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:27:24 by rcabezas          #+#    #+#             */
/*   Updated: 2022/02/23 12:54:16 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{
	template <class T>
	struct is_integral
	{
		static const bool	value = false;
	};

	template <>
	struct	is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<char16_t>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<char32_t>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<wchar_t>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<signed char>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<short int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long long int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<unsigned char>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<unsigned short int>
	{
		static const bool value = true;
	};
	
	template <>
	struct	is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<unsigned long int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<unsigned long long int>
	{
		static const bool value = true;
	};
};
