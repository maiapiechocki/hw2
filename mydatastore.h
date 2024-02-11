#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include <queue>

class MyDataStore: public DataStore {
  public: 

    MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type); 

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile); 
    void addToCart(std::string username, Product* p);
    void printCart(std::string username);
    void buyCart(std::string username);

  private:	
  // maps product name to product
	std::set<Product*> productList;
	// maps usernames to user* 
  std::set<User*> userList;
  // maps keyword to matching products set
  std::map<std::string, std::set<Product*>> pNameMap;  // maps keyword to set of products that match
    std::map<std::string, std::queue<Product*>>  cartMap;  // maps username to cartMap

};

#endif