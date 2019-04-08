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
    string name, brewer, equipment, style, category, description;
    double minOG, maxOG, minFG, maxFG, minIBU, maxIBU, minCarb, maxCarb, minABV;
    double maxABV, grainWeight, grainTemp, boilTemp, PH, age, OGmessured, FGmessured;
    vector <string> ingredients;
};

class Hash{
private:
    int alloc;
    int dealloc;
    int TableSize;
    recipe * * table;
    int hash(string name);
    int currSize;
public:
    Hash(int maxSize = 1000);
    ~Hash(void);
    void insert(recipe beerRecipe);
    recipe * search(string key, string parameter);
    recipe * search(double key, string parameter);
    void del(string name);
    void print(void);
};

#endif /* beer_hpp */
