#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "clothing.h"
#include "movie.h"
#include "book.h"
#include "user.h"
#include "mydatastore.cpp"
#include "datastore.h"

using namespace std;


// Struct comparator to sort products by name
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};


void displayProducts(vector<Product*>& hits);


int main(int argc, char* argv[])
{
    // Check if database file is provided
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;

        return 1;
    }

    // Instantiate a derived DataStore object
    MyDataStore ds; 

    // Instantiate individual section and product parsers
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    // Display menu
    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    string user = "";
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                // Parse search terms
                while(ss >> term) {
                    term = convToLower(term); // Convert term to lowercase
                    terms.push_back(term);
                }
                // Perform search with AND logic
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                // Parse search terms
                while(ss >> term) {
                    term = convToLower(term); // Convert term to lowercase
                    terms.push_back(term);
                }
                
                // Perform search with OR logic
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile); // Save database to a new file
                    ofile.close();
                }
                done = true; // Exit loop and terminate program
            }

            /* Add support for other commands here */
              else if (cmd == "ADD") {
              string user = "";
              size_t idx = 0;
              if (ss >> user) {
                // verify ss working by printing
                if (ss >> idx) {
                  if (idx <= hits.size() && idx > 0) {
                    ds.addToCart(user, hits[idx - 1]);
                  }
                  else {
                    cout << "Invalid request" << endl;
                  }
                }
                else {
                  cout << "Invalid request" << endl;
                }
              }
              else {
                cout << "Invalid request" << endl;
              }
            }

            else if (cmd == "VIEWCART") {
              string user = "";
              if (ss >> user) {
                ds.printCart(user);
              }
              else {
                cout << "Invalid request" << endl;
              }
            }
            else if (cmd == "BUYCART") {
              string user = "";
              if (ss >> user) {
                ds.buyCart(user);
              }
              else {
                cout << "Invalid request" << endl;
              }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
        cout << "No results found!" << endl;
        return;
    }
    // Display each hit
    //std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
