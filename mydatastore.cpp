#include <sstream>
#include <set>
#include <vector>
#include <ostream>
#include <iostream>
#include <queue>
#include <iomanip>
#include "mydatastore.h"
#include "util.h"
#include <map>
#include <string>
#include "product.h"
#include "user.h"
#include <algorithm>
// #define DEBUG 
using namespace std;

MyDataStore::MyDataStore() {}
MyDataStore::~MyDataStore() {
    // delete all products and clear product list
    for (set<Product*>::iterator it = productList.begin(); it != productList.end(); ++it) {
        delete *it; // delete product pointed by iterator
    }
    productList.clear(); // clear the set after deleting all products

    // delete all users and clear user list
    for (set<User*>::iterator it = userList.begin(); it != userList.end(); ++it) {
        delete *it; // delete user pointed by iterator
    }
    userList.clear(); // clear the set after deleting all users

    // clear all user carts
    for (map<string, queue<Product*>>::iterator it = cartMap.begin(); it != cartMap.end(); ++it) {
        queue<Product*>& cart = it->second; // get reference to cart
        queue<Product*> empty; // create an empty queue
        swap(cart, empty); // swap current cart with empty queue to clear it
    }
    cartMap.clear(); // clear the map of carts
    pNameMap.clear(); // clear the product-name map
}


void MyDataStore::addProduct(Product* p) {
#ifdef DEBUG
  cout << "I work!" << endl;
#endif
    productList.insert(p); // add product to product list
    set<string> keywords = p->keywords(); // get product's keywords
    for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        // check if keyword already mapped
        if (pNameMap.find(*it) == pNameMap.end()) {
            set<Product*> newSet; // create new set for new keyword
            newSet.insert(p); // add product to new set
#ifdef DEBUG
            cout << "Set keyword: " << *it <<endl;
            cout << "Keyword product: " << p->getName() << endl;
#endif
            pNameMap.insert(std::pair<string, set<Product*>>(*it, newSet)); // map keyword to set
        } else {
#ifdef DEBUG
            cout << "Keyword exists: " << *it <<endl;
            cout << "Keyword product: " << p->getName() << endl;
            #endif
            pNameMap[*it].insert(p); // add product to existing set
        }
    }
}

void MyDataStore::addUser(User* u) {
    userList.insert(u); // add user to user list
    queue<Product*> cart; // create new cart
    cartMap.insert(make_pair(convToLower(u->getName()), cart)); // map user to new cart
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    vector<Product*> results; // store search results
        #ifdef DEBUG

    cout << "Starting search Number of terms: " << terms.size() << ", Search type: " << (type == 0 ? "AND" : "OR") << endl;
        #endif
    if (terms.empty()){
          #ifdef DEBUG

      cout << "No search terms provided." << endl;
      #endif
      return results; // return empty if no search terms
    }

    set<Product*> searchResults; // temporary set for search results
    if (type == 0) { // AND search logic
        #ifdef DEBUG

        cout << "Performing AND search..." << endl;
        #endif
        // initialize searchResults based on whether the first term is found in the map
      if (pNameMap.find(terms[0]) != pNameMap.end()) {
          searchResults = pNameMap[terms[0]];
      } else {
          searchResults = set<Product*>();
      }

            #ifdef DEBUG

        cout << "Set Checking: " << (pNameMap.find(terms[0]) != pNameMap.end()) << endl;
        cout << "Initial results size: " << searchResults.size() << " for term: " << terms[0] << endl;
        #endif
        // intersect results of subsequent terms
        for (size_t i = 1; i < terms.size(); ++i) {
            if (pNameMap.find(terms[i]) != pNameMap.end()) {
                searchResults = setIntersection(searchResults, pNameMap[terms[i]]);
                    #ifdef DEBUG

                cout << "Intersecting with results for term: " << terms[i] << ", New results size: " << searchResults.size() << endl;
                #endif
            } else {
                searchResults.clear(); // clear results if term not found
                cout << "Term not found, clearing results: " << terms[i] << endl;
                break;
            }
        }
    } else if (type == 1) { // OR search logic
       // cout << "Performing OR search..." << endl;
        // unite results of all terms
        for (string& term : terms) {
            if (pNameMap.find(term) != pNameMap.end()) {
                searchResults = setUnion(searchResults, pNameMap[term]);
                //cout << "Uniting with results for term: " << term << ", New results size: " << searchResults.size() << endl;
            }
        }
    }

    // convert set of products to vector
    #ifdef DEBUG
    cout << "Converting results to vector, final results size: " << searchResults.size() << endl;
    #endif
    for (set<Product*>::iterator it = searchResults.begin(); it != searchResults.end(); ++it) {
        results.push_back(*it);
    }

    return results; // return vector of product pointers
}


void MyDataStore::dump(ostream& ofile) {
    ofile << "<products>\n";
    for (set<Product*>::iterator it = productList.begin(); it != productList.end(); ++it) {
        (*it)->dump(ofile);
    }

    ofile << "</products>\n";
    ofile << "<users>\n";
    for (set<User*>::iterator it = userList.begin(); it != userList.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</users>\n";
}

void MyDataStore::addToCart(string username, Product* p) {
    string lowerUsername = convToLower(username);
    if (cartMap.find(lowerUsername) != cartMap.end()) {
        cartMap[lowerUsername].push(p);
    } else {
        cout << "Invalid request" << endl;
    }
}
void MyDataStore::printCart(string username) {
    string lowerUsername = convToLower(username);
    if (cartMap.find(lowerUsername) != cartMap.end()) {
        queue<Product*> tempQueue = cartMap[lowerUsername];
        int index = 1;
        while (!tempQueue.empty()) {
            cout << "Item " << index << "\n" << tempQueue.front()->displayString() << endl;
            tempQueue.pop();
            index++;
        }
    } else {
        cout << "Invalid username" << endl;
    }
}

void MyDataStore::buyCart(std::string username) {
  string lowerName = convToLower(username);
 if (cartMap.find(lowerName) == cartMap.end()) {
   cout << "Invalid username" << endl;
 }
 else {
   set<User*>::iterator it;
   User* u = nullptr;
   for (it = userList.begin(); it != userList.end(); ++it) {
     if (((*it)->getName().compare(lowerName) == 0)) {
       u = (*it);
       break;
     }
   }

    Product* p = nullptr; 
    // continues to buy cart items
    while ((!cartMap.find(lowerName)->second.empty())) {
      p = cartMap.find(lowerName)->second.front();
      if (p->getQty() > 0 && (u->getBalance() - p->getPrice() > 0)) {
        p->subtractQty(1);
        u->deductAmount(p->getPrice());
        cartMap.find(lowerName)->second.pop();
      }
      else {
        return;
      }
   }
 }
}