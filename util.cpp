#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <string>

using namespace std;

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

// convert a string containing a rawWord to a set of words 

std::set<std::string> parseStringToWords(std::string rawWords) {
  std::string str = convToLower(trim(rawWords)); // Convert rawWords to lowercase and trim whitespace from the end
  std::set<std::string> parsedSet;

  std::string currWord;
  for(size_t i =0; i<=str.length(); ++i){ 
    if (i<str.length() && !std::isspace(str[i]) && !std::ispunct(str[i])) { // Check if the current character is not a space or punctuation and not past the end of the string
      currWord += str[i];
    }
    else {
      if (currWord.length() >= 2) { // If the current word has 2 or more characters insert it into the set
        parsedSet.insert(currWord);
        #ifdef DEBUG2
          std::cout << "Inserting word: " << currWord << std::endl;
        #endif
      }
      currWord.clear(); // Reset currWord to accumulate next word
    }
  }
  return parsedSet;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
