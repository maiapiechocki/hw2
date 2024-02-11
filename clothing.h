#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "product.h"

class Clothing: public Product {
public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
    
    ~Clothing();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    //bool isMatch(std::vector<std::string>& searchTerms) const; //do i need?

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;

    /**
     * Accessors and mutators
     */
    std::string getSize() const; // const bc read-only info, can't modify objects
    std::string getBrand() const;

private:
    std::string brand_;
    std::string size_;

};
#endif
