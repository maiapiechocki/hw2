#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include <set>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn) 
	: Product(category, name, price, qty), 
    author_(author), isbn_(isbn) {
	
}
Book::~Book() {

}
/**
 * Returns the appropriate keywords that this product should be associated with
 */

// Generates a set of keywords for a Book object.
std::set<std::string> Book::keywords() const { // Use set keys = setUnion(s1,s2); 
    std::set<std::string> keys;
    std::set<std::string> author = parseStringToWords(author_);
    keys.insert(author.begin(), author.end());
    std::set<std::string> title = parseStringToWords(name_);
    keys.insert(title.begin(), title.end());
    keys.insert(isbn_);

    return keys;
}


 // Allows for a more detailed search beyond simple keywords
/*bool Book::isMatch(std::vector<std::string>& searchTerms) const {
  set
} */

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const {
  std::ostringstream s;
  s << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left." << endl;
  return s.str();
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const { 
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n"  << author_ << endl;
}

std::string Book::getAuthor() const {
  return author_;
}
std::string Book::getISBN() const {
  return isbn_;
}