//
//  beer.hpp
//  Final Project
//
//  Created by Michael Lucky on 4/4/19.
//  Copyright © 2019 Michael Lucky. All rights reserved.
//

#ifndef beer_hpp
#define beer_hpp

#include <string>
#include <vector>

using namespace std;

struct recipe{
    recipe * next;
    string name, brewer, date, equipment, style, category, description1, description2, ingredients, examples;
    double minOG, maxOG, minFG, maxFG, minIBU, maxIBU, minCarb, maxCarb, minABV;
    double maxABV, grainWeight, grainTemp, boilTemp, PH, age, OGmessured, FGmessured;
    //int csvRow;

};

class Hash{
private:
    //used for memory debug
    int alloc;
    int dealloc;

    //max table size
    int TableSize;

    //array of recipe structs used for hash table
    recipe * * table;

    //hashing function for string type into integer
    int hash(string name);

    //current number of recipies in hash table
    int currSize;

public:
    //constructor with default table size of 1000
    Hash(int maxSize = 1000);
    //destructor
    ~Hash(void);

    //Input: fully initialized recipe struct
    //Output: memory allocated for struct and pointer to struct stored in proper
    //        place in hash table
    void insert(recipe beerRecipe);

    //Overloaded function
    //Input: string or double and a string of the parameter type to search
    //Output: vector of recipe's that contain the given parameter
    recipe * search(string key, string parameter);
    vector<recipe *> search(double key, string parameter);

    //Input: string to name of recipe
    //Output: Recipe struct removed from hash table, memory deallocated
    void del(string name);

    void printRecipe(recipe * rec);

    //Input: must have a initialized Hash object
    //Output: Printed to screen the number of each "bucket" in the hash array
    //        and the recipies that are currently inside each bucket
    void print(void);
};

#endif /* beer_hpp */
