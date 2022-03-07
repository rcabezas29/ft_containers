/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:06:25 by rcabezas          #+#    #+#             */
/*   Updated: 2022/03/07 15:22:56 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include "vector.hpp"

int main (void)
{
	/*

		CONSTRUCTORS TESTS

	ft::vector<int> first;                                // empty vector of ints
	ft::vector<int> second (4,100);                       // four ints with value 100
	ft::vector<int> third (second.begin(), second.end());  // iterating through second
	ft::vector<int> fourth (second);                       // a copy of third

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

	/*

		INSERT TEST
		
	ft::vector<int>				myvector(3,100);
	ft::vector<int>::iterator	it;

	it = myvector.begin();
	it = myvector.insert(it, 200);

	myvector.insert(it, 2, 300);


	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int>	anothervector(2,400);
	// myvector.insert(it + 2, anothervector.begin(), anothervector.end());

	// int myarray [] = {501, 502, 503};
	// myvector.insert(myvector.begin(), myarray, myarray + 3);

	std::cout << "MYVEC BEGIN: " << *(myvector.begin() + 4) << std::endl;

	myvector.insert(myvector.begin() + 4, 5);
	
	std::cout << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
	*/

	/*
		ASSIGN TEST


	ft::vector<int>	first;
	ft::vector<int>	second;
	ft::vector<int>	third;

	first.assign (7,100);             // 7 ints with a value of 100

	ft::vector<int>::iterator it;
	it = first.begin() + 1;

	second.assign (it, first.end() - 1); // the 5 central values of first

	int myints[] = {1776, 7, 4};
	third.assign(myints, myints + 3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';

	first.assign(2, 4);
	std::cout << "CHECK OVERWRITE SIZE " << first.size() << " should be 2" << std::endl;
	*/

	/*

		AT TEST
	
	ft::vector<int>	myvector(10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i =  0; i < myvector.size(); i++)
		myvector.at(i)=i;

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';

	try
	{
		std::cout << "OUT OF RANGE: " << myvector.at(15) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	*/


	/*

		COPY & ASSIGNMENT CONSTRUCTOR TEST
	ft::vector<int> vct(5);
	ft::vector<int>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	ft::vector<int> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	ft::vector<int> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;

	std::cout << "* VCT *" << std::endl;
	for (size_t i = 0; i != vct.size(); i++)
		std::cout << vct[i] << " ";
	std::cout << "\n";

	std::cout << "* RANGE *" << std::endl;
	for (size_t i = 0; i != vct_range.size(); i++)
		std::cout << vct_range[i] << " ";
	std::cout << "\n";
	
	std::cout << "* COPY *" << std::endl;
	for (size_t i = 0; i != vct_copy.size(); i++)
		std::cout << vct_copy[i] << " ";
	std::cout << "\n";

	std::cout << "VCT = COPY" << std::endl;
	vct = vct_copy;
	std::cout << "COPY = RANGE" << std::endl;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	for (size_t i = 0; i != vct.size(); i++)
		std::cout << vct[i] << " ";
	std::cout << "\n";

	for (size_t i = 0; i != vct_range.size(); i++)
		std::cout << vct_range[i] << " ";
	std::cout << "\n";
	
	for (size_t i = 0; i != vct_copy.size(); i++)
		std::cout << vct_copy[i] << " ";
	std::cout << "\n";
	*/

	ft::vector<int> foo(3, 15);
	ft::vector<int> bar(5, 42);
	
	ft::vector<int>::const_iterator it_foo = foo.begin();
	ft::vector<int>::const_iterator it_bar = bar.begin();

	foo.swap(bar);

	std::cout << "Iterator validity:" << std::endl;

	std::cout << "IT_FOO: " << *it_foo << " " << &it_foo << std::endl;
	std::cout << "IT_BAR: " << *it_bar << " " << &it_bar << std::endl;

	ft::vector<int>::const_iterator foo_check = foo.begin();
	ft::vector<int>::const_iterator bar_check = bar.begin();
	
	std::cout << "bar begin: " << *bar_check << " " << &bar_check << std::endl;
	std::cout << "foo begin: " << *foo_check << " " << &foo_check << std::endl;

	
	std::cout << (it_foo == bar_check) << std::endl;
	std::cout << (it_bar == foo_check) << std::endl;

	return 0;
}
