#include <sstream>
#include <iomanip>
#include <iostream>
#include "clothing.h"
#include "util.h"
#include <string>
#include <set>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, 
std::string size, std::string brand)
	:Product(category, name, price, qty),
	brand_(brand),
	size_(size)
{
	// Name & brand turned into set of keywords
	std::set<std::string> set1 = parseStringToWords(name_);
 // cout << brand_ << endl; 
	std::set<std::string> set2 = parseStringToWords(brand_);
  
  std::set<std::string>::iterator it1; // use typename to clarify that iterator is a type
  // insert set
  #ifdef DEBUG2
  cout << "Keyword for brand: ";
	for(it1 = set2.begin(); it1 != set2.end(); ++it1){
		 cout << *it1 << " " ;
	}
  cout << endl;

  cout << "Keyword for name: ";
  for(it1 = set1.begin(); it1 != set1.end(); ++it1){
		cout << *it1 << " " ;
	}
  cout << endl;
  #endif

  
	this->keys = setUnion(set1,set2);
}

Clothing::~Clothing()
{
}
// Returns the appropriate keywords that this product should be associated with
std::set<std::string> Clothing::keywords() const
{
	// Accessor for keywords
	return keys;
}

/**
 * Allows for a more detailed search beyond simple keywords
     
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
}*/

// Returns a string to display the product info for hits of the search

std::string Clothing::displayString() const {
  std::ostringstream s;
  s << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left." << endl;
  return s.str();
}

// Outputs the product info in the database format
void Clothing::dump(std::ostream& os) const
{
	Product::dump(os);
	// cout << "dumping" << endl;
  os << size_ << "\n" << brand_ <<  endl;
}


//Accessors
std::string Clothing::getSize() const {
  return size_;
}
std::string Clothing::getBrand() const {
  return brand_;
}