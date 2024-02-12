#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

class Movie: public Product {
public:
    Movie(const std::string category, const std::string name, double price, int qty,
    std::string genre, std::string rating);
    
    ~Movie();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    //isMatch(std::vector<std::string>& searchTerms) const; //do i need?

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;

    std::string getGenre() const;
    std::string getRating() const;
    
private:
    std::string genre_;
    std::string rating_;

};
#endif
