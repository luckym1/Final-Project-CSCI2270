#include <iostream>
#include "StyleHash.hpp"
#include <sstream>
#include <fstream>


using namespace std;


int main(int argc, char const *argv[]) {

  if(argc != 2){
    cout<<"Error, need a file to read in"<<endl;
    return -1;
  }
  string line;
  string word;
  string cell;
  ifstream recipeList;
  recipeList.open(argv[1]);
  if(!recipeList.is_open())
  {
    cout<<"Failed to open "<<argv[1]<<endl;
    return 0;
  }

  while(getline(recipeList, line, '\r')){
    cout<<"[*************** NEW ROW ********************]"<<endl;
    cout<<endl;
    //cout<<line<<endl;
    stringstream ss(line);
    while(getline(ss, cell, ',')){
      cout<<"-------------NEW CELL-----------------"<<endl;
      cout<<cell<<endl;

    }
    cout<<"[*************** END ROW ********************]"<<endl;
    cout<<endl;
  }



  return 0;
}
