/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:25:47 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/30 19:36:06 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace	ft
{
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;

		private:
			first_type	first;
			second_type	second;

		public:
			pair(void) : first(NULL), second(NULL) {}

			template <class U, class V>
			pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

			pair(const first_type &a, const second_type &b) : first(a), second(b) {}

			pair	&operator=(const pair &pr)
			{
				if (*this == pr)
					return *this;
				this->first = pr.first;
				this->second = pr.second;
				return *this;
			}

			bool	operator==(const pair<T1, T2> &b)
			{
				return this->first == b.first && this->second == b.second ? true : false;
			}

			bool	operator!=(const pair<T1, T2> &b)
			{
				return !(*this == b);
			}

			bool	operator<(const pair<T1, T2> &b)
			{
				if (this->first < b.first)
					return true;
				else if (this->first > b.first)
					return false;
				else if (this->second < b.second)
					return true;
				else
					return false;
					
			}

			bool	operator<=(const pair<T1, T2> &b)
			{
				return *this < b;
			}

			bool	operator>(const pair<T1, T2> &b)
			{
				return !(*this < b);
			}

			bool	operator>=(const pair<T1, T2> &b)
			{
				return !(*this < b);
			}

	};

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
};
