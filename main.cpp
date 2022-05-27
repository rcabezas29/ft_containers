/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:06:25 by rcabezas          #+#    #+#             */
/*   Updated: 2022/05/27 11:42:57 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include "utils/pair.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"
#include "utils/binary_tree.hpp"

#define NAMESPACE ft

int main (void)
{
	std::cout << "\n\n--------------------------------" << std::endl;
	std::cout << "------------STACK TEST------------" << std::endl;
	std::cout << "--------------------------------\n\n" << std::endl;

	NAMESPACE::stack<int>	stk;

	std::cout << "EMPTY? " << (stk.empty() == true ? "yes" : "no") << std::endl;

	std::cout << "Pulling" << std::endl;

	stk.push(1);
	stk.push(2);
	stk.push(4);
	stk.push(3);
	stk.push(5);
	stk.push(9);

	std::cout << stk.size() << std::endl;;

	stk.pop();
	stk.pop();
	std::cout << "POPING...." << std::endl;

	std::cout << "SIZE: " << stk.size() << std::endl;

	std::cout << "EMPTY? " << (stk.empty() == true ? "yes" : "no")  << std::endl;

	std::cout << "The top is: " << stk.top() << std::endl;

	stk.pop();

	std::cout << "And after: ... " << stk.top() << std::endl;



	std::cout << "\n\n--------------------------------" << std::endl;
	std::cout << "------------MAP TEST------------" << std::endl;
	std::cout << "--------------------------------\n\n" << std::endl;

	NAMESPACE::map<int, std::string>	mp;

	mp[1] = "abc";
	mp[17] = "santana";

	mp.insert(NAMESPACE::make_pair(5, "asdf"));
	mp.insert(NAMESPACE::make_pair(5, "asdf"));

	NAMESPACE::map<int, std::string>	mp_copy(mp);

	/*
		MAP SIZE
		
	NAMESPACE::map<int, std::string>	m;

	std::cout << "M is empty? " << m.empty() << std::endl;
	std::cout << "M SIZE " << m.size() << std::endl;
	std::cout << "M MAX_SIZE " << m.max_size() << std::endl;

	m[1] = "hola";
	m[2] = "adios";
	m[3] = "que tal";
	m[4] = "asdlkfj";
	m[5] = "skdfalsd";

	for (NAMESPACE::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;

	m.clear();

	for (NAMESPACE::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;

	std::cout << "M is empty? " << m.empty() << std::endl;
	std::cout << "M SIZE " << m.size() << std::endl;
	std::cout << "M MAX_SIZE " << m.max_size() << std::endl;

	*/

	

	/*
		MAP CONSTRUCTION
		
	std::list<NAMESPACE::pair<int, int> > lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(NAMESPACE::make_pair(lst_size - i, i));

	NAMESPACE::map<int, int>	mp(lst.begin(), lst.end());

	for (ft::map<int, int>::iterator i = mp.begin(); i != mp.end(); ++i)
		std::cout << i->first << " => " << i->second << '\n';
	
	NAMESPACE::map<int, int>::iterator it = mp.begin(), ite = mp.end();

	NAMESPACE::map<int, int> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;

	for (ft::map<int, int>::iterator i = mp_range.begin(); i != mp_range.end(); ++i)
		std::cout << i->first << " => " << i->second << '\n';
	
	it = mp.begin(); ite = --(--mp.end());
	NAMESPACE::map<int, int> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;

	for (ft::map<int, int>::iterator i = mp_copy.begin(); i != mp_copy.end(); ++i)
		std::cout << i->first << " => " << i->second << '\n';
		*/


	
	/*

		MAP BEGIN / END / RBEGIN / REND
	
	std::list<NAMESPACE::pair<int, int> > lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(NAMESPACE::make_pair(lst_size - i, i));


	NAMESPACE::map<int, int>	mp(lst.begin(), lst.end());

	std::cout << "BEGIN: " << mp.begin()->first << " => " << mp.begin()->second << std::endl;
	NAMESPACE::map<int, int>::iterator	it = mp.end();
	--it;
	std::cout << "END -1: " << it->first << " => " << it->second << std::endl;

	NAMESPACE::map<int, int>::reverse_iterator	rit = mp.rbegin();
	std::cout << "RBEGIN: " << rit->first << " => " << rit->second << std::endl;

	NAMESPACE::map<int, int>::reverse_iterator	rite = mp.rend();
	std::cout << "REND -1: " << rite->first << " => " << rite->second << std::endl;

	*/

	



	/* 
		CONST ITERATOR CREATION
		
	
	std::map<int, std::string>	m;

	m[1] = "hola";
	m[2] = "adios";
	m[3] = "que tal";

	const std::map<int, std::string>	cm(m);

	for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	for (std::map<int, std::string>::reverse_iterator it = m.rbegin(); it != m.rend(); it++)
		std::cout << it->first << " => " << it->second << '\n';

	std::map<int, std::string>::const_iterator cit = cm.begin();
	std::cout << cit->first << " => " << cit->second << '\n';
	
	//std::cout << (it != ite) << std::endl;
	
	*/

	/*
		MAP BOUNDS

	NAMESPACE::map<char,int>			mymap;
	NAMESPACE::map<char,int>::iterator	itlow, itup;

	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;

	itlow = mymap.lower_bound('b');  // itlow points to b
	itup = mymap.upper_bound('d');   // itup points to e (not d!)

	std::cout << "BOUNDS " << std::endl;
	std::cout << itlow->first << " => " << itlow->second << '\n';
	std::cout << itup->first << " => " << itup->second << '\n';
	std::cout << "---------------------------------------- " << std::endl;

	NAMESPACE::map<char,int>::const_iterator	citlow, citup;

	citlow = mymap.lower_bound(-10);
	citup = mymap.upper_bound(-10);


	std::cout << citlow->first << " => " << citlow->second << '\n';
	std::cout << citup->first << " => " << citup->second << '\n';
	std::cout << "---------------------------------------- " << std::endl;

	// mymap.erase(itlow, itup);        // erases [itlow,itup)                                       error: erasing

	// print content:
	for (NAMESPACE::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

		*/

	/*
		Map empty
	
	ft::map<char, int> first;

	std::cout << "Empty? " << first.empty() << std::endl;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	std::cout << "Empty? " << first.empty() << std::endl;

	*/
	/*
		MAP iterator

	ft::map<char, int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	ft::map<char, int>::iterator it = first.begin();
	ft::map<char, int>::iterator ite = first.end();
	
	it++;
	it++;

	if (it == ite) {
		std::cout << "son iguales" << std::endl;
	} else {
		std::cout << "no son iguales" << std::endl;
	}
	

	for (ft::map<char, int>::iterator it = first.begin(); it != first.end(); it++)
		std::cout << (*it).first << std::endl;
		
		*/

	/*
		MAP construction

	ft::map<char, int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	ft::map<char,int> second(first.begin(), first.end());

	ft::map<char,int> third(second);

	ft::map<char,int>	fourth;

	std::cout << "Printing first: Size = " << first.size() << std::endl;
	for (ft::map<char, int>::iterator it = first.begin(); it != first.end(); it++)
		std::cout << (*it).first << " => " << (*it).second << std::endl;

	std::cout << "---------------------------------------------------" << std::endl;

	std::cout << "Printing second: Size = " << second.size() << std::endl;
	for (ft::map<char, int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << (*it).first << " => " << (*it).second << std::endl;

	std::cout << "---------------------------------------------------" << std::endl;

	std::cout << "Printing third: Size = " << third.size() << std::endl;
	for (ft::map<char, int>::iterator it = third.begin(); it != third.end(); it++)
		std::cout << (*it).first << " => " << (*it).second << std::endl;

	std::cout << "---------------------------------------------------" << std::endl;

	std::cout << "Printing fourth: Size = " << fourth.size() << std::endl;
	for (ft::map<char, int>::iterator it = fourth.begin(); it != fourth.end(); it++)
		std::cout << (*it).first << " => " << (*it).second << std::endl;
		*/

	/*
		MAP/operator=
	
	ft::map<char, int> first;
	ft::map<char, int> second;

	first['x'] = 8;
	first['y'] = 16;
	first['z'] = 32;

	second = first;
	first = ft::map<char,int>();

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "Size of second: " << second.size() << '\n';

	*/

	/*
		R/B TREE TEST
	
	ft::binary_tree<int, std::less<int>, std::allocator<int> >	a('a');

	a.insert_node('b');
	a.insert_node('c');
	a.insert_node('d');
	a.insert_node('e');
	// a.insert_node(2);
	// a.insert_node(8);
	// a.insert_node(10);
	// a.insert_node(7);
	// a.insert_node(9);

	// a.delete_val(2);
	// a.delete_val(3);

	std::cout << a._root->value << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << a._root->lhs->value << " ";
	std::cout << a._root->rhs->value << std::endl;
	std::cout << "----------------------------" << std::endl;
	// std::cout << a._root->lhs->lhs->value << " ";
	// std::cout << a._root->lhs->rhs->value << " ";
	std::cout << a._root->rhs->lhs->value << " ";
	std::cout << a._root->rhs->rhs->value << std::endl;
	std::cout << "----------------------------" << std::endl;
	
	// std::cout << a._root->lhs->lhs->lhs->value << " ";
	// std::cout << a._root->lhs->lhs->rhs->value << " ";
	// std::cout << a._root->lhs->rhs->lhs->value << " ";
	// std::cout << a._root->lhs->rhs->rhs->value << " ";
	// std::cout << a._root->rhs->lhs->lhs->value << " ";
	// std::cout << a._root->rhs->lhs->rhs->value << " ";
	// std::cout << a._root->rhs->rhs->lhs->value << " ";
	// std::cout << a._root->rhs->rhs->rhs->value << " ";
	*/

	/*
		R/B Tree

	ft::binary_tree<int, std::less<int>, std::allocator<int> >	a(1);

	a.insert_node(2);
	a.insert_node(3);
	a.insert_node(4);
	a.insert_node(5);
	a.insert_node(6);
	a.insert_node(7);
	a.insert_node(8);
	a.insert_node(9);
	a.insert_node(10);
	a.insert_node(11);
	a.insert_node(12);
	a.insert_node(13);
	a.insert_node(14);
	a.insert_node(15);
	a.insert_node(16);
	a.insert_node(17);
	a.insert_node(18);
	a.insert_node(19);

	a.delete_val(5);
	a.delete_val(12);
	a.delete_val(16);
	a.delete_val(3);
	a.delete_val(8);
	a.delete_val(7);

	std::cout << a._root->value << "(" << a._root->color << ")" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << a._root->lhs->value << "(" << a._root->lhs->color << ")" << " ";
	std::cout << a._root->rhs->value << "(" << a._root->rhs->color << ")" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << a._root->lhs->lhs->value << "(" << a._root->lhs->lhs->color << ")" << " ";
	std::cout << a._root->lhs->rhs->value << "(" << a._root->lhs->rhs->color << ")" << " ";
	std::cout << a._root->rhs->lhs->value << "(" << a._root->rhs->rhs->color << ")" << " ";
	std::cout << a._root->rhs->rhs->value << "(" << a._root->rhs->rhs->color << ")" << std::endl;
	std::cout << "----------------------------" << std::endl;
	// std::cout << a._root->lhs->lhs->lhs->value << "(" << a._root->lhs->lhs->lhs->color << ")" << " ";
	// std::cout << a._root->lhs->lhs->rhs->value << "(" << a._root->lhs->lhs->rhs->color << ")" << " ";
	// std::cout << a._root->lhs->rhs->lhs->value << "(" << a._root->lhs->rhs->lhs->color << ")" << " ";
	// std::cout << a._root->lhs->rhs->rhs->value << "(" << a._root->lhs->rhs->rhs->color << ")" << " ";
	std::cout << a._root->rhs->lhs->lhs->value << "(" << a._root->rhs->lhs->lhs->color << ")" << " ";
	std::cout << a._root->rhs->lhs->rhs->value << "(" << a._root->rhs->lhs->rhs->color << ")" << " ";
	std::cout << a._root->rhs->rhs->lhs->value << "(" << a._root->rhs->rhs->lhs->color << ")" << " ";
	std::cout << a._root->rhs->rhs->rhs->value << "(" << a._root->rhs->rhs->rhs->color << ")" << std::endl;

	*/
	/*

		REV ITER TEST
	ft::vector<int> vct2(5, 5);

	ft::vector<int>::reverse_iterator rit = vct2.rbegin();
	ft::vector<int>::reverse_iterator rite = vct2.rend();

	while (rit != rite)
	{
		std::cout << *rit << std::endl;
		rit++;
	}

	
	
	ft::vector<int> myvector;
	for (int i = 0; i < 10; i++)
		myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

	std::cout << "RBEGIN = "<< *rev_iterator << std::endl;

	rev_iterator += 2;
	
	std::cout << "The third element from the end is: " << *rev_iterator << '\n';

	rev_iterator -= 1;

	std::cout << "The second element from the end is: " << *rev_iterator << '\n';

	ft::reverse_iterator<iter_type> check_iterator = rev_iterator - 1;

	std::cout << "The first element from the end is: " << *check_iterator << '\n';

	check_iterator = check_iterator + 3;

	std::cout << "The fourth element from the end is: " << *check_iterator << '\n';

	check_iterator -= 2;

	std::cout << "The second element from the end is: " << *check_iterator << '\n';

	std::cout << "----------------------------------------" << std::endl;

	std::cout << "       RELATIONAL OPERATOR CHECK         " << std::endl;

	std::cout << "----------------------------------------" << std::endl;

	std::cout << std::boolalpha;

	std::cout << (rev_iterator < check_iterator) << " - Should be false" << std::endl;
	std::cout << (rev_iterator <= check_iterator) << " - Should be true" << std::endl;
	std::cout << (rev_iterator > check_iterator) << " - Should be false" << std::endl;
	std::cout << (rev_iterator >= check_iterator) << " - Should be true" << std::endl;

	++check_iterator;

	std::cout << "--SECOND PART--" << std::endl;

	std::cout << "CHECK IT --> " << *check_iterator << std::endl;

	std::cout << (rev_iterator < check_iterator) << " - Should be true" << std::endl;
	std::cout << (rev_iterator <= check_iterator) << " - Should be true" << std::endl;
	std::cout << (rev_iterator > check_iterator) << " - Should be false" << std::endl;
	std::cout << (rev_iterator >= check_iterator) << " - Should be false" << std::endl;

	check_iterator = check_iterator - 2;

	std::cout << "--THIRD PART--" << std::endl;

	std::cout << "CHECK IT --> " << *check_iterator << std::endl;

	std::cout << (rev_iterator < check_iterator) << " - Should be false" << std::endl;
	std::cout << (rev_iterator <= check_iterator) << " - Should be false" << std::endl;
	std::cout << (rev_iterator > check_iterator) << " - Should be true" << std::endl;
	std::cout << (rev_iterator >= check_iterator) << " - Should be true" << std::endl;

	std::cout << "--FOURTH PART--" << std::endl;

	++check_iterator;

	std::cout << "CHECK IT --> " << *check_iterator << std::endl;

	std::cout << (rev_iterator + 2 < check_iterator) << " - Should be false" << std::endl;
	std::cout << (rev_iterator - 1 <= check_iterator) << " - Should be true" << std::endl;
	std::cout << (rev_iterator + 5 > check_iterator) << " - Should be true" << std::endl;
	std::cout << (rev_iterator >= check_iterator) << " - Should be true" << std::endl;

	*/

	/*

		CONSTRUCTORS TESTS
	ft::vector<int> first(1000000000);                                // empty vector of ints

	std::cout << first.max_size() << std::endl;
	ft::vector<int> second (4,100);                       // four ints with value 100
	ft::vector<int> third (second.begin(), second.end());  // iterating through second
	ft::vector<int> fourth (second);                       // a copy of third

	int myints[] = {16,2,77,29};
	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
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

	myvector.erase(myvector.begin() + 5);

	// erase the first 3 elements:
	myvector.erase(myvector.begin(), myvector.begin() + 3);

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	*/

	/*

		INSERT TEST
		
	ft::vector<int>				myvector(3, 100);
	ft::vector<int>::iterator	it;

	it = myvector.begin();
	it = myvector.insert(it, 200);

	for (size_t i = 0; i < myvector.size(); i++)
		std::cout << myvector[i] << " ";
	std::cout << "\n" << std::endl;

	myvector.insert(it, 2, 300);

	for (size_t i = 0; i < myvector.size(); i++)
		std::cout << myvector[i] << " ";
	std::cout << "\n" << std::endl;

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int>	anothervector(2, 400);
	myvector.insert(it + 2, anothervector.begin(), anothervector.end());

	for (size_t i = 0; i < myvector.size(); i++)
		std::cout << myvector[i] << " ";
	std::cout << "\n" << std::endl;

	int myarray [] = {501, 502, 503};
	myvector.insert(myvector.begin(), myarray, myarray + 3);
	
	std::cout << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
		std::cout << " " << *it;
	std::cout << "\n";
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

	/*
		REVERSE ITERATOR

	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::reverse_iterator it = vct.rbegin();
	ft::vector<int>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
	 	it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	for (size_t i = 0; i < vct.size(); i++)
		std::cout << vct[i] << " ";
	*/

	return 0;
}
