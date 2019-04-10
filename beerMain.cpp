#include <iostream>
#include "StyleHash.hpp"
#include <sstream>
#include <fstream>
#include "beer.hpp"


using namespace std;


int main(int argc, char const *argv[]) {

/*
    -------------- READING IN DATA  -----------------------------------------
*/
  if(argc != 2){
    cout<<"Error, need a file to read in"<<endl;
    return -1;
  }
  string line;
  string word;
  string cell;
  ifstream recipeList;
  int counter = 0;
  int counterMod;

  //------------------------ variables for the recipe struct ---------------
  string name, brewer, equipmentNotes, styleOfBeer, categoryOfBeer, beerDescription, beerIngredients;
  double beerMinOG, beerMaxOG, beerMinFG, beerMaxFG, beerMinIBU, beerMaxIBU,
  beerMinCarb, beerMaxCarb, beerMinABV, beerMaxABV, grain_weight, grain_temp,
  boil_temp, pHLevel, beerAge, measuredOG, measuredFG;
  recipe newRecipe;
  Style newStyle;
  // ------------------------- End Varibles for the recipe struct ------------
  Hash recipeHash(5000);
  StyleHash styleHash;
  recipeList.open(argv[1]);
  if(!recipeList.is_open())
  {
    cout<<"Failed to open "<<argv[1]<<endl;
    return 0;
  }
  getline(recipeList, line, '\r'); //want to pull in the first line to ignore it

  while(getline(recipeList, line, '\r')){
    //cout<<"[*************** NEW ROW ********************]"<<endl;
    //cout<<endl;
    //cout<<line<<endl;
    stringstream ss(line);
    while(getline(ss, cell, ',')){
      counter ++;
      counterMod = counter % 24;
      //cout<<counterMod<<endl;
      //cout<<cell<<endl;
      //cout<<"-------------NEW CELL-----------------"<<endl;
      //cout<<cell<<endl;
      switch (counterMod) {
        case 1:
          name = cell;
          break;
        case 2:
          brewer = cell;
          break;
        case 3:
          equipmentNotes = cell;
          break;
        case 4:
          styleOfBeer = cell;
          break;
        case 5:
          categoryOfBeer = cell;
          break;
        case 6:
          beerMinOG = stod(cell);
          break;
        case 7:
          beerMaxOG = stod(cell);
          break;
        case 8:
          beerMinFG = stod(cell);
          break;
        case 9:
          beerMaxFG = stod(cell);
          break;
        case 10:
          beerMinIBU = stod(cell);
          break;
        case 11:
          beerMaxIBU = stod(cell);
          break;
        case 12:
          beerMinCarb = stod(cell);
          break;
        case 13:
          beerMaxCarb = stod(cell);
          break;
        case 14:
          beerMinABV = stod(cell);
          break;
        case 15:
          beerMaxABV = stod(cell);
          break;
        case 16:
          beerDescription = cell;
          break;
        case 17:
          beerIngredients = cell;
          break;
        case 18:
          grain_weight = stod(cell);
          break;
        case 19:
          grain_temp = stod(cell);
          break;
        case 20:
          boil_temp = stod(cell);
          break;
        case 21:
          pHLevel = stod(cell);
          break;
        case 22:
          beerAge = stod(cell);
          break;
        case 23:
          measuredOG = stod(cell);
          break;
        case 0:
          measuredFG = stod(cell);
          break;
      }
    }
    //cout<<"[*************** END ROW ********************]"<<endl;
    // now I can add all of the values from the row to a recipe struct and save that
    // struct into the recipe hash table and the Style hash table
    newRecipe.name = name;
    newRecipe.brewer = brewer;
    newRecipe.equipment = equipmentNotes;
    newRecipe.style = styleOfBeer;
    newRecipe.category = categoryOfBeer;
    newRecipe.minOG = beerMinOG;
    newRecipe.maxOG = beerMaxOG;
    newRecipe.minFG = beerMinFG;
    newRecipe.maxFG = beerMaxFG;
    newRecipe.minIBU = beerMinIBU;
    newRecipe.maxIBU = beerMaxIBU;
    newRecipe.minCarb = beerMinCarb;
    newRecipe.maxCarb = beerMaxCarb;
    newRecipe.minABV = beerMinABV;
    newRecipe.maxABV = beerMaxABV;
    newRecipe.grainTemp = grain_temp;
    newRecipe.grainWeight = grain_weight;
    newRecipe.boilTemp = boil_temp;
    newRecipe.PH = pHLevel;
    newRecipe.age = beerAge;
    newRecipe.OGmessured = measuredOG;
    newRecipe.FGmessured = measuredFG;

    newStyle.name = styleOfBeer;
    //newRecipe.ingredients = beerIngredients; // need to change ADT
    //cout<<newRecipe.name;
    recipeHash.insert(newRecipe);
    styleHash.addStyle(newStyle, newRecipe);
  }


  /*
      -------------- END READING IN DATA  --------------------------------------
      *************************************************************************
      -------------     MAIN MENU        --------------------------------------
  */
  cout<<"********************************************************"<<endl;
  cout<<"~                                                      ~"<<endl;
  cout<<"~                 BEER RECIPE DATABASE                 ~"<<endl;
  cout<<"~                                                      ~"<<endl;
  cout<<"~                      Created by:                     ~"<<endl;
  cout<<"~                     Michael Lucky                    ~"<<endl;
  cout<<"~                      David Welsh                     ~"<<endl;
  cout<<"~                        Apr 2019                      ~"<<endl;
  cout<<"~                                                      ~"<<endl;
  cout<<"********************************************************"<<endl;
  cout<<endl;


  bool run = true;
  string userInput;
  int userInputInt;

  while(run){
    cout<<"-------------------    Main Menu    --------------------"<<endl;
    cout<<"                                                        | "<<endl;
    cout<<"1)   Brew Beer!                                         |"<<endl;
    cout<<"2)   Search Inventory                                   |"<<endl;
    cout<<"3)   Add Recipe                                         |"<<endl;
    cout<<"4)   Delete Recipe                                      |"<<endl;
    cout<<"5)   Print Recipe List                                  |"<<endl;
    cout<<"6)   Quit                                               |"<<endl;
    cout<<"                                                        | "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<">> ";
    getline(cin, userInput);
    userInputInt = stoi(userInput);
    switch (userInputInt) {
      case 1:
        cout<<endl;
        cout<<"Please enter the name of the beer you wish to brew: "<<endl;
        cout<<">>";
        getline(cin, userInput);
        // need to search through the beer list to find the recipe
        break;

        //----------------- MAIN CASE 2 ---------------------------------------
      case 2:
        cout<<endl;
        cout<<"how would you like to search? "<<endl;
        cout<<endl;
        cout<<"____________________    Search     _____________________"<<endl;
        cout<<"                                                        | "<<endl;
        cout<<"1)   Search by Beer Name                                |"<<endl;
        cout<<"2)   Search by Style                                    |"<<endl;
        cout<<"3)   Search by IBU                                      |"<<endl;
        cout<<"4)   Search by ABV                                      |"<<endl;
        cout<<"5)   return to Main Menu                                |"<<endl;
        cout<<"                                                        | "<<endl;
        cout<<"________________________________________________________"<<endl;
        cout<<">> ";
        getline(cin, userInput);
        switch (stoi(userInput)) {
          case 1:
            cout<<endl;
            cout<<"Enter the name of the beer: "<<endl;
            cout<<">>";

            break;
          case 2:
            cout<<endl;
            cout<<"Enter the style of the beer: "<<endl;
            cout<<">>";
            getline(cin, userInput);
            break;
          case 3:
            cout<<endl;
            cout<<"Search for minimum IBU or maximum IBU? "<<endl;
            cout<<"1) Minimum IBU "<<endl;
            cout<<"2) MAximum IBU "<<endl;
            cout<<">>";
            getline(cin, userInput);
            break;
          case 4:
            cout<<endl;
            cout<<"Search for minimum ABV or maximum ABV? "<<endl;
            cout<<"1) Minimum ABV "<<endl;
            cout<<"2) MAximum ABV "<<endl;
            cout<<">>";
            getline(cin, userInput);
            break;
          case 5:
            break;
        }
        break;

        //----------------- MAIN CASE 3 ---------------------------------------
      case 3:
        // ADD a Recipe .... FML, this is going to be a long one
        cout<<endl;
        cout<<"Please enter the following information as it is given"<<endl;
        cout<<"If you do not know the question, leave it blank"<<endl;
        cout<<endl;
        cout<<"________________________________________________________"<<endl;
        cout<<"1. What is the name of the beer? "<<endl;
        
        break;

        //----------------- MAIN CASE 4 ---------------------------------------
      case 4:
        // delete a recipe
        cout<<endl;
        cout<<"What is the name of the beer recipe you would like to delete? ";
        cout<<">> ";
        getline(cin, userInput);
        //search the recipe list for the name
        break;

        //----------------- MAIN CASE 5 ---------------------------------------
      case 5:
        cout<<endl;
        cout<<"Would you like to print by STYLE or by BEER NAME? "<<endl;
        cout<<"1) Print by Style "<<endl;
        cout<<"2) Print by Beer Name "<<endl;
        cout<<">>";
        getline(cin, userInput);
        if(userInput == "1")
        {
          cout<<"....Printing by style"<<endl;
          styleHash.printStyleList();
        }
        else if(userInput == "2")
        {

        }
        break;

        //----------------- MAIN CASE 6 ---------------------------------------
      case 6:

        run = false;
        break;
    }
  }
  return 0;
}
