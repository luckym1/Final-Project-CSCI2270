#include <iostream>
#include "StyleHash.hpp"
#include <sstream>
#include <fstream>
#include "beer.hpp"

#define NCOLS 26 //number of items in each line to read in

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
    vector <string> lineVector;
    
    //------------------------ variables for the recipe struct ---------------
    string styleOfBeer;
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
    getline(recipeList, line, '\n'); //want to pull in the first line to ignore it
    int count = 0;
    while(getline(recipeList, line, '\r')){
        count++;
        //cout<<"[*************** NEW ROW ********************]"<<endl;
        //cout<<endl;
        //cout<<line<<endl;
        stringstream ss(line);
        lineVector.clear(); //initialize this to start new each line
        while(getline(ss, cell, ',')){
            lineVector.push_back(cell);
            //cout<<cell<<endl;
        }
        //cout<<"[*************** END ROW ********************]"<<endl;
        // now I can add all of the values from the row to a recipe struct and save that
        // struct into the recipe hash table and the Style hash table
        //cout << "First Letter in name: " << lineVector[0][0] << endl;
        if (isspace(lineVector[0][0])){
            lineVector[0].erase(lineVector[0].begin());
        }
        //cout << "First Letter in name after erase: " << lineVector[0][0] << endl;
        newRecipe.name = lineVector[0];
        newRecipe.brewer = lineVector[1];
        newRecipe.date = lineVector[2];
        newRecipe.equipment = lineVector[3];
        newRecipe.style = lineVector[4];
        newRecipe.category = lineVector[5];
        try {
            newRecipe.minOG = stod(lineVector[6]);
            newRecipe.maxOG = stod(lineVector[7]);
            newRecipe.minFG = stod(lineVector[8]);
            newRecipe.maxFG = stod(lineVector[9]);
            newRecipe.minIBU = stod(lineVector[10]);
            newRecipe.maxIBU = stod(lineVector[11]);
            newRecipe.minCarb = stod(lineVector[12]);
            newRecipe.maxCarb = stod(lineVector[13]);
            newRecipe.minABV = stod(lineVector[14]);
            newRecipe.maxABV = stod(lineVector[15]);
        }catch (invalid_argument) {
            cout << "invalid stod() conversion in " << argv[1] << endl;
            for (int i = 0; i < lineVector.size(); i++) {
                cout << lineVector[i] << " ";
            }
            cout << endl;
            cout << count << endl;
            cout << "Error on line: " << count << endl;
            exit(0);
        }
        newRecipe.description1 = lineVector[16];
        newRecipe.ingredients = lineVector[17];
        newRecipe.examples = lineVector[18];
        try {
            newRecipe.grainWeight = stod(lineVector[19]);
            newRecipe.grainTemp = stod(lineVector[20]);
            newRecipe.boilTemp = stod(lineVector[21]);
            newRecipe.PH = stod(lineVector[22]);
            newRecipe.age = stod(lineVector[23]);
            newRecipe.OGmessured = stod(lineVector[24]);
            newRecipe.FGmessured = stod(lineVector[25]);
        }catch (invalid_argument) {
            cout << "invalid stod() conversion in " << argv[1] << endl;
            for (int i = 0; i < lineVector.size(); i++) {
                cout << lineVector[i] << " ";
            }
            cout << endl;
            cout << "Error on line: " << count << endl;
            exit(0);
        }
        newRecipe.description2 = lineVector[26];
        
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
        try{
            userInputInt = stoi(userInput);
        }catch(invalid_argument){
            cout << "Input must be a integer number" << endl;
        }
        
        switch (userInputInt) {
            case 1:{
                cout<<endl;
                cout<<"Please enter the name of the beer you wish to brew: "<<endl;
                cout<<">>";
                getline(cin, userInput);
                // need to search through the beer list to find the recipe
                recipe * found = recipeHash.search(userInput, "name");
                if (found) {
                    recipeHash.printRecipe(found);
                }else{
                    cout << "Not found in list" << endl;
                }
                
                break;
            }
                
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
                    recipeHash.print();
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
