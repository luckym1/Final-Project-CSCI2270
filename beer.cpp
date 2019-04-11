//
//  beer.cpp
//  Final Project
//
//  Created by Michael Lucky on 4/4/19.
//  Copyright © 2019 Michael Lucky. All rights reserved.
//

#include "beer.hpp"

#include <iostream>

using namespace std;

//constructor that allocates dynamic memory and initializes private variables
//alloc and dealloc are for memory leak debug
Hash::Hash(int maxSize){
    if (maxSize > 0) {
        TableSize = maxSize;
    }
    alloc = 0;
    table = new recipe * [TableSize];
    alloc++;
    for (int i = 0; i < TableSize; i++) {
        table[i] = nullptr;
    }
    currSize = 0;
    dealloc = 0;
}
//free's all allocated memory by the constructor and insert function
Hash::~Hash(void){
}
// returns a hash key based on a string and the max table size
int Hash::hash(string key){
    int hashValue = 5381 ;
    size_t length = key.length();
    for (size_t i= 0; i < length; i++){
        hashValue=((hashValue << 5)+hashValue) + key[i];
    }
    hashValue %= TableSize;
    return abs(hashValue);
}
//input: beerRecipe structed with all members initialized
//takes the name of the beer and hash's, creates a dynamic node and copies
// given struct to it, then inserts it into a chained hash table
//output: full initialized structed allocated in dynamic memory with and placed
//properly in the hash table
void Hash::insert(recipe beerRecipe){
    int index = hash(beerRecipe.name);
    if (index >= 0 && index < TableSize) {

        if (!table[index]) {
            table[index] = new recipe;
            alloc++;
            table[index]->next = nullptr;
            table[index]->name = beerRecipe.name;
            table[index]->brewer = beerRecipe.brewer;
            table[index]->date = beerRecipe.date;
            table[index]->equipment = beerRecipe.equipment;
            table[index]->style = beerRecipe.style;
            table[index]->category = beerRecipe.category;
            table[index]->description1 = beerRecipe.description1;
            table[index]->minOG = beerRecipe.minOG;
            table[index]->maxOG = beerRecipe.maxOG;
            table[index]->minFG = beerRecipe.minFG;
            table[index]->maxFG = beerRecipe.maxFG;
            table[index]->minIBU = beerRecipe.minIBU;
            table[index]->maxIBU = beerRecipe.maxIBU;
            table[index]->minCarb = beerRecipe.minCarb;
            table[index]->maxCarb = beerRecipe.maxCarb;
            table[index]->minABV = beerRecipe.minABV;
            table[index]->maxABV = beerRecipe.maxABV;
            table[index]->grainWeight = beerRecipe.grainWeight;
            table[index]->grainTemp = beerRecipe.grainTemp;
            table[index]->boilTemp = beerRecipe.boilTemp;
            table[index]->PH = beerRecipe.PH;
            table[index]->age = beerRecipe.age;
            table[index]->OGmessured = beerRecipe.OGmessured;
            table[index]->FGmessured = beerRecipe.FGmessured;
            table[index]->ingredients = beerRecipe.ingredients;
            table[index]->description2 = beerRecipe.description2;
            table[index]->examples = beerRecipe.examples;
            cout << beerRecipe.name << " inserted" << endl;
        }else{
            recipe * pointer = table[index]->next, * chaser = table[index];
            while (pointer) {
                chaser = pointer;
                pointer = pointer->next;
            }
            chaser->next = new recipe;
            alloc++;
            chaser->next->next = nullptr;
            chaser->next->name = beerRecipe.name;
            chaser->next->brewer = beerRecipe.brewer;
            chaser->next->date = beerRecipe.date;
            chaser->next->equipment = beerRecipe.equipment;
            chaser->next->style = beerRecipe.style;
            chaser->next->category = beerRecipe.category;
            chaser->next->description1 = beerRecipe.description1;
            chaser->next->minOG = beerRecipe.minOG;
            chaser->next->maxOG = beerRecipe.maxOG;
            chaser->next->minFG = beerRecipe.minFG;
            chaser->next->maxFG = beerRecipe.maxFG;
            chaser->next->minIBU = beerRecipe.minIBU;
            chaser->next->maxIBU = beerRecipe.maxIBU;
            chaser->next->minCarb = beerRecipe.minCarb;
            chaser->next->maxCarb = beerRecipe.maxCarb;
            chaser->next->minABV = beerRecipe.minABV;
            chaser->next->maxABV = beerRecipe.maxABV;
            chaser->next->grainWeight = beerRecipe.grainWeight;
            chaser->next->grainTemp = beerRecipe.grainTemp;
            chaser->next->boilTemp = beerRecipe.boilTemp;
            chaser->next->PH = beerRecipe.PH;
            chaser->next->age = beerRecipe.age;
            chaser->next->OGmessured = beerRecipe.OGmessured;
            chaser->next->FGmessured = beerRecipe.FGmessured;
            chaser->next->ingredients = beerRecipe.ingredients;
            chaser->next->description2 = beerRecipe.description2;
            cout << beerRecipe.name << " chained" << endl;
        }
        currSize++;
    }
}
//Input: key that can be any variable of string type and the name of the variable to search
//Output: pointer to the recipe that contains the given key
//**** need to update ***
//needs to return a vector of pointers to ALL recipies that contain the given key, right now it only
//returns the first one
recipe * Hash::search(string key, string parameter){
    int s = 0;
    if (parameter == "name" || parameter == "Name") {
        s = 1;
    }else if (parameter == "brewer" || parameter == "Brewer"){
        s = 2;
    }else if (parameter == "equipment" || parameter == "Equipment"){
        s = 3;
    }else if (parameter == "style" || parameter == "Style"){
        s = 4;
    }else if (parameter == "category" || parameter == "Category"){
        s = 5;
    }else if (parameter == "description" || parameter == "Description"){
        s = 6;
    }else if (parameter == "ingrediant" || parameter == "Ingrediant" || parameter == "ingrediants" || parameter == "Ingrediants"){
        s = 7;
    }
    switch (s) {
        case 1:{
            int index = hash(key);
            if (index >= 0 && index < TableSize) {
                recipe * pointer = table[index];
                while (pointer) {
                    if (pointer->name == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 2:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->brewer == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 3:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->equipment == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 4:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->style == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 5:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->category == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 6:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->description1 == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 7:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->ingredients == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        default:
            cout << "not a vaild parameter" << endl;
            break;
    }
    return nullptr;
}
//Overloaded function to search for variables that are double type
//Input: double type variable and string of name of variable
//Output: vector of pointers to recipes that contain the key
vector<recipe *> Hash::search(double key, string parameter){
    int s = 0;
    vector<recipe *> recipes;
    recipes.clear();
    if (parameter == "minIBU" || parameter == "minimum IBU") {
        s = 1;
    }else if (parameter == "maxIBU" || parameter == "maximum IBU"){
        s = 2;
    }
    switch (s) {
        case 1:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->minIBU >= key) {
                        recipes.push_back(pointer);
                    }
                    pointer = pointer->next;
                }
            }
            break;
        }
        case 2:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->maxIBU <= key) {
                        recipes.push_back(pointer);
                    }
                    pointer = pointer->next;
                }
            }
            break;
        }
        default:
            cout << "not a vaild parameter" << endl;
            break;
    }
    return recipes;
}
//input: name of recipe to delete
//output: memory previously allocated for string is deallocated and
void Hash::del(string key){
    int index = hash(key);
    if (index >= 0 && index < TableSize && table[index]) {
        if (table[index]->name == key) {
            cout << table[index]->name << " deleted" << endl;
            recipe * temp = table[index];
            table[index] = table[index]->next;
            delete temp;
            temp = nullptr;
            dealloc++;
            currSize--;
            return;
        }else{
            recipe * pointer = table[index]->next, * chaser = table[index];
            while (pointer) {
                if (pointer->name == key) {
                    chaser->next = pointer->next;
                    cout << pointer->name << " deleted" << endl;
                    delete pointer;
                    pointer = nullptr;
                    dealloc++;
                    currSize--;
                    return;
                }
                chaser = pointer;
                pointer = pointer->next;
            }
        }
    }
    cout << "Could not find recipe to delete" << endl;
}
void Hash::printRecipe(recipe * rec){
    cout << "Name: " << rec->name << " | Style: " << rec->style <<  endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Category: " << rec->category << endl;
    cout << "Made by: " << rec->brewer<< " on " << rec->date << endl;
    cout << "Equipment: " << rec->equipment << endl;
    cout << "Ingredients: " << rec->ingredients << endl;
    cout << "Description: " << rec->description1 << endl;
    cout << "OG min: " << rec->minOG << " max: " << rec->maxOG << endl;
    cout << "FG min: " << rec->minFG << " max: " << rec->maxFG << endl;
    cout << "IBU min: " << rec->minIBU << " max: " << rec->maxIBU << endl;
    cout << "Carbination min: " << rec->minCarb << " max: " << rec->maxCarb << endl;
    cout << "ABV min: " << rec->minABV << " max: " << rec->maxABV << endl;
    cout << "Grain weight: " << rec->grainWeight << " Grain Temp: " << rec->grainTemp << endl;
    cout << "Boil Temp: " << rec->boilTemp << endl;
    cout << "PH: " << rec->PH << endl;
    cout << "Age Time: " << rec->age << " days" << endl;
    cout << "Measured OG: " << rec->OGmessured << " Measured FG: " << rec->FGmessured << endl;
    cout << "Examples: " << rec->examples << endl;
    cout << "Comments: " << rec->description2 << endl;
}
void Hash::print(){
    for (int i = 0; i < TableSize; i++) {
        recipe * pointer = table[i];
        while (pointer) {
            cout << pointer->name << endl;
            pointer = pointer->next;
        }
    }
}
