#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
// find common elements of type T and returns set with only elements containg both 
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T> setI;
	for(typename std::set<T>::iterator it1 = s1.begin(); it1 != s1.end(); ++it1){
    if(s2.find(*it1) != s2.end()){
			setI.insert(*it1); 
		}
	}
	return setI;
}

template <typename T> 
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T> setU;
	// iterators for both sets
	typename std::set<T>::iterator it1; // use typename to clarify that iterator is a type
	typename std::set<T>::iterator it2;
  // insert set
	for(it1 = s1.begin(); it1 != s1.end(); ++it1){
		setU.insert(*it1);
	}
  // adds unique elements from s2 to setU
	for(it2 = s2.begin(); it2 != s2.end(); ++it2){
		if(setU.find(*it2) == setU.end()){ // if element is not found in setU insert it into setU
			setU.insert(*it2);
		}
	}
	return setU;
}
/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
