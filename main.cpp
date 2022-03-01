/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:06:25 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/01 11:16:59 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"

int main (void)
{
	/*

		CONSTRUCTORS TESTS

	// ft::vector<int> first;                                // empty vector of ints
	//ft::vector<int> second (4,100);                       // four ints with value 100
	//ft::vector<int> third (second.begin(), second.end());  // iterating through second
	//ft::vector<int> fourth (second);                       // a copy of third

	int myints[] = {16,2,77,29};
	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of third are:";
	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	*/

	/*

		PUSH_BACK / POP_BACK TEST
	ft::vector<int> myvector;
	int	sum = 0;
	
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i);


	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	while (!myvector.empty())
  	{
    	sum += myvector.back();
   		myvector.pop_back();
  	}

	std::cout << "The elements of myvector add up to " << sum << '\n';
	std::cout << "SIZE: " << myvector.size() << " CAPACITY: " << myvector.capacity() << std::endl;
	*/
	

	/*

		ERASE TEST

	ft::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++)
		myvector.push_back(i);

	myvector.erase (myvector.begin() + 5);

	// erase the first 3 elements:
	myvector.erase (myvector.begin(), myvector.begin() + 3);

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	*/


	return 0;
}
