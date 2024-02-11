#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include <set>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn) 
	: Product(category, name, price, qty), author_(author), isbn_(isbn) {
	
}
Book::~Book() {

}
/**
 * Returns the appropriate keywords that this product should be associated with
 */

// Generates a set of keywords for a Book object.
std::set<std::string> Book::keywords() const {
    // Initialize an empty set to store the keywords.
    std::set<std::string> keys;

    // Parse author's name into individual words and store them in a set.
    std::set<std::string> author = parseStringToWords(author_);
    // Insert all words from the author's name into the keywords set.
    keys.insert(author.begin(), author.end());

    // Parse book's title into individual words and store them in a set.
    std::set<std::string> title = parseStringToWords(name_);
    // Insert all words from the book's title into the keywords set.
    keys.insert(title.begin(), title.end());

    // Insert the book's ISBN directly into the keywords set.
    keys.insert(isbn_);

    // Return the complete set of keywords for the book.
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

//Accessors
std::string Book::getAuthor() const {
  return author_;
}
std::string Book::getISBN() const {
  return isbn_;
}