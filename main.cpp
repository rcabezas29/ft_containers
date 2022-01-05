/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:06:25 by rcabezas          #+#    #+#             */
/*   Updated: 2022/01/05 19:18:03 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.hpp"

int	main(void)
{
	ft::stack<int, std::vector<int, std::allocator<int> > >	stck;

	for (int i = 1; i <= 10; i++)
		stck.push(i);

	while (!stck.empty())
	{
		std::cout << stck.top() << std::endl;
		stck.pop();
	}

	return (0);
}
