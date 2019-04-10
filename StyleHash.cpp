#include <iostream>
#include "StyleHash.hpp"
#include "beer.hpp"
using namespace std;


StyleHash::StyleHash(){
  hashtable = new Style * [hashtableSize];
  for(int i = 0; i<hashtableSize; i++){
    hashtable[i] = nullptr;
  }
  numCollisions = 0;
  currentSize = 0;
}

StyleHash::~StyleHash(){


}



void StyleHash::addStyle(Style beerStyle, recipe beerRecipe){
  // need to figure out something with vectors
  int indexForHashTable = getHash(beerStyle.name);
  bool placed = false;
  if(hashtable[indexForHashTable] == nullptr)
  {
    // then I can add in the style
    hashtable[indexForHashTable] = new Style;
    hashtable[indexForHashTable] -> name = beerStyle.name;
    hashtable[indexForHashTable] -> listOfRecipes.push_back(beerRecipe);
    //cout<<"STYLE ADDED!: "<<hashtable[indexForHashTable] -> name<<endl;
    //cout<<"Beer Recipe: "<<beerRecipe.name<<endl
    currentSize += 1;
  }
  else
  {
    // then there is something in the hashtable, check for collision or same...
    if(hashtable[indexForHashTable] -> name == beerStyle.name)
    {
      // then it is already listed as a style and can simply add the recipe.
      hashtable[indexForHashTable] -> listOfRecipes.push_back(beerRecipe);
    }
    else
    {
        // then there is a collision and we must deal with it.
        //first, must check the list for any that may have collided with it:
        for(int i = 0; i<hashtableSize; i++){
          if(hashtable[i] != nullptr){
            if(hashtable[i] -> name == beerStyle.name){
              hashtable[i] -> listOfRecipes.push_back(beerRecipe);
              return;
            }
          }
        }
        // if nothing collided with it, then it should be a new style and has a collision:
        numCollisions += 1;
        //cout<<"!!!!! collision at "<<hashtable[indexForHashTable] -> name<<"with "<<beerStyle.name<<endl;
        bool placed  = false;
        while(!placed){
          indexForHashTable += 1;
          if(hashtable[indexForHashTable] != nullptr)
          {
            indexForHashTable += 1;
          }
          else
          {
            hashtable[indexForHashTable] = new Style;
            hashtable[indexForHashTable] -> name = beerStyle.name;
            hashtable[indexForHashTable] -> listOfRecipes.push_back(beerRecipe);
            placed = true;
            //cout<<"STYLE ADDED!: "<<hashtable[indexForHashTable] -> name<<endl;
            currentSize += 1;
          }
        }
    }
  }
}



bool StyleHash::isInTable(string name){
  // if the beer style is in the table already, return true
  return true;


}
int StyleHash::getNumberCollisions(){
  return 0;

}

void StyleHash::printStyleList(){
  cout<<"________________________________________________________"<<endl;
  cout<<"                   Current Styles                       | "<<endl;
  cout<<"________________________________________________________"<<endl;

  for(int i = 0; i<hashtableSize; i++){
    if(hashtable[i] != nullptr){
      cout<<"________________________________________________________"<<endl;
      cout<<"********* Style:   ";
      cout<<hashtable[i] -> name<<endl;
      cout<<"Beer:"<<endl;
      for(int j = 0; j < hashtable[i] ->listOfRecipes.size(); j++){
        cout<<hashtable[i] ->listOfRecipes[j].name<<endl;
      }
    }
  }
  cout<<"________________________________________________________"<<endl;
}

unsigned int StyleHash::getHash(string styleName){
  unsigned int hashValue = 5380;
  int length = styleName.length();
  for (int i=0;i<length;i++)
  {
    hashValue=((hashValue<<5)+hashValue) + styleName[i];
  }

  hashValue %= hashtableSize;
  //cout<<hashTableSize<<endl;
  return hashValue;
}

Style* StyleHash::searchStyles(string styleName){
  int index = getHash(styleName);
  if(styleName == hashtable[index] -> name){
    return hashtable[index];
  }
  return NULL;

}
