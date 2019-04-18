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
  //cout<<beerStyle.name<<endl;
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
  int length = (int)styleName.length();
  for (int i=0;i<length;i++)
  {
    hashValue=((hashValue<<5)+hashValue) + styleName[i];
  }

  hashValue %= hashtableSize;
  //cout<<hashTableSize<<endl;
  return hashValue;
}

void StyleHash::searchStyles(string styleName){
  int index = getHash(styleName);
    if (!hashtable[index]) {
        return;
    }
  if(styleName == hashtable[index] -> name){
    cout<<"________________________________________________________"<<endl;
    cout<<"  STYLE:                                                |"<<endl;
    cout<<"                                                        |"<<endl;
    cout<<"  "<<hashtable[index] -> name<<"                         "<<endl;
    cout<<"                                                        |"<<endl;
    cout<<"========================================================"<<endl;
    cout<<"  Beer within Style:                                     "<<endl;
    cout<<"                                                         "<<endl;
    for(int i = 0; i<hashtable[index]->listOfRecipes.size(); i++){
      cout<<"   "<<hashtable[index]->listOfRecipes[i].name<<endl;
    }

  }
    else{
      // then I need to parse through the list and check to see if it is there.
      for(int j = 0; j<hashtableSize; j++){
        if(styleName == hashtable[j] -> name){
          cout<<"________________________________________________________"<<endl;
          cout<<"  STYLE:                                                |"<<endl;
          cout<<"                                                        |"<<endl;
          cout<<"  "<<hashtable[j] -> name<<"                            "<<endl;
          cout<<"                                                        |"<<endl;
          cout<<"========================================================"<<endl;
          cout<<"  Beer within Style:                                     "<<endl;
          cout<<"                                                         "<<endl;
          for(int i = 0; i<hashtable[j]->listOfRecipes.size(); i++){
            cout<<"   "<<hashtable[j]->listOfRecipes[i].name<<endl;
          }
          return;
        }
      }
      cout<<"Style not found"<<endl;
    }
  }
