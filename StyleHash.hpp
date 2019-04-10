#include <iostream>
#include "beer.hpp"
#include <vector>

using namespace std;

struct Style{

  string name;
  vector<recipe> listOfRecipes;
  //recipe *recipes = new recipe[100];
};

class StyleHash{
  public:
    StyleHash();
    ~StyleHash();
    void addStyle(Style beerStyle, recipe beerRecipe);
    bool isInTable(string name);
    int getNumberCollisions();
    void printStyleList();

  private:
    unsigned int getHash(string styleName);
    Style* searchStyles(string styleName);

    // Instance variables
    Style **hashtable;
    int numCollisions;
    int currentSize;
    const int hashtableSize = 5000;
};
