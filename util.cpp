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

std::set<std::string> parseStringToWords(std::string rawWords)
{
    std::string str = trim(rawWords); // remove whitespace before and after words
    str = convToLower(str); // convert to lowercase
    std::set<std::string> parsedSet; // initialize the answer set
    int indexOfSpace = 0; // idx of the letter after space

    int length = str.length();
    for (int i = 0; i < length; ++i) {
        if (str[i] == ' ' && (i - indexOfSpace >= 2)) {
            // word separated
            std::string word = str.substr(indexOfSpace, i - indexOfSpace);

            // iterate through each char of individual word
            int individualWordLength = word.length();
            for (int j = 0; j < individualWordLength; ++j) {
                // check for punctuation
                if (ispunct(word[j])) {
                    // check if the part before the punctuation is valid
                    if (individualWordLength - (individualWordLength - j) >= 2) {
                        word = word.substr(0, j);
                        break;
                    }
                    // else check if the part after the punctuation is valid
                    else if (individualWordLength - j - 1 >= 2) {
                        word = word.substr(j + 1, individualWordLength - j - 1);
                        break;
                    }
                }
            }
            parsedSet.insert(word);
            indexOfSpace = i + 1;
        }
        else if ((i == length - 1) && (i - indexOfSpace + 1 >= 2)) {
          // if its the last letter, and the letters b/w it and space >2
          // more than 2 letters after the space
          // word separated
            std::string word = str.substr(indexOfSpace, i - indexOfSpace + 1);
            #ifdef DEBUG2
            cout << "str.subtr() " << word << endl;
            #endif 
            int individualWordLength = word.length();
            for (int j = 0; j < individualWordLength; ++j) {
                // check for punctuation
                if (ispunct(word[j])) {
                    // check if the part before the punctuation is valid
                    if (individualWordLength - (individualWordLength - j) >= 2) {
                        word = word.substr(0, j);
                        break;
                    }
                    // else check if the part after the punctuation is valid
                    else if (individualWordLength - j - 1 >= 2) {
                        word = word.substr(j + 1, individualWordLength - j - 1);
                        break;
                    }
                }
            }
            #ifdef DEBUG2
            cout << "Inserting word " << word << endl;
            #endif
            parsedSet.insert(word);
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
